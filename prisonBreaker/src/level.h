#pragma once


typedef enum {
    LEFT_DIR, RIGHT_DIR, UP_DIR, DOWN_DIR, NOTHING_DIR
} Direction;

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



} Level;

Level* initLevel();
void levelHandler(Level* level);
void stopLevel(Level* level);
