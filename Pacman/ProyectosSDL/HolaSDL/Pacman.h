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
	Texture* texture;
	SDL_Rect destRect, srcRect;
public:
	Pacman(Game *dir, uint xI, uint yI);
	~Pacman();
	void cambiaDir(char dir);
	void mueve();
	bool siguiente(int x, int y, int dirX, int dirY, int& nx, int& ny);
	void render();
	void update();
};

