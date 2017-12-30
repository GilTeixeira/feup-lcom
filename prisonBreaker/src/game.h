#pragma once

#include "level.h"
#include "square.h"
#include "timer.h"


// TO DO change for 15
#define NUMBEROFLEVELS 2

typedef enum {
    LEFT_DIR, RIGHT_DIR, UP_DIR, DOWN_DIR, NOTHING_DIR, INVALID_DIR
} Direction;


typedef enum {
    PLAYING, WAITING, LOSE
} Result;


typedef struct {
	short currLevel;
	short score;
	short result;
	long timePerPlay;
	Level** levels;

	Square* square;

	Bitmap* fundo;

} Game;

Game* initGame();
void gameHandler(Game* game);
void stopGame(Game* game);
void initLevels(Game* game);

void gameUpdate(Game* game, Timer* timer);

void gameUpdateKeyboard(Game* game, unsigned long scancode);
void displayGame(Game* game);
void selectNextLevel(Game* game);
void freeGameLevels(Game* game);
void freeGame(Game* game);

short getDirectionFromKey(unsigned long scancode);
