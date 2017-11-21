#pragma once
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "GameMap.h"
#include  <cstdlib>
#include <time.h>
#include "checkML.h";

struct par{//Struct para guardar las direcciones
	int x;
	int y;
};

using namespace std;
class Game;
class Ghost
{
private:

	int x, y, w, h;
	//Posiciones iniciales 
	uint xIni;
	uint yIni;
	int nx, ny;//La posición siguiente calculada
	int dirX, dirY;//Dirección actual del fantasma
	uint Frow, Fcol;//Filas y columnas donde están los frames en la imagen fuente
	uint IniFrow, IniFcol;//Filas y columnas que tienen al principio
	uint bFrow, bFcol;//Filas y columnas de los sprites azules
	Game* game;
	Texture* texture;
	SDL_Rect destRect, srcRect;
	vector<par> dir;//Vector que guarda las direcciones accesibles
	bool vulnerable;//Booleano que indica si el fantasma se puede comer o no
	clock_t startTime;

public:
	Ghost(Game *dir, uint xI, uint yI, uint FcolI);
	~Ghost();

	int getPosX();
	int getPosY();
	bool getVulnerability();

	void blueAnimation();
	void standardAnimation();

	void vulnerabilityOn();
	void vulnerabilityOff();
	
	void searchDir();
	void move();
	void update();
	void render();	

	void backToIni();
};

