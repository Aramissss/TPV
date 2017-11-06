#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include "Texture.h";
using namespace std;
class Dog
{
private:
	uint w, h;
	uint x, y;
	int dirX;
	int dirY;
	uint row, col;
	Texture* texture;//Puntero a la textura
	Game* game;//Puntero al juego
	SDL_Rect destRect;
public:
	Dog();
	~Dog();
	void render();
	void update();
};

