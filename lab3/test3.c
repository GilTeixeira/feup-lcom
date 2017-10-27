#include <minix/syslib.h>
#include <minix/driver.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "i8042.h"
#include "i8254.h"
#include "kbd.h"
#include "timer.h"

int sys_inb_counter = 0;
short codeAss;

int sys_inb_cnt(port_t port, unsigned long* byte) {
	sys_inb_counter++;
	return sys_inb(port, byte);
}

int kbd_test_scan(unsigned short assembly) {

	int ipc_status, r, irq_set;
	int isSecondByte = 0;
	unsigned long code = 0, stat;

	message msg;
	irq_set = kbd_subscribe_int();

	if (irq_set < 0)
		return KBD_SUB_ERROR;

	while (code != ESC) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

					if (code == FIRST_BYTE)
						isSecondByte = 1;

					if (assembly == 0) {
						kbd_handler();
						code = globalCode;
					} else {
						kbd_asm_handler();
						code = codeAss;
					}

					if (code != FIRST_BYTE)
						printcode(code, isSecondByte);

					isSecondByte = 0;
				}
				break;
			default:
				break;
			}
		} else {
		}
	}

	if (sys_inb_cnt(STAT_REG, &stat) != Ok)
		return KBD_TEST_SCAN_ERROR;

	if (stat & OBF) {
		if (sys_inb_cnt(OUT_BUF, &code) != Ok)
			return KBD_TEST_SCAN_ERROR;
	}

	if (kbd_unsubscribe_int() != 0)
		return KBD_UNSUB_ERROR;

	if (assembly == 0) {
		printf("\nNumber of sys_inb calls: %d\n", sys_inb_counter);

	}

	return Ok;
}

int kbd_test_poll() {

	int isSecondByte = 0;
	unsigned long code = 0;
	unsigned long ComByte;

	while (code != ESC) {

		if (code == FIRST_BYTE)
			isSecondByte = 1;

		code = polling();

		if (code == KBD_SYS_IN_ERROR)
			return KBD_POLLING_ERROR;

		if (code != FIRST_BYTE)
			printcode(code, isSecondByte);

		isSecondByte = 0;
	}

	if (WriteCommandByte(KBC_CMD_REG, READ_COMM_BYTE) != Ok)
		return KBD_WRITE_CMD_BYTE_ERROR;

	ComByte = ReadCommandByte();

	if (ComByte == KBD_IN_CMD_ERROR)
		return KBD_POLLING_ERROR;

	ComByte |= ENABLE_KBD_INT;

	if (WriteCommandByte(KBC_CMD_REG, WRITE_COMM_BYTE) != Ok)
		return KBD_WRITE_CMD_BYTE_ERROR;
	if (WriteCommandByte(OUT_BUF, ComByte) != Ok)
		return KBD_WRITE_CMD_BYTE_ERROR;

	printf("\nNumber of sys_inb calls: %d\n", sys_inb_counter);

	return Ok;

}

int kbd_test_timed_scan(unsigned short n) {

	int ipc_status, r, irq_set_timer, irq_set_kbd;
	int isSecondByte = 0;
	int counter = 0;
	unsigned long code = 0;
	unsigned long stat;

	message msg;

	irq_set_kbd = kbd_subscribe_int();
	if (irq_set_kbd < 0)
		return KBD_SUB_ERROR;

	irq_set_timer = timer_subscribe_int();
	if (irq_set_timer < 0)
		return TIMER_SUB_ERROR;

	while (code != ESC && counter != 60 * n) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_kbd) { /* subscribed interrupt */

					if (code == FIRST_BYTE)
						isSecondByte = 1;
					kbd_handler();
					code = globalCode;
					if (code != FIRST_BYTE)
						printcode(code, isSecondByte);

					isSecondByte = 0;

					counter = 0;

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

	if (kbd_unsubscribe_int() != Ok)
		return KBD_UNSUB_ERROR;

	return Ok;
}

