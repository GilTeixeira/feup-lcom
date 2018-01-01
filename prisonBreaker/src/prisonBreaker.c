#include <minix/drivers.h>

#include "video_gr.h"
#include "kbd.h"
#include "game.h"
#include "mouse.h"


#include "prisonBreaker.h"

#include "bitmap.h"


//const int FPS = 25;
//const int mouseFPSmult = 3;



PrisonBreaker* initPrisonBreaker() {
	PrisonBreaker* prisonBreaker = (PrisonBreaker*) malloc(
			sizeof(PrisonBreaker));

	//subscribe devices
	prisonBreaker->IRQ_SET_KBD = kbd_subscribe_int();
	prisonBreaker->IRQ_SET_TIMER = timer_subscribe_int();
	prisonBreaker->IRQ_SET_MOUSE = mouse_subscribe_int();

	enable_stream_mode();


	//fundo

	//prisonBreaker->circle=loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/circle.bmp");
	//prisonBreaker->win=loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/win.bmp");
	//prisonBreaker->lose=loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/lose.bmp");

	//prisonBreaker->done = 0;
	prisonBreaker->draw = 1;
	prisonBreaker->scancode = 0;

	prisonBreaker->timer = initTimer();
	prisonBreaker->mouse = initMouse();

	prisonBreaker->gameState = initGameState();

	//deslocamento
	//prisonBreaker->deslX=0;



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
				gameStateUpdateKeyboard(prisonBreaker->gameState, prisonBreaker->scancode,  prisonBreaker->timer, prisonBreaker->mouse);
				//gameUpdateKeyboard(prisonBreaker->game,prisonBreaker->scancode);
			}
			if (msg.NOTIFY_ARG & prisonBreaker->IRQ_SET_TIMER) { /* timer subscribed interrupt */
				timerHandler(prisonBreaker->timer);
				//gameUpdate(prisonBreaker->game,prisonBreaker->timer);
				gameStateUpdate(prisonBreaker->gameState, prisonBreaker->timer, prisonBreaker->mouse);
				prisonBreaker->draw = 1;
			}
			if (msg.NOTIFY_ARG & prisonBreaker->IRQ_SET_MOUSE) { /* timer subscribed interrupt */
				mouseHandler(prisonBreaker->mouse);
				gameStateUpdateMouse(prisonBreaker->gameState, prisonBreaker->mouse);
			//	printf("Mouse interrupt");


			}

			break;
		default:
			break;
		}
	}


	//prisonBreaker->done =
	//if (prisonBreaker->scancode != 0) {
//		if (prisonBreaker->scancode == KEY_ESC)
//			prisonBreaker->done = 1;
		//if (prisonBreaker->scancode == KEY_D)
		//	if(prisonBreaker->game->result==PLAYING)
			//		prisonBreaker->game->result = WIN;
//	}






}

void drawPrisonBreaker(PrisonBreaker* prisonBreaker) {
	displayGameState(prisonBreaker->gameState, prisonBreaker->timer);
	//displayGame(prisonBreaker->game);
	//drawBitmap(prisonBreaker->fundo,0,0,ALIGN_LEFT);
	//drawBitmap(prisonBreaker->circle,361+prisonBreaker->deslX,262,ALIGN_LEFT);

}

void stopPrisonBreaker(PrisonBreaker* prisonBreaker) {
	kbd_unsubscribe_int();
	timer_unsubscribe_int();
	mouse_unsubscribe_int();

	stopTimer(prisonBreaker->timer);
	stopMouse(prisonBreaker->mouse);
	stopGameState(prisonBreaker->gameState);

	free(prisonBreaker);

}

