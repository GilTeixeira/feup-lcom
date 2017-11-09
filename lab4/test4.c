#include <minix/syslib.h>
#include <minix/driver.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "i8042.h"
#include "i8254.h"
#include "mouse.h"


int mouse_test_packet(unsigned short cnt){
	printf("RIP?\n");
	int ipc_status, r, irq_set;
	unsigned short curr_num_packets=0;

	message msg;
	irq_set = mouse_subscribe_int();
	printf("RIP2\n");


	//if (irq_set < 0)
		//return KBD_SUB_ERROR;
	enable_stream_mode();
	printf("RIP2.5\n");
	while (curr_num_packets != cnt) {
		printf("RIP3\n");


		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		printf("RIP4\n");


		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

					printf("jiogipdsfjpkdfs\n");
					mouse_handler();
					if (fullPacket)
						print_packets();
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
	printf("RIP5\n");
	if (mouse_unsubscribe_int() != 0)
		return 1;



	return Ok;

}	

int mouse_test_async(unsigned short idle_time){
    /* To be completed ... */

	return 0;
}	

int mouse_test_remote(unsigned long period, unsigned short cnt){
    /* To be completed ... */

	return 0;
}	

int mouse_test_gesture(short length){
    /* To be completed ... */

	return 0;
}	
