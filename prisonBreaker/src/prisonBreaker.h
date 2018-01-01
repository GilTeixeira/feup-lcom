#pragma once

#include "bitmap.h"
#include "timer.h"
#include "mouse.h"
#include "game.h"
#include "gameState.h"

typedef struct {
	int IRQ_SET_KBD;
	int IRQ_SET_TIMER;
	int IRQ_SET_MOUSE;

	//Bitmap* fundo;
	//Bitmap* circle;
	//Bitmap* win;
	//Bitmap* lose;

	int done, draw;
	unsigned long scancode;
	Timer* timer;
	Mouse* mouse;

	//short deslX;
	GameState* gameState;
	//Game* game;
} PrisonBreaker;

PrisonBreaker* initPrisonBreaker();
void updatePrisonBreaker(PrisonBreaker* prisonBreaker);
void drawPrisonBreaker(PrisonBreaker* prisonBreaker);
void stopPrisonBreaker(PrisonBreaker* prisonBreaker);

