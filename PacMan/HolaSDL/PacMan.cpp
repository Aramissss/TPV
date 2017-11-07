#include "PacMan.h"
#include "Game.h"


PacMan::PacMan(Texture*  tex, Game* gm)
{
	texture = tex;
	game = gm;
	x = destRect.x;
	y= destRect.y;
	w= destRect.w;
	h =destRect.h;
}


PacMan::~PacMan()
{
	delete texture;
	delete game;
}

void PacMan::render()
{
	texture->renderFrame(game->renderer, srcRect ,destRect, row, col);
}
void PacMan::update()
{

}