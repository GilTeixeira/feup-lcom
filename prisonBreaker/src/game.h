#pragma once


typedef enum {
    PLAYING, WIN, LOSE
} Result;


typedef struct {
	short level;
	short result;
	long timePerPlay;
	Level** levels;


} Game;

Game* initGame();
void gameHandler(Game* game);
void stopGame(Game* game);
