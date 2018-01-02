#include "game.h"
#include "timer.h"
#include "kbd.h"
#include "level.h"

#define TIMEPERPLAY      1

#define KEY_TO_MOVE_UP      KEY_W
#define KEY_TO_MOVE_DOWN    KEY_S
#define KEY_TO_MOVE_LEFT    KEY_A
#define KEY_TO_MOVE_RIGHT   KEY_D

#define MIN_MOUSE_MOVEMENT  1000

#define BAR_X_COORD_START    25
#define BAR_X_COORD_END      275
#define BAR_Y_COORD   490

Game* initGame() {
	Game* game = (Game*) malloc(sizeof(Game));
	game->result = PLAYING;
	game->score = 0;
	game->currLevel = 0;

	game->timePerPlay = TIMEPERPLAY;

	initLevels(game);

	game->fundo = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/fundo.bmp");
	//game->lose = loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/lose.bmp");

	game->square = initSquare();

	game->timeBar = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/barra.bmp");

	return game;

}

void initBeginnerLevels(Game* game) {

	/***********************
	 *     Level 1  - UP   *
	 ***********************/

	Level * level1 = (Level*) malloc(sizeof(Level));

	level1->levelID = 1;

	level1->instruction = UP;

	level1->numAcceptedDirections = 1;
	level1->acceptedDirections = (short *) malloc(
			sizeof(short) * level1->numAcceptedDirections);
	level1->acceptedDirections[0] = UP_DIR;

	level1->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/up.bmp");

	game->levels[0] = level1;

	/***********************
	 *   Level 1  - DOWN   *
	 ***********************/

	Level * level2 = (Level*) malloc(sizeof(Level));

	level2->levelID = 2;

	level2->instruction = DOWN;

	level2->numAcceptedDirections = 1;
	level2->acceptedDirections = (short *) malloc(
			sizeof(short) * level2->numAcceptedDirections);

	level2->acceptedDirections[0] = DOWN_DIR;

	level2->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/down.bmp");

	game->levels[1] = level2;

	/***********************
	 *   Level 3 - LEFT    *
	 ***********************/

	//TODO: Change BITMAP
	Level * level3 = (Level*) malloc(sizeof(Level));

	level3->levelID = 3;

	level3->instruction = LEFT;

	level3->numAcceptedDirections = 1;
	level3->acceptedDirections = (short *) malloc(
			sizeof(short) * level3->numAcceptedDirections);

	level3->acceptedDirections[0] = LEFT_DIR;

	level3->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/left.bmp");

	game->levels[2] = level3;

	/*********************
	 *  Level 4 - RIGHT  *
	 *********************/

	//TODO: Change BITMAP
	Level * level4 = (Level*) malloc(sizeof(Level));

	level4->levelID = 4;

	level4->instruction = RIGHT;

	level4->numAcceptedDirections = 1;
	level4->acceptedDirections = (short *) malloc(
			sizeof(short) * level4->numAcceptedDirections);

	level4->acceptedDirections[0] = RIGHT_DIR;

	level4->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/right.bmp");

	game->levels[3] = level4;

}

void initNormalLevels(Game* game) {

	/***********************
	 *     Level 5  - NOT UP   *
	 ***********************/

	Level * level5 = (Level*) malloc(sizeof(Level));

	level5->levelID = 5;

	level5->instruction = NOT_UP;

	level5->numAcceptedDirections = 3;
	level5->acceptedDirections = (short *) malloc(
			sizeof(short) * level5->numAcceptedDirections);

	level5->acceptedDirections[0] = DOWN_DIR;
	level5->acceptedDirections[1] = LEFT_DIR;
	level5->acceptedDirections[2] = RIGHT_DIR;

	level5->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/up.bmp");

	game->levels[4] = level5;

	/***********************
	 *   Level 6  - NOT DOWN   *
	 ***********************/

	Level * level6 = (Level*) malloc(sizeof(Level));

	level6->levelID = 6;

	level6->instruction = NOT_DOWN;

	level6->numAcceptedDirections = 3;
	level6->acceptedDirections = (short *) malloc(
			sizeof(short) * level6->numAcceptedDirections);

	level6->acceptedDirections[0] = UP_DIR;
	level6->acceptedDirections[2] = LEFT_DIR;
	level6->acceptedDirections[3] = RIGHT_DIR;

	level6->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/down.bmp");

	game->levels[5] = level6;

	/***********************
	 *   Level 7 - NOT LEFT    *
	 ***********************/

	//TODO: Change BITMAP
	Level * level7 = (Level*) malloc(sizeof(Level));

	level7->levelID = 7;

	level7->instruction = NOT_LEFT;

	level7->numAcceptedDirections = 3;
	level7->acceptedDirections = (short *) malloc(
			sizeof(short) * level7->numAcceptedDirections);

	level7->acceptedDirections[0] = UP_DIR;
	level7->acceptedDirections[1] = DOWN_DIR;
	level7->acceptedDirections[2] = RIGHT_DIR;

	level7->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/left.bmp");

	game->levels[6] = level7;

	/*********************
	 *  Level 8 - NOT RIGHT  *
	 *********************/

	//TODO: Change BITMAP
	Level * level8 = (Level*) malloc(sizeof(Level));

	level8->levelID = 8;

	level8->instruction = NOT_RIGHT;

	level8->numAcceptedDirections = 3;
	level8->acceptedDirections = (short *) malloc(
			sizeof(short) * level8->numAcceptedDirections);

	level8->acceptedDirections[0] = UP_DIR;
	level8->acceptedDirections[1] = DOWN_DIR;
	level8->acceptedDirections[2] = LEFT_DIR;

	level8->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/right.bmp");

	game->levels[7] = level8;

}

