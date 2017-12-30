#pragma once

#include "bitmap.h"


#define numMaxOfAcceptedDirections 5

typedef enum {
    LEFT, RIGHT, UP, DOWN,
	NOT_LEFT ,NOT_RIGHT,  NOT_UP, NOT_DOWN,
	NOT_NOT_LEFT , NOT_NOT_RIGHT,   NOT_NOT_UP,  NOT_NOT_DOWN,
	NOTHING , NOT_NOTHING,NOT_NOT_NOTHING

} Intruction;


typedef struct {
	short* acceptedDirections;
	short numAcceptedDirections;

	short instruction;

	short levelID;

	Bitmap* instructionBitmap;



} Level;

Level* initLevel();
void levelHandler(Level* level);
void stopLevel(Level* level);

void displayLevel(Level* level);

short isAcceptedDirection(Level* level, short direction);
void freeLevel(Level* level);
