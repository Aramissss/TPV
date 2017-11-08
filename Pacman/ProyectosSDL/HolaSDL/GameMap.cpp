#include "GameMap.h"


GameMap::GameMap(uint rows, uint cols)
{
	this->rows = rows;
	this->cols = cols;
	cells = new MapCell*[rows];
	for (int r = 0; r < rows; r++){
		cells[r] = new MapCell[cols];
	}
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
