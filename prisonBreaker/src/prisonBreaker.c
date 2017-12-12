#include <minix/drivers.h>

#include "video_gr.h"
#include "kbd.h"

#include "prisonBreaker.h"

#include "bitmap.h"


const int FPS = 25;
const int mouseFPSmult = 3;



PrisonBreaker* initPrisonBreaker() {
	PrisonBreaker* prisonBreaker = (PrisonBreaker*) malloc(
			sizeof(PrisonBreaker));

	//subscribe devices
	prisonBreaker->IRQ_SET_KBD = kbd_subscribe_int();
	prisonBreaker->IRQ_SET_TIMER = timer_subscribe_int();


	//fundo
	prisonBreaker->fundo=loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/images/test.bmp");

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
			if (msg.NOTIFY_ARG & prisonBreaker->IRQ_SET_KBD) { /* keyboard interrupt */
				kbd_handler();
				prisonBreaker->scancode = globalCode;
			}
			if (msg.NOTIFY_ARG & prisonBreaker->IRQ_SET_KBD) { /* timer subscribed interrupt */

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
	drawBitmap(prisonBreaker->fundo,0,0,ALIGN_LEFT);

}

void stopPrisonBreaker(PrisonBreaker* prisonBreaker) {
	kbd_unsubscribe_int();
	timer_unsubscribe_int();
	free(prisonBreaker);

}

