
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Game.h"
using namespace std;


int main(int argc, char* argv[]){
	Game* game = new Game;
	game->run();
	//game->~Game();
	return 0;
}