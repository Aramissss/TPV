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
		dogText = new Texture;
		if (!dogText->load(renderer, "..\\images\\dog.png"))//Si no consigue cargar el render activa el flag
		{
			error = true;
		}
		if (!error) {
			dog = Dog();
		}
	}
}
void Game::Update() {
	dog.update();
}
void Game::render() {
	SDL_RenderClear(renderer);
	backgroundText->renderWindow(renderer);
	dog.render();
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
 }



Game::~Game()
{
}
