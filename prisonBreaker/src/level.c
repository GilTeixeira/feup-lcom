
#include "level.h"

void displayLevel(Level* level){

}

short isAcceptedDirection(Level* level, short direction){
	int i;
	for (i = 0; i < level->numAcceptedDirections; i++) {
		if (level->acceptedDirections[i] == direction)
			return 1;
	}
	return 0;
}


void freeLevel(Level* level){
	free(level->acceptedDirections);
	free(level);

}
