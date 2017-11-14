#pragma once
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "GameMap.h"
#include  <cstdlib>
#include <time.h>

struct par{//Struct para guardar las direcciones
	int x;
	int y;
};

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
	int dirX, dirY;//Dirección actual del fantasma
	uint Frow, Fcol;//Filas y columnas donde están los frames en la imagen fuente
	uint IniFrow, IniFcol;//Filas y columnas que tienen al principio
	Game* game;
	GameMap* gameMap;//Puntero provisional al mapa
	Texture* texture;
	SDL_Rect destRect, srcRect;
	vector<par> dir;
	bool vulnerable;
	clock_t startTime;

public:
	Ghost(Game *dir, uint xI, uint yI, uint FcolI);
	~Ghost();
	bool getVulnerability();
	int getPosX();
	int getPosY();
	void backToIni();
	void searchDir();
	void changeDir(int dirX, int dirY);
	void move();
	void render();
	void update();
	void vulnerabilityOn();
	void vulnerabilityOff();
};

