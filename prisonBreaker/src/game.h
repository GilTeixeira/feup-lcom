#pragma once

#include "level.h"
#include "square.h"
#include "timer.h"
#include "mouse.h"


/**
 * Game Settings
 */
#define NUMBEROFLEVELS 15
#define TIMEPERPLAY      2

#define KEY_TO_MOVE_UP      KEY_W
#define KEY_TO_MOVE_DOWN    KEY_S
#define KEY_TO_MOVE_LEFT    KEY_A
#define KEY_TO_MOVE_RIGHT   KEY_D

#define MIN_MOUSE_MOVEMENT  1000

#define BAR_X_COORD_START    25
#define BAR_X_COORD_END      275
#define BAR_Y_COORD   489

#define SCORE_X_COORD_START    670
#define SCORE_Y_COORD_START    455
#define SCORE_DELTAX    22
#define SCORE_DELTAY    3


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
	Bitmap** scoreNumbers;
	short numberOfNumbers;

} ScoreNumbers;

/**
 * @struct Game
 * @brief This structure holds information about the Game
 */

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

	ScoreNumbers* scoreNumbers;

} Game;



/**
 * @brief Initializes the Game
 *
 * @return The New Game
 */
Game* initGame();

ScoreNumbers* initScoreNumbers();

/**
 * @brief Initializes the Games Levels
 *
 * @param game The Game to be Initialized
 */
void initLevels(Game* game);

/**
 * @brief Initializes the Games Beginner Levels
 *
 * @param game The Game to be Initialized
 */
void initBeginnerLevels(Game* game);

/**
 * @brief Initializes the Games Normal Levels
 *
 * @param game The Game to be Initialized
 */
void initNormalLevels(Game* game);

/**
 * @brief Initializes the Games Advanced Levels
 *
 * @param game The Game to be Initialized
 */
void initAdvancedLevels(Game* game);

/**
 * @brief Initializes the Games Expert Levels
 *
 * @param game The Game to be Initialized
 */
void initExpertLevels(Game* game);

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
 * @brief Updates the Game in function of Mouse interrupt
 *
 * @param game The Game to be updated
 * @param mouse The current Mouse
 */
void gameUpdateMouse(Game* game, Mouse* mouse);

/**
 * @brief Displays the Game
 *
 * @param game The Game to be displayed
 * @param timer The current Timer
 */
void displayGame(Game* game, Timer* timer);

/**
 * @brief Displays the Game Time Bar
 *
 * @param game The Game to be displayed
 * @param timer The current Timer
 */
void displayTimeBar(Game* game, Timer* timer);

/**
 * @brief Displays the Game Score
 *
 * @param game The Game which score will be displayed
 */
void displayScore(Game* game);

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
 * @brief Free the Game and all the resources used by it
 *
 * @param game The Game to be freed
 */
void freeGame(Game* game);

/**
 * @brief Free the Games Levels and all the resources used by them
 *
 * @param game The Game which levels will be freed
 */
void freeGameLevels(Game* game);



