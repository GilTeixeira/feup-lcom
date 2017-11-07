#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/sysutil.h>
#include <minix/driver.h>
#include <minix/drivers.h>
#include "i8042.h"
#include "i8254.h"
#include "mouse.h"
#include "kbd.h"


int hook_id_mouse = 12;
unsigned long packet[3];
int mouse_counter=0;
int fullPacket=0;

int mouse_subscribe_int(void) {

	int temp_hook_id_mouse = hook_id_mouse;

	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_EXCLUSIVE | IRQ_REENABLE,
			&hook_id_mouse)!=Ok)
		return IRQ_MOUSE_SET_ERROR;

	if (sys_irqenable(&hook_id_mouse) != Ok)
		return IRQ_MOUSE_ENAB_ERROR;

	return BIT(temp_hook_id_mouse);


}

int mouse_unsubscribe_int() {

	if (sys_irqdisable(&hook_id_mouse) != Ok)
		return IRQ_MOUSE_DISAB_ERROR;

	if (sys_irqrmpolicy(&hook_id_mouse) != Ok)
		return IRQ_MOUSE_REM_ERROR;

	return Ok;
}

unsigned long readByte() {
	unsigned long stat, byte;

	while (1) {
		if (sys_inb(STAT_REG, &stat) != Ok)
			return KBD_SYS_IN_ERROR;

		if (stat & OBF) {
			if ((stat & (PAR_ERR | TO_ERR | IBF)) == 0) {
				if (sys_inb(OUT_BUF, &byte) != Ok)
					return KBD_SYS_IN_ERROR;

				return byte;
			}
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}

}

void mouse_handler() {
	unsigned long byte_read = readByte();

	switch (mouse_counter) {
	case 0:
		if (byte_read & BIT(3)) {
			packet[mouse_counter] = byte_read;
			mouse_counter++;
			fullPacket = 0;
		}

		break;

	case 1:
		packet[mouse_counter] = byte_read;
		mouse_counter++;

		break;
	case 2:
		packet[mouse_counter] = byte_read;
		mouse_counter = 0;
		fullPacket = 1;
		break;
	}

}


int print_packets(){

	printf("%d",packet[0]);
	printf("%d",packet[1]);
	printf("%d",packet[2]);


	return 0;
}

int enable_stream_mode() {
		unsigned long ret;
		WriteCommandByte(0x64, 0xD4);
		WriteCommandByte(0x60, DISABLE_DR);
		while (ret != ack) {

			ret = readByte();
		}
		return Ok;


}
