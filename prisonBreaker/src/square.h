#pragma once

#include "bitmap.h"

/**
 *
 */
#define DISTANCE_TO_MOVE 100

typedef enum {
    GOING_LEFT,  GOING_RIGHT,  GOING_UP,  GOING__DOWN,
	RET_FROM_LEFT, RET_FROM_RIGHT, RET_FROM_UP, RET_FROM_DOWN,
	CENTER
} DirectionSquare;



typedef struct {
	short direction;
	Bitmap* bitmap;

	short deslocX, deslocY;


} Square;


/**
 * @brief  Initializes the Square
 *
 * @return The Square
 */
Square* initSquare();

/**
 * @brief
 *
 * @param Square
 */
//void SquareHandler(Square* square);

/**
 * @brief
 *
 * @param Square
 */
//void stopSquare(Square* square);

/**
 * @brief  Updates the Square
 *
 * @param Square The Square to be updated
 */
void updateSquare(Square* square);

/**
 * @brief Display the Square
 *
 * @param Square The Square to be displayed
 */
void displaySquare(Square* square);

/**
 * @brief  Free the Square and all the resources used by it
 *
 * @param square The Square to be freed
 */
void freeSquare(Square* square);

/**
 * @brief
 *
 * @param direction
 *
 * @return
 */
//short switchDirection(short direction);

/**
 * @brief Check if square has return to its initial position
 *
 * @param square The square to be tested
 *
 * @return 1 if has finished, 0 if has not
 */
short hasFinishedMovement(Square* square);
