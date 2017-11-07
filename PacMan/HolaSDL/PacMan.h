#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h";
using namespace std;

class Game;

class PacMan
{
private:
	uint w, h;
	uint x;
	uint y;
	int dirX;
	int dirY;
	uint row, col;
	Texture* texture;//Puntero a la textura
	Game* game;//Puntero al juego
	SDL_Rect destRect, srcRect;
public:
	PacMan(Texture* texture, Game* game);
	~PacMan();
	void render();
	void update();
};