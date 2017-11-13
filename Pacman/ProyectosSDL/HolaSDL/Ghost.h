#pragma once
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "GameMap.h"

using namespace std;
class Game;
class Ghost
{
private:

	uint x, y, w, h;
	//Posiciones iniciales 
	uint xIni;
	uint yIni;
	uint nx, ny;//La posición siguiente calculada
	int dirX, dirY;
	uint Frow, Fcol;//Filas y columnas donde están los frames en la imagen fuente
	Game* game;
	GameMap* gameMap;//Puntero provisional al mapa
	Texture* texture;
	SDL_Rect destRect, srcRect;


public:
	Ghost(Game *dir, uint xI, uint yI, uint FcolI);
	~Ghost();
	void vuelveIni();
	void cambiaDir(int dirX, int dirY);
	void mueve(int dirX, int dirY);
	void render();
	void update();

};

