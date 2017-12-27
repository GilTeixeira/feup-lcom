#include "game.h"
#include "timer.h"

Game* initGame() {
	Game* game = (Game*) malloc(sizeof(Game));
	game->result = PLAYING;

	game->timePerPlay = 5;

	initLevels(game);

}
void gameHandler(Game* game) {

}
void stopGame(Game* game) {
	free(game);
}

void initLevels(Game* game) {
	/*******************
	 *     Level 1     *
	 ******************/
	short levelID = 1;

	Level * level1 = (Level*) malloc(sizeof(Level));

	level1->numAcceptedDirections = levelID;

	level1->instruction = LEFT;

	level1->acceptedDirections[0] = LEFT_DIR;
	level1->numAcceptedDirections = 1;

	/*******************
	 *     Level 2     *
	 ******************/
	levelID = 2;

	Level * level2 = (Level*) malloc(sizeof(Level));

	level2->numAcceptedDirections = levelID;

	level2->instruction = RIGHT;

	level2->acceptedDirections[0] = RIGHT_DIR;
	level2->numAcceptedDirections = 1;

	/*******************
	 *     Level 3     *
	 ******************/
	levelID = 3;

	Level * level3 = (Level*) malloc(sizeof(Level));

	level3->numAcceptedDirections = levelID;

	level3->instruction = UP;

	level3->acceptedDirections[0] = UP_DIR;
	level3->numAcceptedDirections = 1;

	/*******************
	 *     Level 4     *
	 ******************/
	levelID = 4;

	Level * level4 = (Level*) malloc(sizeof(Level));

	level4->numAcceptedDirections = levelID;

	level4->instruction = DOWN;

	level4->acceptedDirections[0] = DOWN_DIR;
	level4->numAcceptedDirections = 1;

}

void gameUpdate(Game* game, Timer* timer) {

	switch (game->result) {

	case PLAYING:
		if (timer->counter == 3)
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

void gameUpdateKeyboard(Game* game, unsigned long scancode){

	//gameUpdateKeyboard(prisonBreaker->game,prisonBreaker->scancode)

}
