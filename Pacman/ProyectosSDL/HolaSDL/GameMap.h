#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include <vector>
using namespace std;
enum MapCell{Empty, Wall, Food, Vitamins};
class Game;
class GameMap
{
	friend class Game;	
private:
	vector<Texture*> WallsTex;
	vector<Texture*> FoodsTex;
	vector<Texture*> VitaminsTex;
	Game* game;
	SDL_Rect size;
	uint rows;
	uint cols;
	uint walls;
	uint foods;
	uint vitamins;

public:
	
	MapCell** cells;
	GameMap(Game* dir,uint rows, uint cols);
	~GameMap();
	int getRows();
	int getCols();
	int getWalls();
	int getFoods();
	int getVitamins();

	void mapTexts();
	void renderMap();
};

