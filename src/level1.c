#include <stdio.h>
#include <stdlib.h>
#include "../lib/SDL2/SDL.h"
#include "../lib/SDL2/SDL_ttf.h"
#include "../lib/SDL2/SDL_image.h"
#include <unistd.h>
#include <time.h>
#define N 17
#define M 13

// vider la map totalement
void innitMatrice(int jeu[M][N]){
  for(int i=0; i<M;i++){
    for(int j=0; j<N;j++){
      jeu[i][j]=0;
    }
  }
}
// placer les murs incassable de la map
void placerMurIncassable(int jeu[M][N]){
  for(int i=0; i<M;i++){
    for(int j=0; j<N;j++){
      if(j==0 || i==0 || j==N-1 || i==M-1){  //on place les murs indestructible sur les bords
        jeu[i][j]=1;
      }
      else if(i%2==0 && j%2==0){  // on place les murs indestructible toutes les deux cases
        jeu[i][j]=1;
      }
    }
  }
}
// placer les murs cassable de la map
void placerMurCassable(int jeu[M][N]){
  for(int i=1; i<M-1;i++){
    for(int j=1; j<N-1;j++){
      if(jeu[i][j]==0){
        if(rand()%100 < 45){
          jeu[i][j]=2;
        }
      }
    }
  }

  //place par défaut pour spawn dans les coins de la map
  jeu[1][1]=0;
  jeu[1][2]=0;
  jeu[2][1]=0;

  jeu[M-2][N-2]=0;
  jeu[M-3][N-2]=0;
  jeu[M-2][N-3]=0;

  jeu[1][N-2]=0;
  jeu[1][N-3]=0;
  jeu[2][N-2]=0;

  jeu[M-2][1]=0;
  jeu[M-2][2]=0;
  jeu[M-3][1]=0;

  //place par défaut les spawns des joueurs

  jeu[1][1]=-1; // joueur 1

  //place par défaut les spawns des monstres IA

  jeu[9][6]=0; // espace libre
  jeu[9][7]=7; // position monstre
  jeu[9][8]=0; // espace libre




}
// afficher la map dans le cmd
void afficherMatrice(int jeu[M][N]){
  for(int i=0; i<M;i++){
    for(int j=0; j<N;j++){
      switch (jeu[i][j]) {
        case 0:
          printf("○ "); // pas de murs
          break;
        case 1:
          printf("● "); // murs pleins
          break;
        case 2:
          printf("# "); // murs creux
          break;
        case -1:
          printf("1 "); // joueur1
          break;
        case -2:
          printf("2 "); // joueur2
          break;
        case -3:
          printf("3 "); // joueur3
          break;
        case -4:
          printf("4 "); // joueur4
          break;
        case 7:
          printf("7 "); // Monstres 1
          break;
        break;
      }
    }printf("\n");
  }
}


int main(int argc, char *argv[]) {
    int jeu[M][N];
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *bitmapFond, *bitmapMurI, *bitmapMurC, *bitmapJ1, *bitmapM1 = NULL;
    int posX = 100, posY = 100, width = 952, height = 728, w = 56, h = 56;
    SDL_Rect rectMurI, rectMurC, rectJ1, rectM1;


    // Initialisation de l'ecran SDL
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("(= BomberMan =)", posX, posY, width, height, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    //

    // Affichage fond
    bitmapFond = IMG_LoadTexture(renderer, "../assets/map/sol.png"); //MurIncassable
    SDL_RenderCopy(renderer, bitmapFond, NULL, NULL);
    //

    // afficher la map dans le cmd

    //Matrice
    innitMatrice(jeu);
    placerMurIncassable(jeu);
    placerMurCassable(jeu);
    //

    //Initialisation des images
    bitmapMurI = IMG_LoadTexture(renderer, "../assets/map/murincassable1.png"); //MurIncassable
    bitmapMurC = IMG_LoadTexture(renderer, "../assets/map/murcassable1.png");   //MurCassable
    bitmapJ1 = IMG_LoadTexture(renderer, "../assets/bonhomme/rouge/bonhommeAvant.png");  //joueur1
    bitmapM1 = IMG_LoadTexture(renderer, "../assets/monstres/petit/monstreAvant.png");  //Monstre
    //

      for(int i=0; i<M;i++){
        for(int j=0; j<N;j++){
          switch (jeu[i][j]) {
            case 0:
                                // pas de murs
            break;
            case 1:            //MurIncassable
            rectMurI.x = w * j;
            rectMurI.y = h * i;
            rectMurI.w = w;
            rectMurI.h = h;
            SDL_RenderCopy(renderer, bitmapMurI, NULL, &rectMurI);
            break;
            case 2:            //MurCassable
            rectMurC.x = w * j;
            rectMurC.y = h * i;
            rectMurC.w = w;
            rectMurC.h = h;
            SDL_RenderCopy(renderer, bitmapMurC, NULL, &rectMurC);
            break;
            case -1:            //joueur1
            rectJ1.x = w * j;
            rectJ1.y = h * i;
            rectJ1.w = w;
            rectJ1.h = h;
            SDL_RenderCopy(renderer, bitmapJ1, NULL, &rectJ1);
            break;
            case 7:            //Monstre
            rectJ1.x = w * j;
            rectJ1.y = h * i;
            rectJ1.w = w;
            rectJ1.h = h;
            SDL_RenderCopy(renderer, bitmapM1, NULL, &rectM1);
            break;
          break;
          }
        }printf("\n");
      }

    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }
    SDL_RenderPresent(renderer); //affichage de tout
    }

    SDL_DestroyTexture(bitmapFond); //Fond
    SDL_DestroyTexture(bitmapMurI); //Mur Incassable
    SDL_DestroyTexture(bitmapMurC); //Mur MurCassable
    SDL_DestroyTexture(bitmapJ1); // joueur1
    SDL_DestroyTexture(bitmapM1); // joueur1


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
