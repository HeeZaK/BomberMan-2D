#include <stdio.h>
#include <stdlib.h>
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/matriceBombe.h"



int main(int argc, char *argv[]) {
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *bitmapTex = NULL;
    SDL_Surface *bitmapSurface = NULL;
		SDL_Texture *bitmapPerso = NULL;
    SDL_Surface *Perso = NULL;
    int posX = 100, posY = 100, width = 840, height = 600;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);



    bitmapSurface = SDL_LoadBMP("../image/sol.bmp");
    bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
    SDL_FreeSurface(bitmapSurface);

		Perso = IMG_Load("../image/bonhomme.png");
		bitmapPerso = SDL_CreateTextureFromSurface(renderer, Perso);
    SDL_FreeSurface(Perso);

    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
				SDL_RenderCopy(renderer, bitmapPerso, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(bitmapTex);
		SDL_DestroyTexture(bitmapPerso);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}
