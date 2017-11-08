#include "Game.h"


Game::Game()
{
	winX = winY = 200;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pacman", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	gamemap = new GameMap(20, 20);//Valor de prueba 20x20


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
		pinkText = new Texture();
		blueText = new Texture();
		purpleText = new Texture();
		
		//Fin

		//Carga texturas
		pacmanText->load(renderer, "..\\images\\characters1.png", 4, 14);
		redText->load(renderer, "..\\images\\characters1.png", 4, 14);
		orangeText->load(renderer, "..\\images\\characters1.png", 4, 14);
		pinkText->load(renderer, "..\\images\\characters1.png", 4, 14);
		blueText->load(renderer, "..\\images\\characters1.png", 4, 14);
		purpleText->load(renderer, "..\\images\\characters1.png", 4, 14);
		//Fin
		
		//Inicializa Entidades
		pacman = new Pacman(this);
		redGhost = new Ghost(this, 0, 0, 0);
		orangeGhost = new Ghost(this, 1, 1, 2);
		pinkGhost = new Ghost(this, 2, 2, 4);
		blueGhost = new Ghost(this, 3, 3, 6);
		purpleGhost = new Ghost(this, 4, 4, 8);
		//Fin
	}
}
Game::~Game()
{
	//Borra entidades
	pacman->~Pacman();
	redGhost->~Ghost();
	orangeGhost->~Ghost();
	pinkGhost->~Ghost();
	blueGhost->~Ghost();
	purpleGhost->~Ghost();
	//Fin

	gamemap->~GameMap();

	//Borra punteros
	delete pacman;
	delete redGhost;
	delete orangeGhost;
	delete pinkGhost;
	delete blueGhost;
	delete purpleGhost;
	//Fin

}
void Game::update(){
	pacman->update();
	redGhost->update();
	orangeGhost->update();
	pinkGhost->update();
	blueGhost->update();
	purpleGhost->update();
}
void Game::render(){
	SDL_RenderClear(renderer);
	pacman->render();
	redGhost->render();
	orangeGhost->render();
	pinkGhost->render();
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
				pacman->cambiaDir(0, 1);
			}
			else if (event.key.keysym.sym == SDLK_UP){
				pacman->cambiaDir(0, -1);
			}
			else if (event.key.keysym.sym == SDLK_RIGHT){
				pacman->cambiaDir(1, 0);
			}
			else if (event.key.keysym.sym == SDLK_LEFT){
				pacman->cambiaDir(-1, 0);
			}
		}
	}
}

void Game::run(){
	while (!exit){
		handleEvents();
		update();
		render();
		SDL_Delay(200);
	}
}
