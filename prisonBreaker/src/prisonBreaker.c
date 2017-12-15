#include <minix/drivers.h>

#include "video_gr.h"
#include "kbd.h"
#include "game.h"


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
	prisonBreaker->fundo=loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/fundo.bmp");

	prisonBreaker->done = 0;
	prisonBreaker->draw = 1;
	prisonBreaker->scancode = 0;

	prisonBreaker->timer = initTimer();

	//Game
	prisonBreaker->game = initGame();

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
				timerHandler(prisonBreaker->timer);
				if(prisonBreaker->timer->counter==6)
					prisonBreaker->game->result=LOSE;


			}

			break;
		default:
			break;
		}
	}

	if (prisonBreaker->scancode != 0) {
		if (prisonBreaker->scancode == KEY_ESC)
			prisonBreaker->done = 1;
		if (prisonBreaker->scancode == KEY_D)
					prisonBreaker->game->result = WIN;
	}




}

void drawPrisonBreaker(PrisonBreaker* prisonBreaker) {


	drawBitmap(prisonBreaker->fundo,0,0,ALIGN_LEFT);
	draw_square(1, 1, 20, 0);

}

void stopPrisonBreaker(PrisonBreaker* prisonBreaker) {
	kbd_unsubscribe_int();
	timer_unsubscribe_int();

	stopTimer(prisonBreaker->timer);

	free(prisonBreaker);

}

