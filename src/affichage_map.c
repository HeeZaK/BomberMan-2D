#include <stdio.h>
#include <stdlib.h>
#include "../lib/SDL2/SDL.h"
#include "../lib/SDL2/SDL_ttf.h"
#include "../lib/SDL2/SDL_image.h"
#include "../lib/matriceBombe.h"
#include <unistd.h>
#include <time.h>
#define N 15
#define M 11

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
        if(rand()%100 < 88){
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
  jeu[1][13]=-2; // joueur 2
  jeu[9][13]=-3; // joueur 3
  jeu[9][1]=-4; // joueur 4


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
        break;
      }
    }printf("\n");
  }
}


int main(int argc, char *argv[]) {
    int jeu[M][N];
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *bitmapFond, *bitmapMurI, *bitmapMurC, *bitmapJ1, *bitmapJ2, *bitmapJ3, *bitmapJ4 = NULL;
    int posX = 100, posY = 100, width = 840, height = 616, w = 56, h = 56;
    SDL_Rect rectMurI, rectMurC, rectJ1, rectJ2, rectJ3, rectJ4;


    // Initialisation de l'ecran SDL
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("(= BomberMan =)", posX, posY, width, height, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    //

    // Affichage fond
    bitmapFond = IMG_LoadTexture(renderer, "../assets/map/sol.png"); //Fond
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
    bitmapJ2 = IMG_LoadTexture(renderer, "../assets/bonhomme/bleu/bonhommeAvant.png");   //joueur2
    bitmapJ3 = IMG_LoadTexture(renderer, "../assets/bonhomme/jaune/bonhommeAvant.png");  //joueur3
    bitmapJ4 = IMG_LoadTexture(renderer, "../assets/bonhomme/vert/bonhommeAvant.png");   //joueur4
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
            case -2:             //joueur2
            rectJ2.x = w * j;
            rectJ2.y = h * i;
            rectJ2.w = w;
            rectJ2.h = h;
            SDL_RenderCopy(renderer, bitmapJ2, NULL, &rectJ2);
            break;
            case -3:              //joueur3
            rectJ3.x = w * j;
            rectJ3.y = h * i;
            rectJ3.w = w;
            rectJ3.h = h;
            SDL_RenderCopy(renderer, bitmapJ3, NULL, &rectJ3);
            break;
            case -4:                //joueur4
            rectJ4.x = w * j;
            rectJ4.y = h * i;
            rectJ4.w = w;
            rectJ4.h = h;
            SDL_RenderCopy(renderer, bitmapJ4, NULL, &rectJ4);
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
    SDL_DestroyTexture(bitmapJ2); // joueur2
    SDL_DestroyTexture(bitmapJ3); // joueur3
    SDL_DestroyTexture(bitmapJ4); // joueur4

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
