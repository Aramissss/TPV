#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
using namespace std;
class Game;
class Pacman
{
private:
	int x, y, w, h, xIni, yIni;
	int nx, ny;//La posición siguiente calculada
	int dirX, dirY, ndirX, ndirY;
	uint Frow, Fcol;//Columnas donde están los frames en la imagen fuente
	uint IniFrow, IniFcol; //Columnas iniciales donde están los frames
	Game* game;
	Texture* texture;
	SDL_Rect destRect, srcRect;
	int lives;
public:
	Pacman(Game *dir, uint xI, uint yI);
	~Pacman();
	int getLives();
	int getPosX();
	int getPosY();

	void handleAnimation();
	void upAnimation();
	void downAnimation();
	void leftAnimation();
	void rightAnimation();
	
	void changeDir(char dir);
	void move();	
	void update();
	void render();
	
	void die();
	void backToIni();
};

