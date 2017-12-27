
#include "square.h"

Square* initSquare(){

	Square* square = (Square*) malloc(
				sizeof(Square));

	square->direction = CENTER;
	square->bitmap = 0;
	square->deslocX = 0;
	square->deslocY = 0;
}


void SquareHandler(Square* Square){

}

void stopSquare(Square* Square){


}

void updateSquare(Square* Square){

}
