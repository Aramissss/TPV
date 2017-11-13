#include "Ghost.h"
#include "Game.h";


Ghost::Ghost(Game *dir, uint xI, uint yI, uint FcolI)
{
	game = dir;
	texture = game->pacmanText;
	gameMap = game->gamemap;
	Fcol = FcolI;
	Frow = 1;
	x = xIni = xI;
	y = yIni = yI;
	destRect.w = w =game->winWidth / gameMap->cols;//Calcula el tamaño del Pacman teniendo en relación la anchura de la ventana y las columnas
	destRect.h = h = game->winHeight / gameMap->rows;
	destRect.x = xIni*w;
	destRect.y = yIni*h;
	dirY = 1;
}


Ghost::~Ghost()
{
	texture->~Texture();
	delete texture;
	delete gameMap;
	delete game;
}
void Ghost::vuelveIni(){//Método que se llama cuando Pacman come una vitamina y regresan a su pos inicial
	x = xIni;
	y = yIni;	
}
void Ghost::cambiaDir(int dirX, int dirY){
	this->dirX = dirX;
	this->dirY = dirY;
}
void Ghost::mueve(int dirX, int dirY){
	x += dirX;//Multiplica por el tamaño de las celdas
	y += dirY;
}
void Ghost::render(){
	texture->renderFrame(game->renderer, srcRect, destRect, Frow, Fcol);
}
void Ghost::update(){
	mueve(dirX, dirY);
	destRect.x = x*w;
	destRect.y = y*h;

}
