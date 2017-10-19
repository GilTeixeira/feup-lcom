#include <string.h>
#include "i8024.h"




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



	if(assembly==0){
		kbd_test_scan_c();

		printf("Makecode: %d",makecode);
		printf("Breakcode: %d",breakcode);


	}
	/*else {kbd_test_scan_assembly();*/


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
	return 0;
}

int kbd_test_scan_c(){



	return 0;
}

int kbd_test_scan_assembly(){



	return 0;
}


int readcode(){}
int kbd_test_poll() {


	return 0;

}
int kbd_test_timed_scan(unsigned short n) {
	/* To be completed */
	return 0;
}
