#include <minix/syslib.h>
#include <minix/driver.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "i8042.h"
#include "i8254.h"
#include "mouse.h"
#include "kbd.h"
#include "timer.h"
#include "test4.h"

extern unsigned long packet[3];
extern int fullPacket;

static state_t mouseSt = INIT;

int mouse_test_packet(unsigned short cnt) {
	int ipc_status, r, irq_set;
	unsigned short curr_num_packets = 0;

	message msg;
	irq_set = mouse_subscribe_int();

	if (irq_set < 0)
		return MOUSE_SUB_ERROR;

	if (enable_stream_mode() != Ok)
		return ENAB_STREAM_MODE_ERROR;

	while (curr_num_packets < cnt) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

					mouse_handler();
					if (fullPacket) {
						print_packets();
						curr_num_packets++;
					}
				}
				break;
			default:
				break;
			}
		} else {
		}
	}

	if (cleanOutBuf() != Ok)
		return CLEAN_OUTBUFF_ERROR;

	if (mouse_unsubscribe_int() != Ok)
		return MOUSE_UNSUB_ERROR;

	return Ok;

}

int mouse_test_async(unsigned short idle_time) {

	int ipc_status, r, irq_set_timer, irq_set_mouse;

	int counter = 0;

	message msg;
	irq_set_mouse = mouse_subscribe_int();

	if (irq_set_mouse < 0)
		return MOUSE_SUB_ERROR;

	irq_set_timer = timer_subscribe_int();

	if (irq_set_timer < Ok)
		return TIMER_SUB_ERROR;

	while (counter != 60 * idle_time) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;

		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_mouse) { /* subscribed interrupt */
					mouse_handler();
					if (fullPacket)
						print_packets();
					counter = 0;

				}
				if (msg.NOTIFY_ARG & irq_set_timer) { /* subscribed interrupt */
					counter++;
				}
				break;
			default:
				break;
			}
		} else {
		}
	}

	if (cleanOutBuf() != Ok)
		return CLEAN_OUTBUFF_ERROR;

	if (timer_unsubscribe_int() != Ok)
		return TIMER_UNSUB_ERROR;

	if (mouse_unsubscribe_int() != Ok)
		return MOUSE_UNSUB_ERROR;

	return Ok;

}

int mouse_test_remote(unsigned long period, unsigned short cnt) {

	int irq_set;
	irq_set = mouse_subscribe_Exc_int();

	if (irq_set < 0)
		return MOUSE_SUB_ERROR;

	if (mouseWriteCommandByte(DISABLE_DR) != Ok)
		return MOUSE_WRITE_CMD_ERROR;
	if (mouseWriteCommandByte(SET_REMOTE_MODE) != Ok)
		return MOUSE_WRITE_CMD_ERROR;

	while (cnt > 0) {
		if (mouseWriteCommandByte(READ_DATA) != Ok)
			return MOUSE_WRITE_CMD_ERROR;

		int i;
		for (i = 0; i < 3; i++)
			mouse_handler();

		cnt--;
		print_packets();

		tickdelay(micros_to_ticks(period * 1000));
	}

	if (enable_stream_mode() != Ok)
		return ENAB_STREAM_MODE_ERROR;
	if (cleanOutBuf() != Ok)
		return CLEAN_OUTBUFF_ERROR;
	if (mouse_unsubscribe_int() != Ok)
		return MOUSE_UNSUB_ERROR;

	return Ok;
}

int mouse_test_gesture(short length) {
	int ipc_status, r, irq_set;

	message msg;

	struct event_t mouseEvent;
	mouseEvent.evType = BTTUP;
	mouseEvent.deltax = 0;
	mouseEvent.deltay = 0;
	mouseEvent.length_moved = 0;
	mouseEvent.length_to_move = length;

	irq_set = mouse_subscribe_int();

	if (irq_set < 0)
		return MOUSE_SUB_ERROR;

	if (enable_stream_mode() != Ok)
		return ENAB_STREAM_MODE_ERROR;

	while (mouseSt != DONE) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

					mouse_handler();
					if (fullPacket) {
						processEvent(&mouseEvent);
						processStateMachine(&mouseEvent);

						print_packets();

					}

				}
				break;
			default:
				break;
			}
		} else {
		}
	}

	if (cleanOutBuf() != Ok)
		return CLEAN_OUTBUFF_ERROR;

	if (mouse_unsubscribe_int() != Ok)
		return 1;

	return Ok;

}

unsigned long cleanOutBuf() {
	unsigned long stat, code;
	if (sys_inb(STAT_REG, &stat) != Ok)
		return SYS_IN_ERROR;

	if (stat & OBF) {
		if (sys_inb(OUT_BUF, &code) != Ok)
			return SYS_IN_ERROR;
	}
	return Ok;
}

long getDeltaX() {

	long xdelta = convertNumber(packet[1], packet[0] & MOUSE_XSIGN);
	return xdelta;

}

