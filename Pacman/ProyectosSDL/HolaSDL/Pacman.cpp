#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(Game *dir, uint xI, uint yI)//Dirección al juego
{
	Frow = IniFrow= 0;
	Fcol = IniFcol = 10;
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
}
int Pacman::getLives(){//Devuelve las vidas actuales
	return lives;
}
int Pacman::getPosX(){//Devuelve la posición x
	return x;
}
int Pacman::getPosY(){//Devuelve la posición y
	return y;
}

void Pacman::handleAnimation(){//Controla animación que se ejecuta según la dirección actual
	if (dirX == 1 && dirY == 0){
		rightAnimation();
	}
	else if (dirX == -1 && dirY == 0){
		leftAnimation();
	}
	else if (dirX == 0 && dirY == 1){
		downAnimation();
	}
	else if (dirX == 0 && dirY == -1){
		upAnimation();
	}
}
void Pacman::upAnimation(){//Animación arriba
	Frow = 3;
	Fcol = IniFcol + ((SDL_GetTicks() / 150) % 2);
}
void Pacman::downAnimation(){//Animación abajo
	Frow = 1;
	Fcol = IniFcol + ((SDL_GetTicks() / 150) % 2);
}
void Pacman::leftAnimation(){//Animación izquierda
	Frow = 2;
	Fcol = IniFcol + ((SDL_GetTicks() / 150) % 2);
}
void Pacman::rightAnimation(){//Animación derecha
	Frow = 0;
	Fcol = IniFcol + ((SDL_GetTicks() / 150) % 2);
}

void Pacman::changeDir(char dir){//Según la letra introducida cambia la dirección
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
void Pacman::move(){//Aplica la dirección siguiente si es posible
	int nx=0;
	int ny=0;
	if (game->nextCell(x, y, ndirX, ndirY, nx, ny)){//Si la posición pulsada en ese momento es posible
		dirX = ndirX; // entonces la dirección actual toma ese valor (Búffer)
		dirY = ndirY;
	}
	handleAnimation();//Aplica la animación según la dirección
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

void Pacman::update(){//Lleva el movimiento y el lugar donde se pinta
	move();
	destRect.x = x*w;
	destRect.y = y*h;
}
void Pacman::render(){//Pinta la textura
	texture->renderFrame(game->renderer, srcRect, destRect, Frow, Fcol);
}

void Pacman::die(){//Resta una vida a Pacman
	lives--;	
	if (lives < 0){
		game->gameOver();
	}
}
void Pacman::backToIni(){//Regresa a la posición inicial
	x = xIni;
	y = yIni;
}
