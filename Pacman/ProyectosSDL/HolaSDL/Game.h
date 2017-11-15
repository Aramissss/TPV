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
	bool exitlevel = false;
	bool gameover = false;
	
	SDL_Event event;
	int winX, winY;	
	const int winWidth = 800;
	const int winHeight = 600;
	Texture* menuText;
	Texture* levelCText;
	Texture* gameOverText;
	Texture* gameWonText;
	bool exitMenu = false;
	SDL_Rect windowRect;
	uint level;
	
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
	void nextLevel();
	int getWinW();
	int getWinH();
	void run();
	void menuEvents();
	void menuRender();
	void nextLevelRender();
	void gameOverRender();
	void gameWonRender();
	void handleEvents();
	void update();
	bool nextCell(int x, int y, int dirX, int dirY, int& nx, int& ny);
	void render();
	void createMap(string filename);
	void substractFood();
	void substractVitamin();
	void checkEndGame();
	int getRows();
	int getCols();
	MapCell getCell(int x, int y);
	void changeCell(int x, int y, MapCell cell);
	bool PacmanBlueColl();
	bool PacmanRedColl();
	bool PacmanPurpleColl();
	bool PacmanOrangeColl();
	void resetPositions();
	void handleCollision();
	void gameOver();
	void gameWon();
};

