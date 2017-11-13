#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(Game *dir, uint xI, uint yI)//Direcci�n al juego
{
	Frow = 0;
	Fcol = 11;
	game = dir;
	texture = game->pacmanText;
	gameMap = game->gamemap;
	destRect.w = w = game->winWidth / gameMap->cols;//Calcula el tama�o del Pacman teniendo en relaci�n la anchura de la ventana y las columnas
	destRect.h = h = game->winHeight / gameMap->rows;
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
	delete gameMap;
	delete game;
}
bool Pacman::siguiente(int x, int y, int dirX, int dirY, int& nx, int& ny)//Si la siguiente posici�n es una pared devuelve false
{
	nx = x + dirX;//Calcula la posici�n siguiente
	ny = y + dirY;
	if (ny >= gameMap->cols)//Estas condiciones hacen que el mapa tenga forma toroide
	{
		ny = 0;
	}
	else if (ny < 0)
	{
		ny = gameMap->cols - 1;
	}
	if (nx < 0)
	{
		nx = gameMap->rows - 1;
	}
	else if (nx >= gameMap->rows)
	{
		nx = 0;
	}
	if (gameMap->cells[ny][nx] != Wall)
	{
		return true;
	}
	else return false;
}

void Pacman::cambiaDir(char dir){//Seg�n la letra introducida cambia la direcci�n si es posible
	int nx, ny;
	nx = ny = 0;
	if (dir == 'u' && siguiente(x,y,0,-1,nx,ny)){//Up
		dirX = 0;
		dirY = -1;
	}
	else if (dir == 'd' && siguiente(x, y, 0, 1, nx, ny)){//Down
		dirX = 0;
		dirY = 1;
	}
	else if (dir == 'l' && siguiente(x, y, -1, 0, nx, ny)){//Left
		dirX = -1;
		dirY = 0;
	}
	else if (dir == 'r' && siguiente(x, y, 1, 0, nx, ny)){//Right
		dirX = 1;
		dirY = 0;
	}
}
void Pacman::mueve(){
	int nx=0;
	int ny=0;
	if (siguiente(x, y, dirX, dirY,  nx, ny))//Si la posici�n siguiente devuelve true, entonces se puede mover
	{
		x = nx;
		y = ny;
		if (gameMap->cells[ny][nx] == Vitamins)//Cuando choca con una vitamina los fantasmas regresan a su posici�n original
		{
			gameMap->vitamins--;
			//INTRODUCIR QUE LOS FANTASMAS REGRESEN A SU POSICI�N INICIAL
			game->orangeGhost->vuelveIni();
			game->blueGhost->vuelveIni();
			game->redGhost->vuelveIni();
			game->purpleGhost->vuelveIni();
			gameMap->cells[ny][nx] = Empty;
		}
		else if (gameMap->cells[ny][nx] == Food)
		{
			gameMap->foods--;
			gameMap->cells[ny][nx] = Empty;
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
