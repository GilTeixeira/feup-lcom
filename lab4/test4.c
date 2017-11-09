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
/*
	if (sys_inb_cnt(STAT_REG, &stat) != Ok)
		return KBD_TEST_SCAN_ERROR;

	if (stat & OBF) {
		if (sys_inb_cnt(OUT_BUF, &code) != Ok)
			return KBD_TEST_SCAN_ERROR;
	}

	*/
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

int mouse_test_remote(unsigned long period, unsigned short cnt){
    /* To be completed ... */

	return 0;
}	

int mouse_test_gesture(short length){
    /* To be completed ... */

	return 0;
}	
