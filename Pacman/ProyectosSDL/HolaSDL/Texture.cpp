#include "Texture.h"


Texture::Texture()
{
}
Texture::~Texture()
{
}
bool Texture::load(SDL_Renderer* renderer, string filename, uint numRows, uint numCols){//Carga la textura a parti de un archivo

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
void Texture::render(SDL_Renderer* renderer, const SDL_Rect& destRect, SDL_RendererFlip flip){//Copia la textura al render
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}
void Texture::renderFrame(SDL_Renderer* renderer, SDL_Rect& srcRect, const SDL_Rect& destRect, int row, int col, SDL_RendererFlip flip){//Pinta un frame determinado
	srcRect.x = fw*(col);//El rectángulo fuente se posiciona según la columna
	srcRect.y = fh*(row);
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}