#include "Ghost.h"
#include "Game.h";


Ghost::Ghost(Game *dir, uint xI, uint yI, uint FcolI)
{
	game = dir;
	texture = game->pacmanText;
	gameMap = game->gamemap;
	Fcol = FcolI;
	Frow = 1;
	destRect.w = game->winWidth / gameMap->cols;//Calcula el tamaño del Pacman teniendo en relación la anchura de la ventana y las columnas
	destRect.h = game->winHeight / gameMap->rows;
	destRect.x = x = xIni = xI*destRect.w;
	destRect.y = y = yIni = yI*destRect.h;
	dirY = 1;
}


Ghost::~Ghost()
{
	texture->~Texture();
	delete texture;
	delete gameMap;
	delete game;
}

void Ghost::cambiaDir(int dirX, int dirY){
	this->dirX = dirX;
	this->dirY = dirY;
}
void Ghost::mueve(int dirX, int dirY){
	x += dirX*destRect.w;//Multiplica por el tamaño de las celdas
	y += dirY*destRect.h;
}
void Ghost::render(){
	texture->renderFrame(game->renderer, srcRect, destRect, Frow, Fcol);
}
void Ghost::update(){
	mueve(dirX, dirY);
	destRect.x = x;
	destRect.y = y;

}
