#pragma once

#include "bitmap.h"

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

Square* initSquare();
void SquareHandler(Square* Square);
void stopSquare(Square* Square);
void updateSquare(Square* Square);

void displaySquare(Square* Square);
void freeSquare(Square* square);

short switchDirection(short direction);
