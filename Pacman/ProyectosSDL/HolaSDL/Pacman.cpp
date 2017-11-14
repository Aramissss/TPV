#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(Game *dir, uint xI, uint yI)//Dirección al juego
{
	Frow = 0;
	Fcol = 11;
	game = dir;
	texture = game->pacmanText;
	destRect.w = w = game->winWidth / game->getCols();//Calcula el tamaño del Pacman teniendo en relación la anchura de la ventana y las columnas
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


void Pacman::cambiaDir(char dir){//Según la letra introducida cambia la dirección si es posible
	int nx, ny;
	nx = ny = 0;
	if (dir == 'u' && game->nextCell(x,y,0,-1,nx,ny)){//Up
		dirX = 0;
		dirY = -1;
	}
	else if (dir == 'd' && game->nextCell(x, y, 0, 1, nx, ny)){//Down
		dirX = 0;
		dirY = 1;
	}
	else if (dir == 'l' && game->nextCell(x, y, -1, 0, nx, ny)){//Left
		dirX = -1;
		dirY = 0;
	}
	else if (dir == 'r' && game->nextCell(x, y, 1, 0, nx, ny)){//Right
		dirX = 1;
		dirY = 0;
	}
}
void Pacman::mueve(){
	int nx=0;
	int ny=0;
	if (game->nextCell(x, y, dirX, dirY, nx, ny))//Si la posición siguiente devuelve true, entonces se puede mover
	{
		x = nx;
		y = ny;
		if (game->getCell(nx,ny) == Vitamins)//Cuando choca con una vitamina los fantasmas regresan a su posición original
		{
			game->substractVitamin();
			//LOS FANTASMAS REGRESAN A SU POSICIÓN INICIAL
			game->orangeGhost->vuelveIni();
			game->blueGhost->vuelveIni();
			game->redGhost->vuelveIni();
			game->purpleGhost->vuelveIni();
			game->changeCell(nx, ny, Empty);//Cambia el valor de vitamina por vacío
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
