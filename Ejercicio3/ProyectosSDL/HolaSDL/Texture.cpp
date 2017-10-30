#include "Texture.h"
#include<string>


Texture::Texture()
{

}


Texture::~Texture()
{
}

bool Texture::load(SDL_Renderer* renderer, string filename, uint numRows = 1, uint numCols = 1){

	SDL_Surface* surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	int tw, th;
	SDL_QueryTexture(texture, nullptr, nullptr, &tw, &th);
		w = tw;
		h = th;
	return true;
}
void Texture::render(SDL_Renderer* renderer, const SDL_Rect& srcRect, const SDL_Rect& destRect, SDL_RendererFlip flip = SDL_FLIP_NONE){
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
void Texture::renderFrame(SDL_Renderer* renderer, SDL_Rect& srcRect , const SDL_Rect& destRect, int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE){
	fw = w / col;
	fh = h / row;
	
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
void Texture::clearRender(SDL_Renderer* renderer){
	SDL_RenderClear(renderer);
}

