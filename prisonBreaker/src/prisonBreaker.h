#pragma once

#include "bitmap.h"
#include "timer.h"
#include "game.h"
#include "gameState.h"

typedef struct {
	int IRQ_SET_KBD;
	int IRQ_SET_TIMER;

	//Bitmap* fundo;
	//Bitmap* circle;
	//Bitmap* win;
	//Bitmap* lose;

	int done, draw;
	unsigned long scancode;
	Timer* timer;

	//short deslX;
	GameState* gameState;
	//Game* game;
} PrisonBreaker;

PrisonBreaker* initPrisonBreaker();
void updatePrisonBreaker(PrisonBreaker* prisonBreaker);
void drawPrisonBreaker(PrisonBreaker* prisonBreaker);
void stopPrisonBreaker(PrisonBreaker* prisonBreaker);

