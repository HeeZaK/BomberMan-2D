#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../lib/matriceBombe.h"
#include "../lib/bombe.h"
#include <unistd.h>
#include <time.h>

int main(int argc, char ** argv){
  int jeu[M][N];

  bombe_t bombe_vide[9];

  joueur_t j1 = {-1, 1, 1, 'E', 0, 0, 0, 1, 1, -11, bombe_vide};

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* win = NULL;
  win = SDL_CreateWindow("Fenêtre inutile", 0, 0, 0, 0, 0); //nécessaire pour faire fonctionner l'interaction avec les touches

  //Initialisation de la matrice
  innitMatrice(jeu);
  placerMurIncassable(jeu);


  jeu[j1.pos_x][j1.pos_y]=j1.id;

  afficherMatrice(jeu);

  SDL_Event event;
  int continuer = 1;

  while( continuer ){
    SDL_PollEvent(&event); /* On attend un événement qu'on récupère dans event */
    switch (event.type){
      //fermer la fenêtre
      case SDL_QUIT:
        continuer = 0;
        break;

      case SDL_KEYDOWN:
      // La touche pressée :
        switch (event.key.keysym.sym) {
          printf("Affichage menu choisit : \n");
          //joueur1
          case SDLK_z:
              deplacerJ(&j1,3,jeu);
              afficherMatrice(jeu);
            break;
          case SDLK_q:
              deplacerJ(&j1,2,jeu);
              afficherMatrice(jeu);
            break;
          case SDLK_s:
              deplacerJ(&j1,1,jeu);
              afficherMatrice(jeu);
            break;
          case SDLK_d:
              deplacerJ(&j1,0,jeu);
              afficherMatrice(jeu);
            break;
        }
        break;
    }
  }

  SDL_Quit();
}
