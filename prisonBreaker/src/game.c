#include "game.h"

Game* initGame(){
	Game* game = (Game*) malloc(
				sizeof(Game));
	game->result = PLAYING;

	game->timePerPlay = 5;


}
void gameHandler(Game* game){

}
void stopGame(Game* game){
	free(game);
}