void initAdvancedLevels(Game* game) {

	/***********************
	 *     Level 1  - NOT NOT UP   *
	 ***********************/

	Level * level9 = (Level*) malloc(sizeof(Level));

	level9->levelID = 9;

	level9->instruction = NOT_NOT_UP;

	level9->numAcceptedDirections = 1;
	level9->acceptedDirections = (short *) malloc(
			sizeof(short) * level9->numAcceptedDirections);
	level9->acceptedDirections[0] = UP_DIR;

	level9->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/up.bmp");

	game->levels[8] = level9;

	/***********************
	 *     Level 1  - NOT NOT DOWN   *
	 ***********************/

	Level * level10 = (Level*) malloc(sizeof(Level));

	level10->levelID = 10;

	level10->instruction = NOT_NOT_DOWN;

	level10->numAcceptedDirections = 1;
	level10->acceptedDirections = (short *) malloc(
			sizeof(short) * level10->numAcceptedDirections);

	level10->acceptedDirections[0] = DOWN_DIR;

	level10->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/down.bmp");

	game->levels[9] = level10;

	/*******************
	 *     Level 3 NOT NOT LEFT    *
	 ******************/

	//TODO: Change BITMAP
	Level * level11 = (Level*) malloc(sizeof(Level));

	level11->levelID = 11;

	level11->instruction = NOT_NOT_LEFT;

	level11->numAcceptedDirections = 1;
	level11->acceptedDirections = (short *) malloc(
			sizeof(short) * level11->numAcceptedDirections);

	level11->acceptedDirections[0] = LEFT_DIR;

	level11->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/left.bmp");

	game->levels[10] = level11;

	/*******************
	 *     Level 4  NOT NOT RIGHT    *
	 ******************/

	//TODO: Change BITMAP
	Level * level12 = (Level*) malloc(sizeof(Level));

	level12->levelID = 12;

	level12->instruction = NOT_NOT_RIGHT;

	level12->numAcceptedDirections = 1;
	level12->acceptedDirections = (short *) malloc(
			sizeof(short) * level12->numAcceptedDirections);

	level12->acceptedDirections[0] = RIGHT_DIR;

	level12->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/right.bmp");

	game->levels[11] = level12;

}

void initExpertLevels(Game* game) {

	/***********************
	 *     Level 1  - NOTHING  *
	 ***********************/

	Level * level13 = (Level*) malloc(sizeof(Level));

	level13->levelID = 13;

	level13->instruction = NOTHING;

	level13->numAcceptedDirections = 1;
	level13->acceptedDirections = (short *) malloc(
			sizeof(short) * level13->numAcceptedDirections);
	level13->acceptedDirections[0] = NOTHING_DIR;

	level13->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/up.bmp");

	game->levels[12] = level13;

	/***********************
	 *     Level 1  - NOT NOTHING   *
	 ***********************/

	Level * level14 = (Level*) malloc(sizeof(Level));

	level14->levelID = 14;

	level14->instruction = NOT_NOTHING;

	level14->numAcceptedDirections = 4;
	level14->acceptedDirections = (short *) malloc(
			sizeof(short) * level14->numAcceptedDirections);

	level14->acceptedDirections[0] = UP_DIR;
	level14->acceptedDirections[1] = DOWN_DIR;
	level14->acceptedDirections[2] = LEFT_DIR;
	level14->acceptedDirections[3] = RIGHT_DIR;

	level14->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/down.bmp");

	game->levels[13] = level14;

	/*******************
	 *     Level 3 NOT NOT NOTHING    *
	 ******************/

	//TODO: Change BITMAP
	Level * level15 = (Level*) malloc(sizeof(Level));

	level15->levelID = 15;

	level15->instruction = NOT_NOT_NOTHING;

	level15->numAcceptedDirections = 1;
	level15->acceptedDirections = (short *) malloc(
			sizeof(short) * level15->numAcceptedDirections);

	level15->acceptedDirections[0] = NOTHING_DIR;

	level15->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/left.bmp");

	game->levels[14] = level15;

}

