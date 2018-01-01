#pragma once

#include "game.h"
#include "kbd.h"
//#include "bitmap.h"


typedef enum {
    MAINMENU, LOSEMENU, GAME
} State;





typedef struct {
	short currState;

	Game * game;

	int done;

	Bitmap* LoseMenuBitmap;
	Bitmap* MainMenuBitmap;

} GameState;

GameState* initGameState();
//void gameHandler(GameState* gameState);
void stopGameState(GameState* gameState);

void displayGameState(GameState* gameState);

void stopGameState(GameState* gameState);
void gameStateUpdateKeyboard(GameState* gameState, unsigned long scancode);
void gameStateUpdate(GameState* gameState, Timer* timer);
