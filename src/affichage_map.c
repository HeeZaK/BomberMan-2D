#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../lib/bombe.h"
#include "../lib/affichage_map.h"
#include <unistd.h>
#include <time.h>


void afficherMap(joueur_t j1, joueur_t j2, joueur_t j3, joueur_t j4, int jeu[M][N]) {

  SDL_Window *win = NULL;
  SDL_Renderer *renderer = NULL;

  SDL_Texture *bitmapFond, *bitmapMurI, *bitmapMurC, *bitmapJ1, *bitmapJ2, *bitmapJ3, *bitmapJ4, *bitmapM1;
  SDL_Texture *bitmapBombeJ1, *bitmapBombeJ2, *bitmapBombeJ3, *bitmapBombeJ4;
  SDL_Texture *bitmapPlusBombe, *bitmapVitesse, *bitmapPuissance, *bitmapShield;

  int posX = 100, posY = 100, width = 840, height = 616, w = 56, h = 56;
  SDL_Rect rectMurI, rectMurC, rectJ1, rectJ2, rectJ3, rectJ4, rectM1;
  SDL_Rect bombeJ1, bombeJ2, bombeJ3, bombeJ4;
  SDL_Rect plusBombe, vitesse, puissance, shield;

  int x1=0,y1=0, x2=0,y2=0, x3=0,y3=0, x4=0,y4=0;
  int flagJ1=0, flagJ2=0, flagJ3=0, flagJ4=0;
  clock_t timeOutJ1, timeOutJ2, timeOutJ3, timeOutJ4;

  int bomb_tmp = 0;

  win = SDL_CreateWindow("(= BomberMan =)", posX, posY, width, height, 0);
  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  //

  // Affichage fond
  bitmapFond = IMG_LoadTexture(renderer, "../assets/map/sol1.bmp"); //Fond


  //Initialisation des images
  bitmapMurI = IMG_LoadTexture(renderer, "../assets/map/murincassable1.png"); //MurIncassable
  bitmapMurC = IMG_LoadTexture(renderer, "../assets/map/murcassable1.png");   //MurCassable

  bitmapJ1 = IMG_LoadTexture(renderer, "../assets/bonhomme/rouge/bonhommeAvant.png");  //joueur1
  bitmapJ2 = IMG_LoadTexture(renderer, "../assets/bonhomme/bleu/bonhommeAvant.png");   //joueur2
  bitmapJ3 = IMG_LoadTexture(renderer, "../assets/bonhomme/jaune/bonhommeAvant.png");  //joueur3
  bitmapJ4 = IMG_LoadTexture(renderer, "../assets/bonhomme/vert/bonhommeAvant.png");   //joueur4

  bitmapM1 = IMG_LoadTexture(renderer, "../assets/monstres/petit/monstreAvant.png");   //monstre petit

  bitmapBombeJ1 = IMG_LoadTexture(renderer, "../assets/bombe/bombe_rouge.png");   //bombe J1
  bitmapBombeJ2 = IMG_LoadTexture(renderer, "../assets/bombe/bombe_bleu.png");   //bombe J2
  bitmapBombeJ3 = IMG_LoadTexture(renderer, "../assets/bombe/bombe_jaune.png");   //bombe J3
  bitmapBombeJ4 = IMG_LoadTexture(renderer, "../assets/bombe/bombe_vert.png");   //bombe J4

  bitmapPlusBombe = IMG_LoadTexture(renderer, "../assets/powerups/plusbombe.png");   //PV nombre de bombe augmenté
  bitmapVitesse = IMG_LoadTexture(renderer, "../assets/powerups/plusvitesse.png");   //PV vitesse augmenté
  bitmapPuissance = IMG_LoadTexture(renderer, "../assets/powerups/puissance.png");   //PV puissance augmenté
  bitmapShield = IMG_LoadTexture(renderer, "../assets/powerups/shield.png");   //PV bouclier
  //



    SDL_Event event;
    int continuer = 1;

    while( continuer ){
      SDL_PollEvent(&event); /* On attend un événement qu'on récupère dans event */
      switch (event.type){
        case SDL_KEYDOWN:
        // La touche pressée :
          switch (event.key.keysym.sym) {

            //joueur1
            case SDLK_z:
              deplacerJ(&j1,3,jeu);
              break;
            case SDLK_q:
              deplacerJ(&j1,2,jeu);
              break;
            case SDLK_s:
              deplacerJ(&j1,1,jeu);
              break;
            case SDLK_d:
              deplacerJ(&j1,0,jeu);
              break;
            case SDLK_a:
              if(checkPoseBombe(&j1,jeu)){
                //timeOutJ1 = clock();

                /*for(int i=0; i<M; i++){
                  for(int j=0; j<N; j++){
                    if(jeu[i][j]==j1.id_bombe){
                      x1=i;
                      y1=j;
                    }
                  }
                }*/
              }
              break;

              /*temps_present=SDL_GetTicks();
              if (temps_present > temps_reset + 1000) {
                temps_reset = temps_present;
              }*/

            //joueur2
            case SDLK_t:
              deplacerJ(&j2,3,jeu);
              break;
            case SDLK_f:
              deplacerJ(&j2,2,jeu);
              break;
            case SDLK_g:
              deplacerJ(&j2,1,jeu);
              break;
            case SDLK_h:
              deplacerJ(&j2,0,jeu);
              break;
            case SDLK_r:
              if(checkPoseBombe(&j2,jeu)){
                timeOutJ2 = clock();
                for(int i=0; i<M; i++){
                  for(int j=0; j<N; j++){
                    if(jeu[i][j]==j2.id_bombe){
                      x2=i;
                      y2=j;
                    }
                  }
                }
                flagJ2 = 1;
              }
              break;

            //joueur3
            case SDLK_i:
              deplacerJ(&j3,3,jeu);
              break;
            case SDLK_j:
              deplacerJ(&j3,2,jeu);
              break;
            case SDLK_k:
              deplacerJ(&j3,1,jeu);
              break;
            case SDLK_l:
              deplacerJ(&j3,0,jeu);
              break;
            case SDLK_u:
              if(checkPoseBombe(&j3,jeu)){
                timeOutJ3 = clock();
                for(int i=0; i<M; i++){
                  for(int j=0; j<N; j++){
                    if(jeu[i][j]==j3.id_bombe){
                      x3=i;
                      y3=j;
                    }
                  }
                }
                flagJ3 = 1;
              }
              break;

            //joueur4
            case SDLK_UP:
              deplacerJ(&j4,3,jeu);
              break;
            case SDLK_LEFT:
              deplacerJ(&j4,2,jeu);
              break;
            case SDLK_DOWN:
              deplacerJ(&j4,1,jeu);
              break;
            case SDLK_RIGHT:
              deplacerJ(&j4,0,jeu);
              break;
            case SDLK_RCTRL:
              if(checkPoseBombe(&j4,jeu)){
                timeOutJ4 = clock();
                for(int i=0; i<M; i++){
                  for(int j=0; j<N; j++){
                    if(jeu[i][j]==j4.id_bombe){
                      x4=i;
                      y4=j;
                    }
                  }
                }
                flagJ4 = 1;
              }
              break;
          }
          break;
      }

      for(int i=0; i<j1.nb_bomb; i++){
        if((SDL_GetTicks() > j1.bombe[i].timer + 2000) && j1.bombe[i].timer!=0){
          Detruire(&j1,&j2,&j3,&j4,i,jeu);
          j1.bombe[i].timer=0;
          j1.bombe[i].pos_x=0;
          j1.bombe[i].pos_y=0;
        }
      }




      /*if(flagJ1==1 && (timeOutJ1 + 2000)<clock()){
        Detruire(&j1,&j2,&j3,&j4,x1,y1,jeu);
        flagJ1 = 0;
      }
      if(flagJ2==1 && (timeOutJ2 + 2000)<clock()){
        Detruire(&j2,&j1,&j3,&j4,x2,y2,jeu);
        flagJ2 = 0;
      }
      if(flagJ3==1 && (timeOutJ3 + 2000)<clock()){
        Detruire(&j3,&j2,&j1,&j4,x3,y3,jeu);
        flagJ3 = 0;
      }
      if(flagJ4==1 && (timeOutJ4 + 2000)<clock()){
        Detruire(&j4,&j1,&j3,&j1,x4,y4,jeu);
        flagJ4 = 0;
      }*/

      SDL_RenderCopy(renderer, bitmapFond, NULL, NULL);
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
            case 7:
            rectM1.x = w * j;
            rectM1.y = h * i;
            rectM1.w = w;
            rectM1.h = h;
            SDL_RenderCopy(renderer, bitmapJ4, NULL, &rectM1);
            break;
            case -11:
            bombeJ1.x = w * j;
            bombeJ1.y = h * i;
            bombeJ1.w = w;
            bombeJ1.h = h;
            SDL_RenderCopy(renderer, bitmapBombeJ1, NULL, &bombeJ1);
            break;
            case -12:
            bombeJ2.x = w * j;
            bombeJ2.y = h * i;
            bombeJ2.w = w;
            bombeJ2.h = h;
            SDL_RenderCopy(renderer, bitmapBombeJ2, NULL, &bombeJ2);
            break;
            case -13:
            bombeJ3.x = w * j;
            bombeJ3.y = h * i;
            bombeJ3.w = w;
            bombeJ3.h = h;
            SDL_RenderCopy(renderer, bitmapBombeJ3, NULL, &bombeJ3);
            break;
            case -14:
            bombeJ4.x = w * j;
            bombeJ4.y = h * i;
            bombeJ4.w = w;
            bombeJ4.h = h;
            SDL_RenderCopy(renderer, bitmapBombeJ4, NULL, &bombeJ4);
            break;
            case 3:
            vitesse.x = w * j;
            vitesse.y = h * i;
            vitesse.w = w;
            vitesse.h = h;
            SDL_RenderCopy(renderer, bitmapVitesse, NULL, &vitesse);
            break;
            case 4:
            puissance.x = w * j;
            puissance.y = h * i;
            puissance.w = w;
            puissance.h = h;
            SDL_RenderCopy(renderer, bitmapPuissance, NULL, &puissance);
            break;
            case 5:
            plusBombe.x = w * j;
            plusBombe.y = h * i;
            plusBombe.w = w;
            plusBombe.h = h;
            SDL_RenderCopy(renderer, bitmapPlusBombe, NULL, &plusBombe);
            break;
            case 6:
            shield.x = w * j;
            shield.y = h * i;
            shield.w = w;
            shield.h = h;
            SDL_RenderCopy(renderer, bitmapShield, NULL, &shield);
            break;
          }
        }
      }

      SDL_RenderPresent(renderer); //affichage de tout
      SDL_Delay(1000/60);
      SDL_RenderClear(renderer);
  }

  SDL_DestroyTexture(bitmapFond); //Fond
  SDL_DestroyTexture(bitmapMurI); //Mur Incassable
  SDL_DestroyTexture(bitmapMurC); //Mur MurCassable
  SDL_DestroyTexture(bitmapJ1); // joueur1
  SDL_DestroyTexture(bitmapJ2); // joueur2
  SDL_DestroyTexture(bitmapJ3); // joueur3
  SDL_DestroyTexture(bitmapJ4); // joueur4
  SDL_DestroyTexture(bitmapM1); // monstre petit
  SDL_DestroyTexture(bitmapBombeJ1);
  SDL_DestroyTexture(bitmapBombeJ2);
  SDL_DestroyTexture(bitmapBombeJ3);
  SDL_DestroyTexture(bitmapBombeJ4);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);


}