void initLevels(Game* game) {

	game->levels = (Level**) malloc(NUMBEROFLEVELS * sizeof(Level*));

	initBeginnerLevels(game);
	initNormalLevels(game);
	initAdvancedLevels(game);
	initExpertLevels(game);

}

void gameUpdate(Game* game, Timer* timer, Mouse* mouse) {

	switch (game->result) {

	case PLAYING:
		if (timer->counter == game->timePerPlay) {
			Level* currentLevel = game->levels[game->currLevel];
			if (!isAcceptedDirection(currentLevel, NOTHING_DIR)) {
				game->result = LOSE;
			} else {
				selectNextLevel(game);
				resetMouse(mouse);
				resetTimer(timer);

			}

		}
		break;
	case WAITING:
		updateSquare(game->square);
		if (hasFinishedMovement(game->square)) {
			selectNextLevel(game);
			resetMouse(mouse);
			resetTimer(timer);

		}

		break;

	case LOSE:

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

	if (dir == INVALID_DIR)
		return;
	//printf("dir: %d, scan: %d\n", dir, scancode);

	if (game->result == PLAYING) {
		//printf("chaega\n");
		if (isAcceptedDirection(currentLevel, dir)) {
			//printf("blabla\n");
			game->result = WAITING;
			game->square->direction = dir;
		} else
			game->result = LOSE;
	}

//if()

//gameUpdateKeyboard(prisonBreaker->game,prisonBreaker->scancode)

}

void gameUpdateMouse(Game* game, Mouse* mouse) {
	Level* currentLevel = game->levels[game->currLevel];
	short dir = getDirectionFromMouse(mouse);

	if (dir == INVALID_DIR)
		return;

	if (game->result == PLAYING) {

		if (isAcceptedDirection(currentLevel, dir)) {
			//printf("blabla\n");
			game->result = WAITING;
			game->square->direction = dir;
		} else
			game->result = LOSE;

	}

//if()

//gameUpdateKeyboard(prisonBreaker->game,prisonBreaker->scancode)

}

void displayTimeBar(Game* game, Timer* timer) {
	//long XCoordBar = BAR_X_COORD_START*game->timePerPlay

	long currTicks = timer->ticks;
	printf("NumberOfTicks: %d\n", currTicks);

	if (currTicks > game->timePerPlay * 60) {
		drawBitmap(game->timeBar, BAR_X_COORD_END, BAR_Y_COORD, ALIGN_LEFT);
		return;
	}

	long XCoordBar = currTicks * (BAR_X_COORD_END - BAR_X_COORD_START)
			/ (game->timePerPlay * 60.0) + BAR_X_COORD_START;
	drawBitmap(game->timeBar, XCoordBar, BAR_Y_COORD, ALIGN_LEFT);

	printf("XCoord: %d\n", XCoordBar);

}

void displayGame(Game* game, Timer* timer) {

	drawBitmap(game->fundo, 0, 0, ALIGN_LEFT);
	displayLevel(game->levels[game->currLevel]);
	displaySquare(game->square);
	displayTimeBar(game, timer);

	//if (game->result == LOSE)
	//	displayLoseScreen(game);

}

void displayLoseScreen(Game* game) {
	//displayGame(game);
	drawBitmap(game->lose, 0, 0, ALIGN_LEFT);

}

void selectNextLevel(Game* game) {
	int nextLevel = rand() % NUMBEROFLEVELS; //random number between 0-NUMBEROFLEVELS-1

	game->score++;
	game->currLevel = nextLevel;
	game->result = PLAYING;

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

short getDirectionFromMouse(Mouse* mouse) {

	if (mouse->deltaX > MIN_MOUSE_MOVEMENT)
		return RIGHT_DIR;

	if (mouse->deltaX < -MIN_MOUSE_MOVEMENT)
		return LEFT_DIR;

	if (mouse->deltaY > MIN_MOUSE_MOVEMENT)
		return UP_DIR;

	if (mouse->deltaY < -MIN_MOUSE_MOVEMENT)
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

void resetGame(Game* game) {

	game->result = PLAYING;
	game->score = 0;
	game->currLevel = 3;

}

void freeGame(Game* game) {

	freeGameLevels(game);
	freeSquare(game->square);
	deleteBitmap(game->fundo);

	//free(game);

}
