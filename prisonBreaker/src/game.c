#include "game.h"
#include "timer.h"
#include "kbd.h"
#include "level.h"

#define KEY_TO_MOVE_UP      KEY_W
#define KEY_TO_MOVE_DOWN    KEY_S
#define KEY_TO_MOVE_LEFT    KEY_A
#define KEY_TO_MOVE_RIGHT   KEY_D

Game* initGame() {
	Game* game = (Game*) malloc(sizeof(Game));
	game->result = PLAYING;
	game->score = 1;
	game->currLevel = 0;

	game->timePerPlay = 5;

	initLevels(game);

	game->fundo = loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/fundo.bmp");

	game->square = initSquare();

	return game;

}

void gameHandler(Game* game) {

}

void stopGame(Game* game) {
	free(game);
}

void initLevels(Game* game) {

	game->levels = (Level**) malloc(NUMBEROFLEVELS * sizeof(Level*));

	/*******************
	 *     Level 1     *
	 ******************/

	Level * level1 = (Level*) malloc(sizeof(Level));

	level1->levelID = 1;

	level1->instruction = LEFT;

	level1->numAcceptedDirections = 1;
	level1->acceptedDirections = (short *) malloc(
			sizeof(short) * level1->numAcceptedDirections);
	level1->acceptedDirections[0] = LEFT_DIR;


	level1->instructionBitmap = loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/left2.bmp");

	game->levels[0] = level1;

	/*******************
	 *     Level 2     *
	 ******************/

	Level * level2 = (Level*) malloc(sizeof(Level));

	level2->levelID = 2;

	level2->instruction = RIGHT;

	level2->numAcceptedDirections = 1;
	level2->acceptedDirections = (short *) malloc(
			sizeof(short) * level2->numAcceptedDirections);

	level1->acceptedDirections[0] = RIGHT_DIR;

	level2->instructionBitmap = loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/left2.bmp");

	game->levels[1] = level2;

	/*******************
	 *     Level 3     *
	 *****************
	 levelID = 3;

	 Level * level3 = (Level*) malloc(sizeof(Level));

	 level3->numAcceptedDirections = levelID;

	 level3->instruction = UP;

	 level3->acceptedDirections[0] = UP_DIR;
	 level3->numAcceptedDirections = 1;

	 /*******************
	 *     Level 4     *
	 *****************
	 levelID = 4;

	 Level * level4 = (Level*) malloc(sizeof(Level));

	 level4->numAcceptedDirections = levelID;

	 level4->instruction = DOWN;

	 level4->acceptedDirections[0] = DOWN_DIR;
	 level4->numAcceptedDirections = 1;
	 */
}

void gameUpdate(Game* game, Timer* timer) {

	switch (game->result) {

	case PLAYING:
		if (timer->counter == 3) //check Nothing
			game->result = LOSE;

	case WAITING:
		updateSquare(game->square);
		break;

	case LOSE:
		//statement(s);
		break;

	}

	//if (prisonBreaker->game->result == PLAYING) {

	//} else if (prisonBreaker->game->result == WIN)
	//	if (prisonBreaker->deslX != 200)
	//	prisonBreaker->deslX++;

}

void gameUpdateKeyboard(Game* game, unsigned long scancode) {
	Level* currentLevel = game->levels[game->currLevel];
	short dir = getDirectionFromKey(scancode);
	printf("dir: %d, scan: %d\n", dir, scancode);

	if (game->result == PLAYING) {
		printf("chaega\n");
		if (isAcceptedDirection(currentLevel, dir)){
			printf("blabla\n");
			game->result = WAITING;
			game->square->direction = dir;
		}
	}

//if()

//gameUpdateKeyboard(prisonBreaker->game,prisonBreaker->scancode)

}

void displayGame(Game* game) {
	drawBitmap(game->fundo, 0, 0, ALIGN_LEFT);
	displayLevel(game->levels[game->currLevel]);
	displaySquare(game->square);

}

void selectNextLevel(Game* game) {
	int nextLevel = rand() % NUMBEROFLEVELS + 1; //random number between 1-NUMBEROFLEVELS

	game->score++;
	game->currLevel = nextLevel;

}

short getDirectionFromKey(unsigned long scancode) {
	if (scancode == KEY_TO_MOVE_LEFT)
		return LEFT_DIR;

	if (scancode == KEY_TO_MOVE_RIGHT)
		return RIGHT_DIR;

	if (scancode == KEY_TO_MOVE_UP)
		return UP_DIR;

	if (scancode == KEY_TO_MOVE_DOWN)
		return DOWN_DIR;

	return INVALID_DIR;

}

void freeGameLevels(Game* game) {
	int i;
	//freeLevel(game->levels[0]);
	freeLevel(game->levels[1]);
	//for (i = 0; i < NUMBEROFLEVELS; ++i) {
	//	freeLevel(game->levels[i]);
	//}
	free(game->levels);

}

void freeGame(Game* game) {

	freeGameLevels(game);
	freeSquare(game->square);
	deleteBitmap(game->fundo);

	//free(game);

}
