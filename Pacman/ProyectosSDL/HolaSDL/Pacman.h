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
	uint x, y, w, h, xIni, yIni;
	uint nx, ny;//La posici�n siguiente calculada
	int dirX, dirY, ndirX, ndirY;
	uint Frow, Fcol;//Columnas donde est�n los frames en la imagen fuente
	uint IniFrow, IniFcol; //Columnas iniciales donde est�n los frames
	Game* game;
	Texture* texture;
	SDL_Rect destRect, srcRect;
	int lives;
public:
	Pacman(Game *dir, uint xI, uint yI);
	~Pacman();
	void handleAnimation();
	void upAnimation();
	void downAnimation();
	void leftAnimation();
	void rightAnimation();
	bool checkGhost();
	void changeDir(char dir);
	void move();
	void render();
	void update();
	int getPosX();
	int getPosY();
	void die();
	void backToIni();
};

