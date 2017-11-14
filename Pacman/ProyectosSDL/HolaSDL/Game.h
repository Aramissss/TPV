#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Pacman.h"
#include "GameMap.h"
#include "Ghost.h"
#include <string>
#include <iostream>

using namespace std;
class Game
{
private:
	SDL_Window* window;
	bool error = false;//Flag para errores
	bool exit = false;
	
	SDL_Event event;
	int winX, winY;	

	
	//Fin Endidades
	
	
	
public:
	GameMap* gamemap;
	const int winWidth = 800;
	const int winHeight = 600;
	/*uint rows = 20;
	uint cols = 20;
	MapCell cells[20][20];*/
	//Entidades
	Pacman* pacman;
	Ghost* redGhost;
	Ghost* orangeGhost;
	//Ghost* pinkGhost;
	Ghost* blueGhost;
	Ghost* purpleGhost;

	//Texturas
	Texture* pacmanText;
	Texture* redText;
	Texture* orangeText;
	//Texture* pinkText;
	Texture* blueText;
	Texture* purpleText;
	//Fin Texturas

	SDL_Renderer* renderer;
	Game();
	~Game();
	void run();
	void handleEvents();
	void update();
	bool nextCell(int x, int y, int dirX, int dirY, int& nx, int& ny);
	void render();
	void createMap();
	void substractFood();
	void substractVitamin();
	uint getRows();
	uint getCols();
	MapCell getCell(int x, int y);
	void changeCell(int x, int y, MapCell cell);
	
};

