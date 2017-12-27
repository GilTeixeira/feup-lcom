#pragma once

#include "level.h"
#include "square.h"

#define NUMBEROFLEVELS 15

typedef enum {
    LEFT_DIR, RIGHT_DIR, UP_DIR, DOWN_DIR, NOTHING_DIR
} Direction;


typedef enum {
    PLAYING, WAITING, LOSE
} Result;


typedef struct {
	short currLevel;
	short score;
	short result;
	long timePerPlay;
	Level* levels[NUMBEROFLEVELS];

	Square* square;

	Bitmap* fundo;

} Game;

Game* initGame();
void gameHandler(Game* game);
void stopGame(Game* game);
void initLevels(Game* game);

short getDirectionFromKey(unsigned long scancode);
