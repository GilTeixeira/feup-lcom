#pragma once

#include "bitmap.h"

typedef enum {
    GO_TO_LEFT, GO_TO_RIGHT, GO_TO_UP, GO_TO_DOWN,
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
