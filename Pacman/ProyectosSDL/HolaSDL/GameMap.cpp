#include "GameMap.h"
#include "Game.h"


GameMap::GameMap(Game* dir, uint rows, uint cols)
{
	game = dir;
	this->rows = rows;
	this->cols = cols;
	foods = 0;
	walls = 0;
	vitamins = 0;
	cells = new MapCell*[rows];
	for (int r = 0; r < rows; r++){
		cells[r] = new MapCell[cols];
	}
	size.h = game->winHeight / rows;
	size.w = game->winWidth / cols;
}

GameMap::~GameMap()
{
	if (cells != nullptr){
		for (int r = 0; r < rows; r++){
			delete[] cells[r];
		}
		delete[] cells;
	}
}
void GameMap::mapTexts()
{
	WallsTex.resize(walls);
	FoodsTex.resize(foods);
	VitaminsTex.resize(vitamins);
	for (int i = 0; i < walls; i++)
	{
		WallsTex[i] = new Texture();
		WallsTex[i]->load(game->renderer, "..\\images\\wall2.png", 1, 1);
	}
	for (int i = 0; i < foods; i++)
	{
		FoodsTex[i] = new Texture();
		FoodsTex[i]->load(game->renderer, "..\\images\\food2.png", 1, 1);
	}
	for (int i = 0; i < vitamins; i++)
	{
		VitaminsTex[i] = new Texture();
		VitaminsTex[i]->load(game->renderer, "..\\images\\burguer1.png", 1, 1);
	}
}
void GameMap::renderMap()
{
	uint w = 0;
	uint f = 0;
	uint v = 0;
	SDL_Rect rect;
	for (int i= 0; i < rows; i++)
	{
		for (int j = 0; j < cols;j++)
		{
			if (cells[i][j] == Wall)
			{
				rect.h = size.h;
				rect.w = size.w;
				rect.x = j*size.w;
				rect.y = i*size.h;
				WallsTex[w]->render(game->renderer, rect);
				w++;

			}
			else if (cells[i][j] == Food)
			{
				rect.h = size.h;
				rect.w = size.w;
				rect.x = j*size.w;
				rect.y = i*size.h;
				FoodsTex[f]->render(game->renderer, rect);
				f++;

			}
			else if (cells[i][j] == Vitamins)
			{
				rect.h = size.h;
				rect.w = size.w;
				rect.x = j*size.w;
				rect.y = i*size.h;
				VitaminsTex[v]->render(game->renderer, rect);
				v++;

			}
		}
	}
}
