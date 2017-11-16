#include "UserInterface.h"
#include "Game.h"

UserInterface::UserInterface(Game* dir)
{
	game = dir;
	menuText = new Texture();
	levelCText = new Texture();
	gameOverText = new Texture();
	gameWonText = new Texture();
	life = new Texture();


	menuText->load(game->renderer, "..\\images\\pacmanMenu.png");
	levelCText->load(game->renderer, "..\\images\\levelCleared.png");
	gameOverText->load(game->renderer, "..\\images\\gameOver.png");
	gameWonText->load(game->renderer, "..\\images\\gameWon.png");
	life->load(game->renderer, "..\\images\\characters1.png", 4, 14);

	
	windowRect.x = windowRect.y = 0;
	windowRect.w = game->getWinW();
	windowRect.h = game->getWinH();	
}

void UserInterface::setLifeSize(){//Cambia el tamaño y la posición de los sprites de vida según el mapa cargado
								  //Para que esté siempre abajo a la izquierda
	lifeRect.w = game->getWinW() / game->getCols();
	lifeRect.h = game->getWinH() / game->getRows();
	lifeRect.x = 0;
	lifeRect.y = game->getWinH() - (game->getWinH() / game->getRows());
}

void UserInterface::renderLives(){//Pinta los sprites de vida

	if (game->pacman->getLives() == 3){//Cuando hay 3 vidas pinta la misma textura 3 veces cambiando su x
		lifeRect.x = 0;
		life->renderFrame(game->renderer, lifeSrcRect, lifeRect, 0, 10);
		lifeRect.x = 0 + game->getWinW() / game->getCols();
		life->renderFrame(game->renderer, lifeSrcRect, lifeRect, 0, 10);
		lifeRect.x = 0 + 2 * game->getWinW() / game->getCols();
		life->renderFrame(game->renderer, lifeSrcRect, lifeRect, 0, 10);
	}
	else if (game->pacman->getLives() == 2){
		lifeRect.x = 0;
		life->renderFrame(game->renderer, lifeSrcRect, lifeRect, 0, 10);
		lifeRect.x = 0 + game->getWinW() / game->getCols();
		life->renderFrame(game->renderer, lifeSrcRect, lifeRect, 0, 10);
	}
	else if (game->pacman->getLives() == 1){
		lifeRect.x = 0;
		life->renderFrame(game->renderer, lifeSrcRect, lifeRect, 0, 10);
	}
}
void UserInterface::menuRender(){//Pinta la pantalla de título
	SDL_RenderClear(game->renderer);
	menuText->render(game->renderer, windowRect);
	SDL_RenderPresent(game->renderer);
}
void UserInterface::nextLevelRender(){//Pinta la pantalla cuando pasas de nivel
	SDL_RenderClear(game->renderer);
	levelCText->render(game->renderer, windowRect);
	SDL_RenderPresent(game->renderer);
}
void UserInterface::gameOverRender(){//Pinta la pantalla de GameOver
	SDL_RenderClear(game->renderer);
	gameOverText->render(game->renderer, windowRect);
	SDL_RenderPresent(game->renderer);
}
void UserInterface::gameWonRender(){//Pinta la pantalla de Victoria
	SDL_RenderClear(game->renderer);
	gameWonText->render(game->renderer, windowRect);
	SDL_RenderPresent(game->renderer);
}


UserInterface::~UserInterface()
{
	delete menuText;
	delete levelCText;
	delete gameOverText;
	delete gameWonText;
	delete life;
}
