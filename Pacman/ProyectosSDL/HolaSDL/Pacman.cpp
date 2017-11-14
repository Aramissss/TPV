#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(Game *dir, uint xI, uint yI)//Dirección al juego
{
	Frow = 0;
	Fcol = 11;
	game = dir;
	texture = game->pacmanText;
	destRect.w = w = game->getWinW() / game->getCols();//Calcula el tamaño del Pacman teniendo en relación la anchura de la ventana y las columnas
	destRect.h = h = game->getWinH() / game->getRows();
	x = xIni = xI;
	y = yIni = yI;
	destRect.x = x*w;
	destRect.y = y*h;
	dirX = 1;
	lives = 3;
}
Pacman::~Pacman()
{
	texture->~Texture();
	delete texture;
	delete game;
}


void Pacman::changeDir(char dir){//Según la letra introducida cambia la dirección si es posible
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
void Pacman::move(){
	int nx=0;
	int ny=0;
	if (game->nextCell(x, y, ndirX, ndirY, nx, ny)){//Si la posición pulsada en ese momento es posible
		dirX = ndirX; // entonces la dirección actual toma ese valor (Búffer)
		dirY = ndirY;
	}
	nx = ny = 0;
	if (game->nextCell(x, y, dirX, dirY, nx, ny))//Si la posición siguiente devuelve true, entonces se puede mover
	{
		x = nx;
		y = ny;
		if (game->getCell(nx,ny) == Vitamins)//Cuando choca con una vitamina los fantasmas regresan a su posición original
		{
			game->substractVitamin();			
			game->changeCell(nx, ny, Empty);//Cambia el valor de vitamina por vacío
			game->blueGhost->vulnerabilityOn();
			game->redGhost->vulnerabilityOn();
			game->purpleGhost->vulnerabilityOn();
			game->orangeGhost->vulnerabilityOn();
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
	move();
	destRect.x = x*w;
	destRect.y = y*h;
}
int Pacman::getPosX(){
	return x;
}
int Pacman::getPosY(){
	return y;
}
void Pacman::die(){//Resta una vida a Pacman
	lives--;
	cout << lives;
}
void Pacman::backToIni(){
	x = xIni;
	y = yIni;
}
