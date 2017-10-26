#include <minix/syslib.h>
#include <minix/driver.h>
#include "i8042.h"
#include "i8254.h"
#include "kbd.h"
#include "timer.h"
#include <limits.h>
#include <string.h>
#include <errno.h>



int sys_inb_counter =0;




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

	sys_inb_cnt(STAT_REG, &stat);

	if (stat & OBF){
		sys_inb_cnt(OUT_BUF, &code);
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

	int isSecondByte = 0;

	unsigned long code = 0;

	while (code != ESC) {
		//printf("jlfdsljkdfs\n");

		if (code == FIRST_BYTE)
			isSecondByte = 1;

		//printf("jlfdsljkdfs\n");

		code = polling();
		//printf("jlfdsljkdfs\n");

		if (code != FIRST_BYTE)
			printcode(code, isSecondByte);

		isSecondByte = 0;
	}

	WriteCommandByte(KBC_CMD_REG, READ_COMM_BYTE);
	unsigned long ComByte= ReadCommandByte();

	ComByte|=ENABLE_KBD_INT;


	WriteCommandByte(KBC_CMD_REG, WRITE_COMM_BYTE);
	WriteCommandByte(OUT_BUF, ComByte);

	return Ok;

}
int kbd_test_timed_scan(unsigned short n) {


    int ipc_status, r, irq_set_timer, irq_set_kbd;
    int isSecondByte=0;

    int counter=0;

    unsigned long code=0;

    message msg;

    irq_set_kbd = kbd_subscribe_int();
    irq_set_timer = timer_subscribe_int();



	while (code!=ESC && counter!=60*n) {

			if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
				printf("driver_receive failed with: %d", r);
				continue;
			}

			if (is_ipc_notify(ipc_status)) { /* received notification */
				switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.NOTIFY_ARG & irq_set_kbd) { /* subscribed interrupt */

						if(code==FIRST_BYTE)
							isSecondByte=1;

						code=kbd_handler();
						if(code!=FIRST_BYTE)
							printcode(code,isSecondByte);

						isSecondByte=0;

						counter=0;


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
	unsigned long stat;

	sys_inb(STAT_REG, &stat);

	if (stat & OBF){
		sys_inb(OUT_BUF, &code);
	}


	timer_unsubscribe_int();
	kbd_unsubscribe_int();

	return Ok;
}


int sys_inb_cnt(port_t port, unsigned long* byte){
	sys_inb_counter++;

	return sys_inb(port,byte);


}


