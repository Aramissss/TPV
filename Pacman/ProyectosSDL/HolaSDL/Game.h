#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Pacman.h"
#include "GameMap.h"
#include "Ghost.h"
#include "UserInterface.h"
#include <string>
#include <iostream>
#include "checkML.h";

using namespace std;
class Game
{
private:
	SDL_Window* window;
	bool error = false;//Flag para errores
	bool exit = false;
	bool exitMenu = false;
	bool exitlevel = false;
	bool gameover = false;
	
	SDL_Event event;
	int winX, winY;	
	const int winWidth = 800;
	const int winHeight = 600;

	
	uint level;
	UserInterface* userinterface;
	
public:
	GameMap* gamemap;
	

	//Entidades
	Pacman* pacman;
	Ghost* redGhost;
	Ghost* orangeGhost;
	Ghost* blueGhost;
	Ghost* purpleGhost;

	//Texturas
	Texture* pacmanText;
	Texture* redText;
	Texture* orangeText;
	Texture* blueText;
	Texture* purpleText;
	//Fin Texturas

	SDL_Renderer* renderer;
	Game();
	~Game();
	int getWinW();
	int getWinH();
	int getRows();
	int getCols();
	MapCell getCell(int x, int y);


	void changeCell(int x, int y, MapCell cell);
	void substractFood();
	void substractVitamin();	

	void createMap(string filename);
	void menuEvents();
	void nextLevel();
	void handleEvents();
	void update();
	void render();
	void run();	
	
	
	bool nextCell(int x, int y, int dirX, int dirY, int& nx, int& ny);		
	bool PacmanBlueColl();
	bool PacmanRedColl();
	bool PacmanPurpleColl();
	bool PacmanOrangeColl();
	void handleCollision();
	void resetPositions();
	
	void checkEndGame();
	void gameOver();
	void gameWon();
};

