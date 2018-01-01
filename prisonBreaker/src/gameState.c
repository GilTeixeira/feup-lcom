#include "gameState.h"

GameState* initGameState() {

	GameState* gameState = (GameState*) malloc(sizeof(GameState));

	gameState->done = 0;

	//Game
	gameState->game = initGame();

	gameState->currState = GAME;

	gameState->LoseMenuBitmap = loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/lose.bmp");
	gameState->MainMenuBitmap = loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/lose.bmp");

	return gameState;

}
//void gameHandler(GameState* gameState);

void displayGameState(GameState* gameState) {

	switch (gameState->currState) {
	case MAINMENU:
		drawBitmap(gameState->MainMenuBitmap, 0, 0, ALIGN_LEFT);
		break;
	case LOSEMENU:
		printf("U lose, loser\n");
		drawBitmap(gameState->LoseMenuBitmap, 0, 0, ALIGN_LEFT);
		break;
	case GAME:
		printf("Still Drawing this?\n");
		displayGame(gameState->game);
		//drawBitmap(gameState->LoseMenuBitmap,0,0,ALIGN_LEFT);
		break;
	}

}

void stopGameState(GameState* gameState) {

	deleteBitmap(gameState->LoseMenuBitmap);
	deleteBitmap(gameState->MainMenuBitmap);
	freeGame(gameState->game);
}

void gameStateUpdateKeyboard(GameState* gameState, unsigned long scancode) {

	switch (gameState->currState) {
	case MAINMENU:
		if (scancode == KEY_ESC)
			gameState->done = 1;

		else if (scancode == KEY_ENTER) {
			resetGame(gameState->game);
			gameState->currState = GAME;
		}

		break;
	case LOSEMENU:
		if (scancode == KEY_ESC)
			gameState->currState = MAINMENU;

		else if (scancode == KEY_ENTER) {
			resetGame(gameState->game);
			gameState->currState = GAME;
		}
		break;
	case GAME:
		gameUpdateKeyboard(gameState->game, scancode);
		break;
	}

}

void gameStateUpdate(GameState* gameState, Timer* timer) {

	switch (gameState->currState) {
	case MAINMENU:
		break;
	case LOSEMENU:
		break;
	case GAME:
		gameUpdate(gameState->game, timer);
		if(gameState->game->result == LOSE)
			gameState->currState = LOSEMENU;
		break;
	}

}
