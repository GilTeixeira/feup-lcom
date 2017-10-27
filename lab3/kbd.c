#include "kbd.h"



int hook_id_kbd = 1;



int kbd_subscribe_int(void) {

	int temp_hook_id_kbd = hook_id_kbd;

	if(sys_irqsetpolicy(KBD_IRQ, IRQ_EXCLUSIVE | IRQ_REENABLE, &hook_id_kbd)!=Ok)
		return IRQ_KBD_SET_ERROR;

	if(sys_irqenable(&hook_id_kbd)!=Ok)
		return IRQ_KBD_ENAB_ERROR;

	return BIT(temp_hook_id_kbd);
}

int kbd_unsubscribe_int() { //the order we disable and remove the policy must be done on the opposite way we make in subscribe_int

	if (sys_irqdisable(&hook_id_kbd) != Ok)
		return IRQ_KBD_DISAB_ERROR;

	if (sys_irqrmpolicy(&hook_id_kbd) != Ok)
		return IRQ_KBD_REM_ERROR;

	return Ok;
}

unsigned long readCode() {
	unsigned long stat, code;

	while (1) {
		sys_inb_cnt(STAT_REG, &stat);

		if (stat & OBF) {

			/* assuming it returns OK */
			/*	loop while 8042 input buffer is not empty	*/
			if ((stat & IBF) == 0) {
				sys_inb_cnt(OUT_BUF, &code);

				return code;
			}
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}

}

unsigned long polling() {
	unsigned long stat, code;

	while (1) {
		sys_inb_cnt(STAT_REG, &stat);
		//printf("%d \n", stat);
		//

		//stat= 0010.1001

		if (stat & OBF && ((stat & AUX) == 0)) {
			//printf("2\n");

			/* assuming it returns OK */
			/*	loop while 8042 input buffer is not empty	*/
			if ((stat & IBF) == 0) {
				//printf("3\n");
				sys_inb_cnt(OUT_BUF, &code);

				return code;
			}
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int printcode(unsigned long code, int isSecondByte) {
	int msb = code & BIT(7);

	if (code == FIRST_BYTE)
		return Ok;

	if (msb == 0) {
		if (isSecondByte)
			printf("Make Code:  0xe0 0x%02x\n", code);
		else
			printf("Make Code:  0x%02x\n", code);
	}

	else {
		if (isSecondByte)
			printf("Break Code: 0xe0 0x%02x\n", code);
		else
			printf("Break Code: 0x%02x\n", code);
	}

	return Ok;
}

void kbd_handler() {
	globalCode = readCode();

}

int WriteCommandByte(unsigned long port, unsigned long cmd) {
	unsigned long stat;

	while (1) {
		sys_inb_cnt(STAT_REG, &stat); /* assuming it returns OK */
		/* loop while 8042 input buffer is not empty */
		if ((stat & IBF) == 0) {
			sys_outb(port, cmd); /* no args command */
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

unsigned long ReadCommandByte() {

	unsigned long stat, data;

	//It is not robust against failures in the KBC/keyboard

	while (1) {
		sys_inb_cnt(STAT_REG, &stat); /* assuming it returns OK */
		/* loop while 8042 output buffer is empty */
		if (stat & OBF) {
			sys_inb_cnt(OUT_BUF, &data); /* assuming it returns OK */
			if ((stat & (PAR_ERR | TO_ERR)) == 0)
				return data;
			else
				return -1;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

