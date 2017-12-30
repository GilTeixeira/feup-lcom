
#include "square.h"

Square* initSquare(){

	Square* square = (Square*) malloc(
				sizeof(Square));

	square->direction = CENTER;
	square->bitmap = 0;
	square->deslocX = 0;
	square->deslocY = 0;

	return square;
}


void SquareHandler(Square* square){

}

void stopSquare(Square* square){


}

void updateSquare(Square* square){

}


void displaySquare(Square* square){

}


void freeSquare(Square* square){
	deleteBitmap(square->bitmap);
	free(square);
}
