#include "game.h"
#include "timer.h"
#include "kbd.h"
#include "level.h"

#define KEY_TO_MOVE_UP      KEY_W
#define KEY_TO_MOVE_DOWN    KEY_S
#define KEY_TO_MOVE_LEFT    KEY_A
#define KEY_TO_MOVE_RIGHT   KEY_D

#define MIN_MOUSE_MOVEMENT  1000

#define BAR_X_COORD_START    25
#define BAR_X_COORD_END      275
#define BAR_X_COORD_DIST      BAR_X_COORD_END - BAR_X_COORD_START
#define BAR_Y_COORD   490



Game* initGame() {
	Game* game = (Game*) malloc(sizeof(Game));
	game->result = PLAYING;
	game->score = 0;
	game->currLevel = 0;

	game->timePerPlay = 3;

	initLevels(game);

	game->fundo = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/fundo.bmp");
	//game->lose = loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/lose.bmp");

	game->square = initSquare();

	game->timeBar = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/barra.bmp");

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

	level1->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/left.bmp");

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

	level2->acceptedDirections[0] = RIGHT_DIR;

	level2->instructionBitmap = loadBitmap(
			"/home/lcom/lcom1718-t6g08/prisonBreaker/res/right.bmp");

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

void gameUpdate(Game* game, Timer* timer, Mouse* mouse) {

	switch (game->result) {

	case PLAYING:
		if (timer->counter == game->timePerPlay) {
			Level* currentLevel = game->levels[game->currLevel];
			if (!isAcceptedDirection(currentLevel, NOTHING_DIR))
				game->result = LOSE;

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
	game->currLevel = 0;

}

void freeGame(Game* game) {

	freeGameLevels(game);
	freeSquare(game->square);
	deleteBitmap(game->fundo);

	//free(game);

}

//short isAValidKey(unsigned long scancode){

//if(scancode == KEY_ESC || scancode == KEY_A || scancode == KEY_S || scancode == KEY_D || scancode == KEY_W || scancode == KEY_ENTER)
//	return 1;

//}
