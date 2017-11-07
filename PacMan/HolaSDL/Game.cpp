#include "Game.h"


Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Ejercicio TPV", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) {//Si hay errores activa el flag
		error = true;
	}

	else {//Crea las texturas
		//Declaración de Texturas
		PacTex = new Texture;
		if (!PacTex->load(renderer, "..\\images\\dog.png"))//Si no consigue cargar el render activa el flag
		{
			error = true;
		}
		if (!error) {//Declaración de entidades
			Pacman = new PacMan(PacTex, this);
		}
	}
}


Game::~Game()
{
	delete window;
}

void Game::Update() {
}
void Game::render() {
	//SDL_RenderClear(renderer);
	Pacman->render();
	

	SDL_RenderPresent(renderer);
}
void Game::handleEvents()
{
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
		{
			exit = true;
		}
	}
}
void Game::run() {
	while (!exit) {
		handleEvents();
		Update();
		render();
	}