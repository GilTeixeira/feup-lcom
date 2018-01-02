#include "gameState.h"

GameState* initGameState() {

	GameState* gameState = (GameState*) malloc(sizeof(GameState));

	gameState->done = 0;

	//Game
	gameState->game = initGame();

	gameState->currState = MAINMENU;

	gameState->LoseMenuBitmap = loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/lose.bmp");
	gameState->MainMenuBitmap = loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/menu.bmp");

	return gameState;

}


void displayGameState(GameState* gameState, Timer* timer) {

	switch (gameState->currState) {
	case MAINMENU:
		drawBitmap(gameState->MainMenuBitmap, 0, 0, ALIGN_LEFT);
		break;
	case LOSEMENU:
		//printf("U lose, loser\n");
		drawBitmap(gameState->LoseMenuBitmap, 0, 0, ALIGN_LEFT);
		break;
	case GAME:
		//printf("Still Drawing this?\n");
		displayGame(gameState->game, timer);
		//drawBitmap(gameState->LoseMenuBitmap,0,0,ALIGN_LEFT);
		break;
	}

}

void gameStateUpdate(GameState* gameState, Timer* timer, Mouse* mouse) {

	switch (gameState->currState) {
	case MAINMENU:
		break;
	case LOSEMENU:
		break;
	case GAME:
		gameUpdate(gameState->game, timer, mouse);
		if(gameState->game->result == LOSE)
			gameState->currState = LOSEMENU;
		break;
	}

}


void gameStateUpdateKeyboard(GameState* gameState, unsigned long scancode, Timer* timer, Mouse* mouse) {

	switch (gameState->currState) {
	case MAINMENU:
		if (scancode == KEY_ESC)
			gameState->done = 1;

		else if (scancode == KEY_ENTER) {
			resetGame(gameState->game);
			resetMouse(mouse);
			resetTimer(timer);
			gameState->currState = GAME;
		}

		break;
	case LOSEMENU:
		if (scancode == KEY_ESC)
			gameState->currState = MAINMENU;

		else if (scancode == KEY_ENTER) {
			resetGame(gameState->game);
			resetMouse(mouse);
			resetTimer(timer);
			gameState->currState = GAME;
		}
		break;
	case GAME:
		gameUpdateKeyboard(gameState->game, scancode);
		break;
	}

}


void gameStateUpdateMouse(GameState* gameState, Mouse* mouse) {

	switch (gameState->currState) {
	case MAINMENU:
		break;
	case LOSEMENU:
		break;
	case GAME:
		gameUpdateMouse(gameState->game, mouse);
		if(gameState->game->result == LOSE)
			gameState->currState = LOSEMENU;
		break;
	}

}


void stopGameState(GameState* gameState) {

	deleteBitmap(gameState->LoseMenuBitmap);
	deleteBitmap(gameState->MainMenuBitmap);
	freeGame(gameState->game);
}
