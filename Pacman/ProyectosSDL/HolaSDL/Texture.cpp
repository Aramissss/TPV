#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
	//delete texture;
}

bool Texture::load(SDL_Renderer* renderer, string filename, uint numRows, uint numCols){

	SDL_Surface* surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);	
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	h = surface->h;
	w = surface->w;
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(surface);
	return true;
}
void Texture::render(SDL_Renderer* renderer, const SDL_Rect& destRect, SDL_RendererFlip flip){
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}
void Texture::renderFrame(SDL_Renderer* renderer, SDL_Rect& srcRect, const SDL_Rect& destRect, int row, int col, SDL_RendererFlip flip){
	srcRect.x = fw*(col);//El rectángulo fuente se posiciona según la columna
	srcRect.y = fh*(row);
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}