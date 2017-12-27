#pragma once

#include "level.h"
#include "square.h"


typedef enum {
    PLAYING, WAITING, LOSE
} Result;


typedef struct {
	short level;
	short result;
	long timePerPlay;
	Level** levels;

	Square* square;


} Game;

Game* initGame();
void gameHandler(Game* game);
void stopGame(Game* game);
void initLevels(Game* game);
