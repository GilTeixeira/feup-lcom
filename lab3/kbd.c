#include "i8042.h"
#include "i8254.h"
#include <limits.h>
#include <string.h>
#include <errno.h>

int hook_id = 1;

int kbd_subscribe_int(void) {

	int temp_hook_id = hook_id;

	sys_irqsetpolicy(KBD_IRQ, IRQ_EXCLUSIVE |IRQ_REENABLE, &hook_id);
	sys_irqenable(&hook_id);

	return BIT(temp_hook_id);
}

int kbd_unsubscribe_int() { //the order we disable and remove the policy must be done on the opposite way we make in subscribe_int
	int i, j;

	i=sys_irqdisable(&hook_id);
	j=sys_irqrmpolicy(&hook_id);
	printf("%d %d",i,j);

	return Ok;
}




unsigned long readcode() {
	unsigned long stat, code;

	while (1) {
		sys_inb(STAT_REG, &stat);

		if (stat & OBF) {

			/* assuming it returns OK */
			/*	loop while 8042 input buffer is not empty	*/
			if ((stat & IBF) == 0) {
				sys_inb(OUT_BUF, &code);

				return code;
			}
		}
		//delay(WAIT_KBC);
	}

}


int printcode(unsigned long code, int isSecondByte){
	int msb = code & BIT(7);

	if(code ==FIRST_BYTE)
		return Ok;



	if (msb == 0){
		if(isSecondByte)
			printf("Make Code:  0xe0 0x%02x\n", code);
		else
		printf("Make Code:  0x%02x\n", code);
	}

	else{
		if(isSecondByte)
			printf("Break Code: 0xe0 0x%02x\n", code);
		else
		printf("Break Code: 0x%02x\n", code);
	}


	return Ok;
}

int kbd_handler() {

	return readcode();

}


