#include <minix/syslib.h>
#include <minix/driver.h>
#include "i8042.h"
#include "i8254.h"
#include "kbd.c"
#include <limits.h>
#include <string.h>
#include <errno.h>

//#ifdef LAB3
//int sys_inb_cnt(port_t port, unsigned long* byte);
//#else
//#define sys_inb_cnt(p,q) sys_inb(p,q)
//#endif

int sys_inb_cnt =0;




int kbd_test_scan(unsigned short assembly) {



    int ipc_status, r, irq_set;
    int isSecondByte=0;

    unsigned long code=0;

    message msg;

    irq_set = kbd_subscribe_int();


	while (code!=ESC) {

			if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
				printf("driver_receive failed with: %d", r);
				continue;
			}

			if (is_ipc_notify(ipc_status)) { /* received notification */
				switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

						if(code==FIRST_BYTE)
							isSecondByte=1;

						code=kbd_handler();
						if(code!=FIRST_BYTE)
							printcode(code,isSecondByte);

						isSecondByte=0;
					}
					break;
				default:
					break;
				}
			} else {
			}
	}
	unsigned long stat;

	sys_inb(STAT_REG, &stat);

	if (stat & OBF){
		sys_inb(OUT_BUF, &code);
	}

	kbd_unsubscribe_int();



	return Ok;
}

int kbd_test_scan_c(){



	return Ok;
}

int kbd_test_scan_assembly(){



	return Ok;
}



int kbd_test_poll() {


	return Ok;

}
int kbd_test_timed_scan(unsigned short n) {
	/* To be completed */
	return Ok;
}

/*
int sys_inb_cnt(port_t port, unsigned long* byte){
	sys_inb(port,byte);
	sys_inb_cnt++;


}


*/
