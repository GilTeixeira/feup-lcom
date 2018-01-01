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

void displayGameState(GameState* gameState, Timer* timer);

void stopGameState(GameState* gameState);
void gameStateUpdateKeyboard(GameState* gameState, unsigned long scancode, Timer* timer, Mouse* mouse);
void gameStateUpdate(GameState* gameState, Timer* timer, Mouse* mouse);
void gameStateUpdateMouse(GameState* gameState, Mouse* mouse);
