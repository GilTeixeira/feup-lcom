#include "i8042.h"
#include "i8254.h"
#include <limits.h>
#include <string.h>
#include <errno.h>


int kbd_subscribe_int(void) {

	int temp_hook_id = hook_id;

	sys_irqsetpolicy(TIMER0_IRQ, IRQ_EXCLUSIVE |IRQ_REENABLE, &hook_id);
	sys_irqenable(&hook_id);

	return BIT(temp_hook_id);
}

int kbd_unsubscribe_int() { //the order we disable and remove the policy must be done on the opposite way we make in subscribe_int

	sys_irqdisable(&hook_id);
	sys_irqrmpolicy(&hook_id);

	return Ok;
}

int kbd_test_scan(unsigned short assembly) {

	int irq_set;

	if(assembly==0){
		kbd_test_scan_c();

		printf("Makecode: %d",makecode);
		printf("Breakcode: %d",breakcode);


	}
	/*else {kbd_test_scan_assembly();*/


	while () {

			if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
				printf("driver_receive failed with: %d", r);
				continue;
			}

			if (is_ipc_notify(ipc_status)) { /* received notification */
				switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

//até aqui está bem
						timer_int_handler();
						if (counter % 60 == 0) {
							printf("\n Seconds passed: %d ", counter / 60);
							break;
						}
					}
					break;
				default:
					break;
				}
			} else {
			}
		}

//usar variaveis entre c e assembly
/**
 * @brief To test reading of scancode via KBD interrupts
 *
 * Displays the scancodes received from the keyboard
 *
 *
 * Exits upon release of the ESC key
 *
 * @param asm Which IH to use: if 0, in C, otherwise in assembly
 *
*/
/*0x81 - ESC */

//numlock_on,capslock_on,scrolllock_on
	return Ok;
}

int kbd_test_scan_c(){



	return Ok;
}

int kbd_test_scan_assembly(){



	return Ok;
}


int readcode(){}
int kbd_test_poll() {


	return Ok;

}
int kbd_test_timed_scan(unsigned short n) {
	/* To be completed */
	return Ok;
}
