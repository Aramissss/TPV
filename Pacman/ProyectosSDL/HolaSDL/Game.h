#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Pacman.h"
#include "GameMap.h"
#include "Ghost.h"

using namespace std;
class Game
{
private:
	SDL_Window* window;
	bool error = false;//Flag para errores
	bool exit = false;
	
	SDL_Event event;
	int winX, winY;	

	//Entidades
	Pacman* pacman;
	Ghost* redGhost;
	Ghost* orangeGhost;
	Ghost* pinkGhost;
	Ghost* blueGhost;
	Ghost* purpleGhost;
	//Fin Endidades
	
	
	
public:
	GameMap* gamemap;
	const int winWidth = 800;
	const int winHeight = 600;
	/*uint rows = 20;
	uint cols = 20;
	MapCell cells[20][20];*/

	//Texturas
	Texture* pacmanText;
	Texture* redText;
	Texture* orangeText;
	Texture* pinkText;
	Texture* blueText;
	Texture* purpleText;
	//Fin Texturas

	SDL_Renderer* renderer;
	Game();
	~Game();
	void run();
	void handleEvents();
	void update();
	void render();
	void createMap();
};

