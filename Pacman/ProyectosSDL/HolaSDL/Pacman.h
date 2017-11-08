#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "GameMap.h"
using namespace std;
class Game;
class Pacman
{
private:
	uint x, y, w, h;
	uint nx, ny;//La posición siguiente calculada
	int dirX, dirY;
	uint Frow, Fcol;//Columnas donde están los frames en la imagen fuente
	Game* game;
	GameMap* gameMap;//Puntero provisional al mapa
	Texture* texture;
	SDL_Rect destRect, srcRect;
public:
	Pacman(Game *dir);
	~Pacman();
	void cambiaDir(int dirX, int dirY);
	void mueve(int dirX, int dirY);
	void render();
	void update();
};

