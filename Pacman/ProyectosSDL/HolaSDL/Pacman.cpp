#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(Game *dir)//Dirección al juego
{
	Frow = 0;
	Fcol = 11;
	game = dir;
	texture = game->pacmanText;
	gameMap = game->gamemap;
	destRect.x = x= 0;
	destRect.y = y= 0;
	destRect.w = game->winWidth / gameMap->cols;//Calcula el tamaño del Pacman teniendo en relación la anchura de la ventana y las columnas
	destRect.h = game->winHeight / gameMap->rows;
	dirX = 1;
}
Pacman::~Pacman()
{
	texture->~Texture();
	delete texture;
	delete gameMap;
	delete game;
}
void Pacman::cambiaDir(int dirX, int dirY){
	this->dirX = dirX;
	this->dirY = dirY;
}
void Pacman::mueve(int dirX, int dirY){
	x += dirX*destRect.w;//Multiplica por el tamaño de las celdas
	y += dirY*destRect.h;	
}
void Pacman::render(){
	texture->renderFrame(game->renderer, srcRect, destRect, Frow, Fcol);
}
void Pacman::update(){
	mueve(dirX, dirY);
	destRect.x = x;
	destRect.y = y;

}
