#include <minix/drivers.h>

#include "video_gr.h"
#include "kbd.h"

#include "prisonBreaker.h"

const int FPS = 25;

PrisonBreaker* initPrisonBreaker() {
	PrisonBreaker* prisonBreaker = (PrisonBreaker*) malloc(
			sizeof(PrisonBreaker));

	//subscribe devices
	prisonBreaker->IRQ_SET_KBD = kbd_subscribe_int();

	prisonBreaker->done = 0;
	prisonBreaker->draw = 1;
	prisonBreaker->scancode = 0;

	return prisonBreaker;
}

void updatePrisonBreaker(PrisonBreaker* prisonBreaker) {

	int ipc_status, r;

	message msg;

	if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
		printf("driver_receive failed with: %d", r);
		return;
	}

	if (is_ipc_notify(ipc_status)) { /* received notification */
		switch (_ENDPOINT_P(msg.m_source)) {
		case HARDWARE: /* hardware interrupt notification */
			if (msg.NOTIFY_ARG & prisonBreaker->IRQ_SET_KBD) { /* subscribed interrupt */
				kbd_handler();
				prisonBreaker->scancode = globalCode;
			}
			break;
		default:
			break;
		}
	}

	if (prisonBreaker->scancode != 0) {
		if (prisonBreaker->scancode == KEY_ESC)
			prisonBreaker->done = 1;
	}

}

void drawPrisonBreaker(PrisonBreaker* prisonBreaker) {

	draw_square(1, 1, 200, 0xFFFFFF);

}

void stopPrisonBreaker(PrisonBreaker* prisonBreaker) {
	kbd_unsubscribe_int();
	free(prisonBreaker);

}

