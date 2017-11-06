#include "Dog.h"


Dog::Dog()
{
	x = 100;
	y = 100;
	w = 100;
	h = 100;
	destRect.x = x;
	destRect.y = y;
	destRect.w = w;
	destRect.h = h;
	dirX = 1;
}


Dog::~Dog()
{
}
void Dog::render() {
	texture->renderFrame(game->renderer, texture->srcRect, destRect, row, col);
}
void Dog::update() {
	x = (x + dirX) % 800;
}
