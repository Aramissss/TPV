#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
using namespace std;
enum MapCell{Empty, Wall, Food, Vitamins};
class GameMap
{
	friend class Game;	
public:
	uint rows;
	uint cols;
	MapCell** cells;
	GameMap(uint rows, uint cols);
	~GameMap();
};

