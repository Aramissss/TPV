#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h";
#include "PacMan.h";
using namespace std;
class Game
{
private:
	SDL_Window* window;
	bool error = false;//Flag para errores
	bool exit = false;
	const int winWidth = 800;
	const int winHeight = 600;
	SDL_Event event;
	int winX, winY;

	Texture* PacTex;
	PacMan* Pacman;
	
public:
	SDL_Renderer* renderer;
	Game();
	~Game();
	void run();
	void handleEvents();
	void Update();
	void render();
};

