
#include "square.h"
#include "game.h"


Square* initSquare(){

	Square* square = (Square*) malloc(
				sizeof(Square));

	square->direction = NOTHING_DIR;
	square->bitmap = 0;
	square->deslocX = 0;
	square->deslocY = 0;

	square->bitmap = loadBitmap("/home/lcom/lcom1718-t6g08/prisonBreaker/res/circle.bmp");

	return square;
}


void SquareHandler(Square* square){

}

void stopSquare(Square* square){


}

void updateSquare(Square* square) {

	switch (square->direction) {

	case LEFT_DIR:
		square->deslocX -= 4;
		break;

	case RIGHT_DIR:
		square->deslocX += 4;
		break;

	case UP_DIR:
		square->deslocY -= 4;
		break;
	case DOWN_DIR:
		square->deslocY += 4;
		break;

	}

	if(square->deslocX > 120 || square->deslocY > 120 ||  square->deslocX < -120 ||	square->deslocY < -120)
		square->direction = switchDirection(square->direction);

}

short switchDirection(short direction) {

	switch (direction) {

	case LEFT_DIR:
		return RIGHT_DIR;
		break;

	case RIGHT_DIR:
		return LEFT_DIR;
		break;

	case UP_DIR:
		return DOWN_DIR;
		break;
	case DOWN_DIR:
		return UP_DIR;
		break;

	}

}

short hasFinishedMovement(Square* square) {
	if (square->deslocX == 0 && square->deslocY == 0) {
		square->direction = NOTHING_DIR;
		return 1;
	}
	return 0;
}


void displaySquare(Square* square){
	drawBitmap(square->bitmap, 361+ square->deslocX , 262 + square->deslocY , ALIGN_LEFT);
}


void freeSquare(Square* square){
	deleteBitmap(square->bitmap);
	free(square);
}
