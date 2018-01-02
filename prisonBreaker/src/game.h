#pragma once

#include "level.h"
#include "square.h"
#include "timer.h"
#include "mouse.h"

// TO DO change for 15
#define NUMBEROFLEVELS 4

/** @defgroup Game
 * @{
 * Game Struct and functions for manipulating the Game
 */

typedef enum {
	LEFT_DIR, RIGHT_DIR, UP_DIR, DOWN_DIR, NOTHING_DIR, INVALID_DIR
} Direction;

typedef enum {
	PLAYING, WAITING, LOSE
} Result;

typedef struct {
	short currLevel;
	short score;
	short result;
	long timePerPlay;
	Level** levels;

	Square* square;

	Bitmap* fundo;
	Bitmap* lose;

	Bitmap* timeBar;

} Game;

/**
 * @brief Initializes the Game
 *
 * @return The New Game
 */
Game* initGame();

/**
 * @brief Initializes the Games Levels
 *
 * @param game The Game to be Initialized
 */
void initLevels(Game* game);

/**
 * @brief Updates the Game in function of Timer interrupt
 *
 * @param game The Game to be updated
 * @param timer The updated Timer
 * @param mouse The current mouse state
 */
void gameUpdate(Game* game, Timer* timer, Mouse* mouse);

/**
 * @brief Updates the Game in function of Keyboard interrupt
 *
 * @param game The Game to be updated
 * @param scancode The scancode read from the interrupt
 */
void gameUpdateKeyboard(Game* game, unsigned long scancode);

/**
 * @brief Displays the Game
 *
 * @param game The Game to be displayed
 * @param timer The current Timer
 */
void displayGame(Game* game, Timer* timer);

/**
 * @brief Displays the Game Lose Screen
 *
 * @param game The Game to be displayed
 */
void displayLoseScreen(Game* game);

/**
 * @brief Selects the Game next Level
 *
 * @param game The Game to be displayed
 */
void selectNextLevel(Game* game);

/**
 * @brief Restarts the Game Settings
 *
 * @param game The Game to be restarted
 */
void resetGame(Game* game);

/**
 * @brief Free the Games Levels and all the resources used by them
 *
 * @param game The Game which levels will be freed
 */
void freeGameLevels(Game* game);

/**
 * @brief Free the Game and all the resources used by it
 *
 * @param game The Game to be freed
 */
void freeGame(Game* game);

/**
 * @brief Gets the Direction from a Key
 *
 * @param scancode The scancode of a Key
 *
 * @return The Direction
 */
short getDirectionFromKey(unsigned long scancode);

/**
 * @brief Gets the Direction read from the Mouse
 *
 * @param mouse The current mouse
 *
 * @return The Direction
 */
short getDirectionFromMouse(Mouse* mouse);

/**
 * @brief Updates the Game in function of Mouse interrupt
 *
 * @param game The Game to be updated
 * @param mouse The current Mouse
 */
void gameUpdateMouse(Game* game, Mouse* mouse);

