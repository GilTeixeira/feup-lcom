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

extern unsigned long packet[3];
extern long xdelta, ydelta;
typedef enum {
	INIT, DRAW, COMP
} state_t;

typedef enum {
	RDOWN, RUP, MOV
} ev_type_t;

struct event_t {
	ev_type_t type;
	short length;
	short deltax;
	short deltay;
};

static state_t mouseSt = INIT; // initial state; keep state
static ev_type_t type,short deltax=0,short deltay=0;

unsigned long cleanOutBuf(){
	unsigned long  stat, code;
	if (sys_inb(STAT_REG, &stat) != Ok)
				return SYS_IN_ERROR;

			if (stat & OBF) {
				if (sys_inb(OUT_BUF, &code) != Ok)
					return SYS_IN_ERROR;
			}
			return Ok;
}

int mouse_test_packet(unsigned short cnt){
	int ipc_status, r, irq_set;
	unsigned short curr_num_packets=0;

	message msg;
	irq_set = mouse_subscribe_int();

	//if (irq_set < 0)
		//return KBD_SUB_ERROR;
	enable_stream_mode();

	while (curr_num_packets < cnt*3) {


		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}


		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

					mouse_handler();
					if (fullPacket)
						print_packets();
					curr_num_packets++;
				}
				break;
			default:
				break;
			}
		} else {
		}
	}

	if (mouse_unsubscribe_int() != 0)
		return 1;

	return Ok;

}	

int mouse_test_async(unsigned short idle_time) {

	int ipc_status, r, irq_set_timer, irq_set_mouse;
	unsigned long code = 0, stat;

	int counter = 0;

	message msg;
	irq_set_mouse = mouse_subscribe_int();

	if (irq_set_mouse < 0)
		//TODO alterar
		return KBD_SUB_ERROR;

	irq_set_timer = timer_subscribe_int();

	if (irq_set_timer < 0)
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
					counter=0;

					/*if (code == FIRST_BYTE)
						isSecondByte = 1;
					kbd_handler();
					code = globalCode;
					if (code != FIRST_BYTE)
						printcode(code, isSecondByte);

					isSecondByte = 0;
					counter = 0;
					*/

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

	if (sys_inb(STAT_REG, &stat) != Ok)
		return SYS_IN_ERROR;

	if (stat & OBF) {
		if (sys_inb(OUT_BUF, &code) != Ok)
			return SYS_IN_ERROR;
	}

	if (timer_unsubscribe_int() != Ok)
		return TIMER_UNSUB_ERROR;

	if (mouse_unsubscribe_int() != Ok)
		return KBD_UNSUB_ERROR;

	return Ok;

}	

int mouse_test_remote(unsigned long period, unsigned short cnt) {
	mouse_subscribe_Exc_int();

	//printf("1\n");

	mouseWriteCommandByte(DISABLE_DR);
	//printf("2\n");
	mouseWriteCommandByte(SET_REMOTE_MODE);
	//printf("3\n");
	/*
	cmd_byte = ReadCommandByte();
	printf("4\n");
	cmd_byte = cmd_byte | DISABLE_MOUSE_INT;
	printf("5\n");

	WriteCommandByte(KBC_CMD_REG, cmd_byte);
	*/
	//printf("6\n");

	while (cnt > 0) {
		//printf("7\n");
		mouseWriteCommandByte(READ_DATA);
		int i;
		for (i = 0; i < 3; i++)
			mouse_handler();

		cnt--;

		print_packets();

		tickdelay(micros_to_ticks(period*1000));

	}



	//enable Minix’s IHby writing to the KBC’s command byte
	/*
	cmd_byte = ReadCommandByte();
	cmd_byte = cmd_byte | ENABLE_MOUSE_INT;

	WriteCommandByte(KBC_CMD_REG, cmd_byte);
*/
	// Set	stream mode
	// ensure data reporting is disabled
	//printf("7\n");
	enable_stream_mode();
	//printf("8\n");

	cleanOutBuf();
	//printf("9\n");
	mouse_unsubscribe_int();
	return 0;
}	

int mouse_test_gesture(short length){
	int ipc_status, r, irq_set;

	message msg;
	struct event_t event;
	event.deltax = xdelta;
	event.deltay = ydelta;
	event.length = length;


	irq_set = mouse_subscribe_int();

	//if (irq_set < 0)
		//return KBD_SUB_ERROR;
	enable_stream_mode();

	while (1) {

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

if((packet[0] & MOUSE_RB) && deltax>0 && deltay<0){
	short newlength=length;
	newlength=newlength+deltax;
}


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

	if (mouse_unsubscribe_int() != 0)
		return 1;



	return Ok;

}

state_t statereader(event_t * evt) {

	switch (mouseSt) {
	case INIT:
		if (evt->type == RDOWN)
			mouseSt = DRAW;
		break;
	case DRAW:
if (evt->type == RUP){
			mouseSt = INIT;
	}else if(evt->type==MOV){

	}
	break;
	default:
		break;
	}
}

ev_type_t event() {

    static int direita=2;
    int length=0;
	switch (mousest) {
	case INIT:
		if(packet[0] & MOUSE_RB)
		type=RDOWN;
		return type;
		break;

	case DRAW:
		if((packet[0] & MOUSE_RB)==0){
			type=RUP;
			return RUP;}

		if((packet[0] & MOUSE_XSIGN)==0){
			deltax=packet[1];}
		else{
			deltax =| packet[1];}

		if((packet[0] & MOUSE_YSIGN)==0){
			deltay=packet[2];}
		else{
			deltay =| packet[2];}

		if((length>0 && direita && deltax>0 && deltay>0) || length<0 && direita && deltax<0 && deltay<0){
			type=MOV;
			return type;}
	break;
	default:
		break;

	}
}
