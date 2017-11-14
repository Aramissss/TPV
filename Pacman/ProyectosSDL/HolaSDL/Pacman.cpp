#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(Game *dir, uint xI, uint yI)//Direcci�n al juego
{
	Frow = 0;
	Fcol = 11;
	game = dir;
	texture = game->pacmanText;
	destRect.w = w = game->winWidth / game->getCols();//Calcula el tama�o del Pacman teniendo en relaci�n la anchura de la ventana y las columnas
	destRect.h = h = game->winHeight / game->getRows();
	x = xI;
	y = yI;
	destRect.x = x*w;
	destRect.y = y*h;
	dirX = 1;
}
Pacman::~Pacman()
{
	texture->~Texture();
	delete texture;
	delete game;
}


void Pacman::cambiaDir(char dir){//Seg�n la letra introducida cambia la direcci�n si es posible
	int nx, ny;
	nx = ny = 0;
	if (dir == 'u'){//Up
		ndirX = 0;
		ndirY = -1;
	}
	else if (dir == 'd'){//Down
		ndirX = 0;
		ndirY = 1;
	}
	else if (dir == 'l'){//Left
		ndirX = -1;
		ndirY = 0;
	}
	else if (dir == 'r'){//Right
		ndirX = 1;
		ndirY = 0;
	}

}
void Pacman::mueve(){
	int nx=0;
	int ny=0;
	if (game->nextCell(x, y, ndirX, ndirY, nx, ny)){//Si la posici�n pulsada en ese momento es posible
		dirX = ndirX; // entonces la direcci�n actual toma ese valor (B�ffer)
		dirY = ndirY;
	}
	nx = ny = 0;
	if (game->nextCell(x, y, dirX, dirY, nx, ny))//Si la posici�n siguiente devuelve true, entonces se puede mover
	{
		x = nx;
		y = ny;
		if (game->getCell(nx,ny) == Vitamins)//Cuando choca con una vitamina los fantasmas regresan a su posici�n original
		{
			game->substractVitamin();
			//LOS FANTASMAS REGRESAN A SU POSICI�N INICIAL
			game->orangeGhost->vuelveIni();
			game->blueGhost->vuelveIni();
			game->redGhost->vuelveIni();
			game->purpleGhost->vuelveIni();
			game->changeCell(nx, ny, Empty);//Cambia el valor de vitamina por vac�o
		}
		else if (game->getCell(nx, ny) == Food)
		{
			game->substractFood();
			game->changeCell(nx, ny, Empty);
		}
	}
}
void Pacman::render(){
	texture->renderFrame(game->renderer, srcRect, destRect, Frow, Fcol);
}
void Pacman::update(){
	mueve();
	destRect.x = x*w;
	destRect.y = y*h;

}
