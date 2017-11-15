#include "Ghost.h"
#include "Game.h";



Ghost::Ghost(Game *dir, uint xI, uint yI, uint FcolI)
{	
	vulnerable = false;
	srand(time(NULL));
	game = dir;
	texture = game->pacmanText;
	gameMap = game->gamemap;
	Fcol = IniFcol=FcolI;
	Frow = IniFrow= 0;
	bFrow = 0;
	bFcol = 12;
	x = xIni = xI;
	y = yIni = yI;
	destRect.w = w =game->getWinW() / gameMap->getCols();//Calcula el tamaño del Pacman teniendo en relación la anchura de la ventana y las columnas
	destRect.h = h = game->getWinH() / gameMap->getRows();
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
void Ghost::backToIni(){//Método que hace que los fantasmas regresen a su pos inicial
	x = xIni;
	y = yIni;	
}
void Ghost::changeDir(int dirX, int dirY){
	this->dirX = dirX;
	this->dirY = dirY;
}
void Ghost::move()//Escoge una dirección aleatoria del vector y la aplica
{
	searchDir();
	
	if (dir.size()==0)//Si el tamaño del vector es 0, pone a 0 las direcciones para que vuelva a buscar
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
	else if (x >= game->getRows())
	{
		y = 0;
	}
	dir.clear();//Limpia el vector de direcciones
}
void Ghost::render(){
	texture->renderFrame(game->renderer, srcRect, destRect, Frow, Fcol);
}
void Ghost::searchDir()//REllena un vector con las direcciones posibles para el fantasma
{
	int nx = 0;
	int ny = 0;
	par aux;
	aux.x = aux.y = 0;
	if (game->nextCell(x, y, 1, 0, nx, ny))//Comprueba derecha
	{
		if (!(dirX == -1 && dirY == 0)){//Solo añade la dirección si no es la contraria
			aux.x = 1;
			aux.y = 0;
			dir.push_back(aux);//Mete la dirección derecha al vector si es posible
		}
	}
	if (game->nextCell(x, y, -1, 0, nx, ny))//Izquierda
	{
		if (!(dirX == 1 && dirY == 0)){//Solo añade la dirección si no es la contraria
			aux.x = -1;
			aux.y = 0;
			dir.push_back(aux);
		}
	}
	if (game->nextCell(x, y, 0, 1, nx, ny))//Abajo
	{
		if (!(dirX == 0 && dirY == -1)){//Solo añade la dirección si no es la contraria
			aux.x = 0;
			aux.y = 1;
			dir.push_back(aux);
		}
	}
	if (game->nextCell(x, y, 0, -1, nx, ny))//Arriba
	{
		if (!(dirX == 0 && dirY == 1)){//Solo añade la dirección si no es la contraria
			aux.x = 0;
			aux.y = -1;
			dir.push_back(aux);
		}
	}
}
void Ghost::update(){
	move();
	destRect.x = x*w;
	destRect.y = y*h;
	if (vulnerable && (clock() - startTime) / CLOCKS_PER_SEC >= 5){//Si es vulnerable llama a un contador
		vulnerabilityOff();//Después de 5 segundos se vuelve invulnerable
	}
	if (!vulnerable){
		standardAnimation();
	}
	else blueAnimation();
}
void Ghost::standardAnimation(){//Se encarga de las animaciones cuando son invulnerables
	Fcol = IniFcol+((SDL_GetTicks() / 500) % 2);
	Frow = IniFrow + ((SDL_GetTicks() / 500) % 4);
}
void Ghost::blueAnimation(){//Hace la animación de cuando los fantasmas están azules
	Fcol = bFcol + ((SDL_GetTicks() / 500) % 2);
	Frow = bFrow + ((SDL_GetTicks() / 500) % 2);
}
int Ghost::getPosX(){//Devuelve la posición x
	return x;
}
int Ghost::getPosY(){//Devuelve la posición y
	return y;
}
bool Ghost::getVulnerability(){
	return vulnerable;
}
void Ghost::vulnerabilityOn(){//Método que hace que el fantasma pueda ser comido
	vulnerable = true;
	startTime = clock();	
	//Frow = 0;//Cambia el sprite al color azul
	//Fcol = 12;
}
void Ghost::vulnerabilityOff(){//Método que vuelve al fantasma invulnerable
	vulnerable = false;	
	//Frow = IniFrow;
	//Fcol = IniFcol;
}