long getDeltaY() {

	long ydelta = convertNumber(packet[2], packet[0] & MOUSE_YSIGN);
	return ydelta;
}

int isRightButtonPressed() {
	return packet[0] & MOUSE_RB;

}

void processStateMachine(struct event_t * mouseEvent) {

	switch (mouseSt) {
	case INIT:
		if (mouseEvent->evType == BTTDOWN)
			mouseSt = MBTTPRESSED;
		break;
	case MBTTPRESSED:
		if (mouseEvent->evType == BTTUP)
			mouseSt = INIT;
		else if (mouseEvent->evType == MOVEDUPRIGHT)
			mouseSt = MOVUPRIGHT;
		else if (mouseEvent->evType == MOVEDDOWNLEFT)
			mouseSt = MOVEDOWNLEFT;
		else if (mouseEvent->evType == COMPLETED)
			mouseSt = DONE;

		break;
	case MOVUPRIGHT:
		if (mouseEvent->evType == BTTUP)
			mouseSt = INIT;
		else if (mouseEvent->evType == MOVEDDOWNLEFT)
			mouseSt = MOVEDOWNLEFT;
		else if (mouseEvent->evType == COMPLETED)
			mouseSt = DONE;

		break;
	case MOVEDOWNLEFT:
		if (mouseEvent->evType == BTTUP)
			mouseSt = INIT;
		else if (mouseEvent->evType == MOVEDUPRIGHT)
			mouseSt = MOVUPRIGHT;
		else if (mouseEvent->evType == COMPLETED)
			mouseSt = DONE;

		break;
	default:
		break;

	}

}

void processEvent(struct event_t * mouseEvent) {
	mouseEvent->deltax = getDeltaX();
	mouseEvent->deltay = getDeltaY();

	if (!isRightButtonPressed()) {
		mouseEvent->length_moved = 0;
		mouseEvent->evType = BTTUP;
		return;
	}

	switch (mouseSt) {
	case INIT:
		mouseEvent->evType = BTTDOWN;
		break;
	case MBTTPRESSED:
		if (mouseEvent->deltax > 0 && mouseEvent->deltay >= 0
				&& mouseEvent->length_to_move > 0) {
			mouseEvent->length_moved += mouseEvent->deltax;
			if (mouseEvent->length_moved >= mouseEvent->length_to_move)
				mouseEvent->evType = COMPLETED;
			else
				mouseEvent->evType = MOVEDUPRIGHT;

		} else if (mouseEvent->deltax < 0 && mouseEvent->deltay <= 0
				&& mouseEvent->length_to_move < 0) {
			mouseEvent->length_moved += mouseEvent->deltax;
			if (mouseEvent->length_moved <= mouseEvent->length_to_move)
				mouseEvent->evType = COMPLETED;
			else
				mouseEvent->evType = MOVEDDOWNLEFT;

		}

		break;
	case MOVUPRIGHT:
		if (mouseEvent->deltax >= 0 && mouseEvent->deltay >= 0
				&& mouseEvent->length_to_move > 0) {
			mouseEvent->length_moved += mouseEvent->deltax;
			if (mouseEvent->length_moved >= mouseEvent->length_to_move)
				mouseEvent->evType = COMPLETED;
			else
				mouseEvent->evType = MOVEDUPRIGHT;

		} else if (mouseEvent->deltax <= 0 && mouseEvent->deltay <= 0
				&& mouseEvent->length_to_move < 0) {
			mouseEvent->length_moved += mouseEvent->deltax;
			if (mouseEvent->length_moved <= mouseEvent->length_to_move)
				mouseEvent->evType = COMPLETED;
			else
				mouseEvent->evType = MOVEDDOWNLEFT;

		} else {
			mouseEvent->length_moved = 0;
			mouseEvent->evType = MBTTPRESSED;

		}

		break;
	case MOVEDOWNLEFT:
		if (mouseEvent->deltax >= 0 && mouseEvent->deltay >= 0
				&& mouseEvent->length_to_move > 0) {
			mouseEvent->length_moved += mouseEvent->deltax;
			if (mouseEvent->length_moved >= mouseEvent->length_to_move)
				mouseEvent->evType = COMPLETED;
			else
				mouseEvent->evType = MOVEDUPRIGHT;

		} else if (mouseEvent->deltax <= 0 && mouseEvent->deltay <= 0
				&& mouseEvent->length_to_move < 0) {
			mouseEvent->length_moved += mouseEvent->deltax;
			if (mouseEvent->length_moved <= mouseEvent->length_to_move)
				mouseEvent->evType = COMPLETED;
			else
				mouseEvent->evType = MOVEDDOWNLEFT;

		} else {
			mouseEvent->length_moved = 0;
			mouseEvent->evType = MBTTPRESSED;

		}
		break;
	default:
		break;

	}

}

