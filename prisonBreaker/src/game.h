#pragma once


typedef enum {
    PLAYING, WIN, LOSE
} Result;


typedef struct {
	short result;
	long timePerPlay;

} Game;

Game* initGame();
void gameHandler(Game* game);
void stopGame(Game* game);
