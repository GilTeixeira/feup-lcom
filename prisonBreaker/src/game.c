#include "game.h"

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

	level1->numInstruction = levelID;

	level1->instruction = LEFT;

	level1->acceptedDirections = {LEFT_DIR};
	level1->numAcceptedDirections = 1;

	/*******************
	 *     Level 2     *
	 ******************/
	levelID = 2;

	Level * level2 = (Level*) malloc(sizeof(Level));

	level2->numInstruction = levelID;

	level2->instruction = RIGHT;

	level2->acceptedDirections = {RIGHT_DIR};
	level2->numAcceptedDirections = 1;

	/*******************
	 *     Level 3     *
	 ******************/
	levelID = 3;

	Level * level3 = (Level*) malloc(sizeof(Level));

	level3->numInstruction = levelID;

	level3->instruction = UP;

	level3->acceptedDirections = {UP_DIR};
	level3->numAcceptedDirections = 1;

	/*******************
	 *     Level 4     *
	 ******************/
	levelID = 4;

	Level * level4 = (Level*) malloc(sizeof(Level));

	level4->numInstruction = levelID;

	level4->instruction = DOWN;

	level4->acceptedDirections = {DOWN_DIR};
	level4->numAcceptedDirections = 1;

}

