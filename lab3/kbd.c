#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/sysutil.h>
#include <minix/driver.h>
#include <minix/drivers.h>
#include "kbd.h"
#include "i8042.h"
#include "i8254.h"
#include "test3.h"

int hook_id_kbd = 1;

int kbd_subscribe_int(void) {

	int temp_hook_id_kbd = hook_id_kbd;

	if (sys_irqsetpolicy(KBD_IRQ, IRQ_EXCLUSIVE | IRQ_REENABLE,
			&hook_id_kbd)!=Ok)
		return IRQ_KBD_SET_ERROR;

	if (sys_irqenable(&hook_id_kbd) != Ok)
		return IRQ_KBD_ENAB_ERROR;

	return BIT(temp_hook_id_kbd);


}

int kbd_unsubscribe_int() {

	if (sys_irqdisable(&hook_id_kbd) != Ok)
		return IRQ_KBD_DISAB_ERROR;

	if (sys_irqrmpolicy(&hook_id_kbd) != Ok)
		return IRQ_KBD_REM_ERROR;

	return Ok;
}

unsigned long readCode() {
	unsigned long stat, code;

	while (1) {
		if (sys_inb_cnt(STAT_REG, &stat) != Ok)
			return KBD_SYS_IN_ERROR;

		if (stat & OBF) {
			if ((stat & (PAR_ERR | TO_ERR | IBF)) == 0) {
				if (sys_inb_cnt(OUT_BUF, &code) != Ok)
					return KBD_SYS_IN_ERROR;

				return code;
			}
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}

}

unsigned long polling() {
	unsigned long stat, code;

	while (1) {
		if (sys_inb_cnt(STAT_REG, &stat) != Ok)
			return KBD_SYS_IN_ERROR;

		if ((stat & OBF) && ((stat & AUX) == 0)) {
			if ((stat & (PAR_ERR | TO_ERR | IBF)) == 0) {
				if (sys_inb_cnt(OUT_BUF, &code) != Ok)
					return KBD_SYS_IN_ERROR;

				return code;
			}
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int printcode(unsigned long code, int isSecondByte) {
	int msb = code & BIT(7);

	if (code == KBD_SYS_IN_ERROR)
		printf("Error: Invalid Read Code\n");

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
		if (sys_inb_cnt(STAT_REG, &stat) != Ok)
			return KBD_SYS_IN_ERROR;

		if ((stat & IBF) == 0) {
			if (sys_outb(port, cmd) != Ok)
				return KBD_SYS_OUT_ERROR;
			return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

unsigned long ReadCommandByte() {

	unsigned long stat, data;

	while (1) {
		if (sys_inb_cnt(STAT_REG, &stat) != Ok)
			return KBD_IN_CMD_ERROR;
		if (stat & OBF) {
			if (sys_inb_cnt(OUT_BUF, &data) != Ok)
				return KBD_IN_CMD_ERROR;

			if ((stat & (PAR_ERR | TO_ERR)) == 0)
				return data;
			else
				return KBD_IN_CMD_ERROR;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}





