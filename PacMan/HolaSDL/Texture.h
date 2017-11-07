#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>

typedef unsigned int uint;

using namespace std;
class Texture
{
private:
	SDL_Texture* texture = nullptr;

	int w = 0;
	int h = 0;
	uint fw = 0;
	uint fh = 0;

public:
	Texture();
	~Texture();
	bool load(SDL_Renderer* renderer, string filename, uint numRows = 1, uint numCols = 1);
	void render(SDL_Renderer* renderer, const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderFrame(SDL_Renderer* renderer, SDL_Rect& srcRect, const SDL_Rect& destRect, int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE);
};
