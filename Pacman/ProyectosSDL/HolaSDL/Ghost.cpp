#include "Ghost.h"
#include "Game.h";



Ghost::Ghost(Game *dir, uint xI, uint yI, uint FcolI)
{	
	vulnerable = false;
	srand(time(NULL));
	game = dir;
	texture = game->pacmanText;
	Fcol = IniFcol=FcolI;
	Frow = IniFrow= 0;
	bFrow = 0;
	bFcol = 12;
	x = xIni = xI;
	y = yIni = yI;
	destRect.w = w =game->getWinW() / game->getCols();//Calcula el tama�o del Pacman teniendo en relaci�n la anchura de la ventana y las columnas
	destRect.h = h = game->getWinH() / game->getRows();
	destRect.x = xIni*w;
	destRect.y = yIni*h;
	dirY = 1;
}


Ghost::~Ghost()
{

}

int Ghost::getPosX(){//Devuelve la posici�n x
	return x;
}
int Ghost::getPosY(){//Devuelve la posici�n y
	return y;
}
bool Ghost::getVulnerability(){//Devuelve el estado actual de su vulnerabilidad
	return vulnerable;
}

void Ghost::standardAnimation(){//Se encarga de las animaciones cuando son invulnerables
	Fcol = IniFcol + ((SDL_GetTicks() / 150) % 2);
	Frow = IniFrow + ((SDL_GetTicks() / 150) % 4);
}
void Ghost::blueAnimation(){//Hace la animaci�n de cuando los fantasmas est�n azules
	Fcol = bFcol + ((SDL_GetTicks() / 150) % 2);
	Frow = bFrow + ((SDL_GetTicks() / 150) % 2);
}

void Ghost::vulnerabilityOn(){//M�todo que hace que el fantasma pueda ser comido
	vulnerable = true;
	startTime = clock();//Guarda la hora actual para despu�s usarla para el contador
}
void Ghost::vulnerabilityOff(){//M�todo que vuelve al fantasma invulnerable
	vulnerable = false;

}

void Ghost::searchDir()//REllena un vector con las direcciones posibles para el fantasma
{
	int nx = 0;
	int ny = 0;
	par aux;
	aux.x = aux.y = 0;
	if (game->nextCell(x, y, 1, 0, nx, ny))//Comprueba derecha
	{
		if (!(dirX == -1 && dirY == 0)){//Solo a�ade la direcci�n si no es la contraria
			aux.x = 1;
			aux.y = 0;
			dir.push_back(aux);//Mete la direcci�n derecha al vector si es posible
		}
	}
	nx = ny = 0;
	if (game->nextCell(x, y, -1, 0, nx, ny))//Izquierda
	{
		if (!(dirX == 1 && dirY == 0)){//Solo a�ade la direcci�n si no es la contraria
			aux.x = -1;
			aux.y = 0;
			dir.push_back(aux);
		}
	}
	nx = ny = 0;
	if (game->nextCell(x, y, 0, 1, nx, ny))//Abajo
	{
		if (!(dirX == 0 && dirY == -1)){//Solo a�ade la direcci�n si no es la contraria
			aux.x = 0;
			aux.y = 1;
			dir.push_back(aux);
		}
	}
	nx = ny = 0;
	if (game->nextCell(x, y, 0, -1, nx, ny))//Arriba
	{
		if (!(dirX == 0 && dirY == 1)){//Solo a�ade la direcci�n si no es la contraria
			aux.x = 0;
			aux.y = -1;
			dir.push_back(aux);
		}
	}
}
void Ghost::move()//Escoge una direcci�n aleatoria del vector y la aplica
{
	searchDir();	
	if (dir.size()==0)//Si el tama�o del vector es 0, pone a 0 las direcciones para que vuelva a buscar
	{
		dirX = 0;
		dirY = 0;
		searchDir();
	}
	int r = rand() % dir.size();//Valor auxiliar que guarda el random
	dirX = dir[r].x;
	dirY = dir[r].y;

	x += dirX;
	y += dirY;
	if (x >= game->getCols())//Estas condiciones hacen que el mapa tenga forma toroide
	{
		x = 0;
	}
	else if (x < 0)
	{
		x = game->getCols() - 1;
	}
	if (y < 0)
	{
		y = game->getRows() - 1;
	}
	else if (y >= game->getRows())
	{
		y = 0;
	}	
	dir.clear();//Limpia el vector de direcciones
}
void Ghost::update(){//Maneja el movimiento, la posici�n del sprite en pantalla y lleva un contador de vulnerabilidad
	move();
	destRect.x = x*w;
	destRect.y = y*h;
	if (vulnerable && (clock() - startTime) / CLOCKS_PER_SEC >= 5){//Si es vulnerable llama a un contador
		vulnerabilityOff();//Despu�s de 5 segundos se vuelve invulnerable
	}
	if (!vulnerable){
		standardAnimation();
	}
	else blueAnimation();
}
void Ghost::render(){//Pinta la textura
	texture->renderFrame(game->renderer, srcRect, destRect, Frow, Fcol);
}



void Ghost::backToIni(){//M�todo que hace que los fantasmas regresen a su pos inicial
	x = xIni;
	y = yIni;
}



