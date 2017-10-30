
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
typedef unsigned int uint;

using namespace std;


int main(int argc, char* argv[]){
	
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const int winWidth = 800;
	const int winHeight	= 600;
	SDL_Event event;
	int winX, winY;

		winX=winY=SDL_WINDOWPOS_CENTERED;

		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("My first test with SDL", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (window == nullptr || renderer == nullptr)
			cout << "Error initializing SDL\n";
		else {
			string filename = "..\\images\\background1.png";
			SDL_Surface* surface = IMG_Load(filename.c_str());
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
			SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		    //SDL_RenderPresent(renderer);

			string filenamePerro = "..\\images\\dog.png";
			SDL_Surface* surfacePerro = IMG_Load(filenamePerro.c_str());
			SDL_Texture* texturePerro = SDL_CreateTextureFromSurface(renderer, surfacePerro);

			string filenameHelicopter = "..\\images\\helicopter2.png";
			SDL_Surface* surfaceHelicopter = IMG_Load(filenameHelicopter.c_str());
			SDL_Texture* textureHelicopter = SDL_CreateTextureFromSurface(renderer, surfaceHelicopter);

			//Perro

			int PerroW, PerroH;//Tamaño total de la imagen
			
			SDL_QueryTexture(texturePerro, nullptr, nullptr, &PerroW, &PerroH);
			SDL_Rect srcRectPerro, destRectPerro;		
			


			uint PerroFrameW = PerroW / 6;//Tamaño de los frames
			uint PerroFrameH = PerroH;


			srcRectPerro.w = PerroW / 6;//Divide el ancho de la imagen fuente
			srcRectPerro.h = PerroH;
			srcRectPerro.x = srcRectPerro.y = 0;//Primer frame

			destRectPerro.w = destRectPerro.h = 100;//Tamaño
			destRectPerro.x = 50;//Izquierda
			destRectPerro.y = 450;//Abajo
			SDL_FreeSurface(surfacePerro);
			SDL_RenderCopy(renderer, texturePerro, &srcRectPerro, &destRectPerro);
			//SDL_RenderPresent(renderer);

			//Helicopter

			int HelicopterW, HelicopterH;

			SDL_QueryTexture(textureHelicopter, nullptr, nullptr, &HelicopterW, &HelicopterH);
			SDL_Rect srcRectHelicopter, destRectHelicopter;

			uint HelicopterFrameW = HelicopterW / 5;
			uint HelicopterFrameH = HelicopterH;

			srcRectHelicopter.w = HelicopterW / 5;
			srcRectHelicopter.h = HelicopterH;
			srcRectHelicopter.x = srcRectHelicopter.y = 0;


			destRectHelicopter.w = 150;
			destRectHelicopter.h = 50;
			destRectHelicopter.x = 800;
			destRectHelicopter.y = 100;

			SDL_FreeSurface(surfaceHelicopter);
			SDL_RenderCopy(renderer, textureHelicopter, &srcRectHelicopter, &destRectHelicopter);

			bool salir = false;;
    	while (!salir)
			{
				while (SDL_PollEvent(&event) && !salir){
					if (event.type == SDL_QUIT)
					{
						salir = true;
					}
					
				}
				if (destRectPerro.x > 800){
					destRectPerro.x = -100;
				}
				if (destRectHelicopter.x < -150){
					destRectHelicopter.x = 900;
				}
				srcRectPerro.x = PerroFrameW*int(((SDL_GetTicks() / 100) % 6));
				srcRectHelicopter.x = HelicopterFrameW*int(((SDL_GetTicks() / 100) % 5));
				destRectHelicopter.x--;
				destRectPerro.x += 1;
				SDL_FreeSurface(surface);				
				SDL_FreeSurface(surfacePerro);
				SDL_FreeSurface(surfaceHelicopter);
				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, texture, nullptr, nullptr);
				SDL_RenderCopy(renderer, texturePerro, &srcRectPerro, &destRectPerro);
				SDL_RenderCopy(renderer, textureHelicopter, &srcRectHelicopter, &destRectHelicopter);
				SDL_Delay(5);
				SDL_RenderPresent(renderer);			
			};

			SDL_RenderClear(renderer);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
		}
		SDL_Quit();
	return 0;
}