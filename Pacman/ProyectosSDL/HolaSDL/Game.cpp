#include "Game.h"
#include <fstream>


Game::Game()
{
	winX = winY = 50;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pacman", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//gamemap = new GameMap(20, 20);//Valor de prueba 20x20


	if (renderer == nullptr)//Si hay errores activa el flag
	{
		error = true;
	}
	else//Crea las texturas e entidades
	{
		//Inicializa Texturas
		pacmanText = new Texture();
		redText = new Texture();
		orangeText = new Texture();
		//pinkText = new Texture();
		blueText = new Texture();
		purpleText = new Texture();
		
		//Fin

		//Carga texturas
		pacmanText->load(renderer, "..\\images\\characters1.png", 4, 14);
		redText->load(renderer, "..\\images\\characters1.png", 4, 14);
		orangeText->load(renderer, "..\\images\\characters1.png", 4, 14);
		//pinkText->load(renderer, "..\\images\\characters1.png", 4, 14);
		blueText->load(renderer, "..\\images\\characters1.png", 4, 14);
		purpleText->load(renderer, "..\\images\\characters1.png", 4, 14);
		//Fin
		
		/*Inicializa Entidades
		pacman = new Pacman(this);
		//redGhost = new Ghost(this, 0, 0, 0);
		orangeGhost = new Ghost(this, 1, 1, 2);
		pinkGhost = new Ghost(this, 2, 2, 4);
		blueGhost = new Ghost(this, 3, 3, 6);
		purpleGhost = new Ghost(this, 4, 4, 8);
		//Fin*/
	}
}
Game::~Game()
{
	//Borra entidades
	pacman->~Pacman();
	redGhost->~Ghost();
	orangeGhost->~Ghost();
	//pinkGhost->~Ghost();
	blueGhost->~Ghost();
	purpleGhost->~Ghost();
	//Fin

	gamemap->~GameMap();

	//Borra punteros
	delete pacman;
	delete redGhost;
	delete orangeGhost;
	//delete pinkGhost;
	delete blueGhost;
	delete purpleGhost;
	//Fin

}
void Game::createMap()//Lee de un archivo y crea la matriz del mapa
{
	ifstream archivo;
	string nameFile;
	cin >> nameFile;
	archivo.open("..\\levels\\"+ nameFile +".dat");
	uint rows, cols;
	archivo >> rows;
	archivo >> cols;	
	int dato;
	gamemap = new GameMap(this,rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			archivo >> dato;
			if (dato == 0){
				gamemap->cells[i][j] = Empty;
			}
			else if (dato == 1){
				gamemap->cells[i][j] = Wall;
				gamemap->walls++;
			}
			else if (dato == 2){
				gamemap->cells[i][j] = Food;
				gamemap->foods++;
			}
			else if (dato == 3){
				gamemap->cells[i][j] = Vitamins;
				gamemap->vitamins++;
			}
			else if (dato == 6)
			{
				gamemap->cells[i][j] = Empty;
				redGhost = new Ghost(this, j, i, 0);
			}
			else if (dato == 5)
			{
				gamemap->cells[i][j] = Empty;
				orangeGhost = new Ghost(this, j, i, 2);
			}
			else if (dato == 4)
			{
				/*gamemap->cells[j][i] = Empty;
				pinkGhost = new Ghost(this, i, j, 0);*/
			}
			else if (dato == 7)
			{
				gamemap->cells[i][j] = Empty;
				blueGhost = new Ghost(this, j, i, 6);
			}
			else if (dato == 8)
			{
				gamemap->cells[i][j] = Empty;
				purpleGhost = new Ghost(this, j, i, 8);
			}
			else if (dato == 9)
			{
				gamemap->cells[i][j] = Empty;
				pacman = new Pacman(this, j, i);
			}
		}
	}
	
	gamemap->mapTexts();
	archivo.close();

}
void Game::update(){
	pacman->update();
	redGhost->update();
	orangeGhost->update();
//	pinkGhost->update();
	blueGhost->update();
	purpleGhost->update();
}
void Game::render(){
	SDL_RenderClear(renderer);
	gamemap->renderMap();
	pacman->render();
	redGhost->render();
	orangeGhost->render();
	//pinkGhost->render();
	blueGhost->render();
	purpleGhost->render();
	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
		{
			exit = true;
		}
		else if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.sym == SDLK_DOWN){
				pacman->cambiaDir('d');
			}
			else if (event.key.keysym.sym == SDLK_UP){
				pacman->cambiaDir('u');
			}
			else if (event.key.keysym.sym == SDLK_RIGHT){
				pacman->cambiaDir('r');
			}
			else if (event.key.keysym.sym == SDLK_LEFT){
				pacman->cambiaDir('l');
			}
		}
	}
}


void Game::run(){
	createMap();
	while (!exit){
		handleEvents();
		update();
		render();
		SDL_Delay(200);
	}
}
