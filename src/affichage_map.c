#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../lib/bombe.h"
#include "../lib/affichage_map.h"
#include <unistd.h>
#include <time.h>


joueur_t * afficherMap(joueur_t j1, joueur_t j2, joueur_t j3, joueur_t j4, int jeu[M][N]) {

  SDL_Window *win = NULL;
  SDL_Renderer *renderer = NULL;

  SDL_Texture *bitmapFond, *bitmapMurI, *bitmapMurC;
  SDL_Texture *bitmapJ1N, *bitmapJ1E, *bitmapJ1S, *bitmapJ1W;
  SDL_Texture *bitmapJ2N, *bitmapJ2E, *bitmapJ2S, *bitmapJ2W;
  SDL_Texture *bitmapJ3N, *bitmapJ3E, *bitmapJ3S, *bitmapJ3W;
  SDL_Texture *bitmapJ4N, *bitmapJ4E, *bitmapJ4S, *bitmapJ4W;
  SDL_Texture *bitmapBombeJ1, *bitmapBombeJ2, *bitmapBombeJ3, *bitmapBombeJ4;
  SDL_Texture *bitmapPlusBombe, *bitmapVitesse, *bitmapPuissance, *bitmapShield;

  int posX = 100, posY = 100, width = 840, height = 616, w = 56, h = 56;
  SDL_Rect rectMurI, rectMurC;
  SDL_Rect rectJ1N, rectJ1E, rectJ1S, rectJ1W;
  SDL_Rect rectJ2N, rectJ2E, rectJ2S, rectJ2W;
  SDL_Rect rectJ3N, rectJ3E, rectJ3S, rectJ3W;
  SDL_Rect rectJ4N, rectJ4E, rectJ4S, rectJ4W;
  SDL_Rect bombeJ1, bombeJ2, bombeJ3, bombeJ4;
  SDL_Rect plusBombe, vitesse, puissance, shield;

  joueur_t * gagnant=NULL;

  win = SDL_CreateWindow("(= BomberMan =)", posX, posY, width, height, 0);
  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  //

  // Affichage fond
  bitmapFond = IMG_LoadTexture(renderer, "../assets/map/sol1.bmp"); //Fond


  //Initialisation des images
  bitmapMurI = IMG_LoadTexture(renderer, "../assets/map/murincassable1.png"); //MurIncassable
  bitmapMurC = IMG_LoadTexture(renderer, "../assets/map/murcassable1.png");   //MurCassable

  //joueur1
  bitmapJ1N = IMG_LoadTexture(renderer, "../assets/bonhomme/rouge/bonhommeArriere.png");
  bitmapJ1E = IMG_LoadTexture(renderer, "../assets/bonhomme/rouge/bonhommeDroite.png");
  bitmapJ1S = IMG_LoadTexture(renderer, "../assets/bonhomme/rouge/bonhommeAvant.png");
  bitmapJ1W = IMG_LoadTexture(renderer, "../assets/bonhomme/rouge/bonhommeGauche.png");

  //joueur2
  bitmapJ2N = IMG_LoadTexture(renderer, "../assets/bonhomme/bleu/bonhommeArriere.png");
  bitmapJ2E = IMG_LoadTexture(renderer, "../assets/bonhomme/bleu/bonhommeDroite.png");
  bitmapJ2S = IMG_LoadTexture(renderer, "../assets/bonhomme/bleu/bonhommeAvant.png");
  bitmapJ2W = IMG_LoadTexture(renderer, "../assets/bonhomme/bleu/bonhommeGauche.png");

  //joueur3
  bitmapJ3N = IMG_LoadTexture(renderer, "../assets/bonhomme/jaune/bonhommeArriere.png");
  bitmapJ3E = IMG_LoadTexture(renderer, "../assets/bonhomme/jaune/bonhommeDroite.png");
  bitmapJ3S = IMG_LoadTexture(renderer, "../assets/bonhomme/jaune/bonhommeAvant.png");
  bitmapJ3W = IMG_LoadTexture(renderer, "../assets/bonhomme/jaune/bonhommeGauche.png");

  //joueur4
  bitmapJ4N = IMG_LoadTexture(renderer, "../assets/bonhomme/vert/bonhommeArriere.png");
  bitmapJ4E = IMG_LoadTexture(renderer, "../assets/bonhomme/vert/bonhommeDroite.png");
  bitmapJ4S = IMG_LoadTexture(renderer, "../assets/bonhomme/vert/bonhommeAvant.png");
  bitmapJ4W = IMG_LoadTexture(renderer, "../assets/bonhomme/vert/bonhommeGauche.png");

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
        //fermer la fenêtre
        case SDL_QUIT:
          return NULL;
          break;

        case SDL_KEYDOWN:
        // La touche pressée :
          switch (event.key.keysym.sym) {

            //joueur1
            case SDLK_z:
              if(j1.timer==0)
                deplacerJ(&j1,3,jeu);
              break;
            case SDLK_q:
              if(j1.timer==0)
                deplacerJ(&j1,2,jeu);
              break;
            case SDLK_s:
              if(j1.timer==0)
                deplacerJ(&j1,1,jeu);
              break;
            case SDLK_d:
              if(j1.timer==0)
                deplacerJ(&j1,0,jeu);
              break;
            case SDLK_a:
              if(checkPoseBombe(&j1,jeu)){
              }
              break;
            case SDLK_e:
              //changer rotation
              if(j1.timer==0)
                changerRotaJoueur(&j1);
              break;

            //joueur2
            case SDLK_t:
              if(j2.timer==0)
                deplacerJ(&j2,3,jeu);
              break;
            case SDLK_f:
              if(j2.timer==0)
                deplacerJ(&j2,2,jeu);
              break;
            case SDLK_g:
              if(j2.timer==0)
                deplacerJ(&j2,1,jeu);
              break;
            case SDLK_h:
              if(j2.timer==0)
                deplacerJ(&j2,0,jeu);
              break;
            case SDLK_r:
              if(checkPoseBombe(&j2,jeu)){
              }
              break;
            case SDLK_y:
              //changer rotation
              if(j2.timer==0)
                changerRotaJoueur(&j2);
              break;

            //joueur3
            case SDLK_i:
              if(j3.timer==0)
                deplacerJ(&j3,3,jeu);
              break;
            case SDLK_j:
              if(j3.timer==0)
                deplacerJ(&j3,2,jeu);
              break;
            case SDLK_k:
              if(j3.timer==0)
                deplacerJ(&j3,1,jeu);
              break;
            case SDLK_l:
              if(j3.timer==0)
                deplacerJ(&j3,0,jeu);
              break;
            case SDLK_u:
              if(checkPoseBombe(&j3,jeu)){
              }
              break;
            case SDLK_o:
              //changer rotation
              if(j3.timer==0)
                changerRotaJoueur(&j3);
              break;

            //joueur4
            case SDLK_UP:
              if(j4.timer==0)
                deplacerJ(&j4,3,jeu);
              break;
            case SDLK_LEFT:
              if(j4.timer==0)
                deplacerJ(&j4,2,jeu);
              break;
            case SDLK_DOWN:
              if(j4.timer==0)
                deplacerJ(&j4,1,jeu);
              break;
            case SDLK_RIGHT:
              if(j4.timer==0)
                deplacerJ(&j4,0,jeu);
              break;
            case SDLK_RCTRL:
              if(checkPoseBombe(&j4,jeu)){
              }
              break;
            case SDLK_RSHIFT:
              //changer rotation
              if(j4.timer==0)
                changerRotaJoueur(&j4);
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

      for(int i=0; i<j2.nb_bomb; i++){
        if((SDL_GetTicks() > j2.bombe[i].timer + 2000) && j2.bombe[i].timer!=0){
          Detruire(&j2,&j1,&j3,&j4,i,jeu);
          j2.bombe[i].timer=0;
          j2.bombe[i].pos_x=0;
          j2.bombe[i].pos_y=0;
        }
      }

      for(int i=0; i<j3.nb_bomb; i++){
        if((SDL_GetTicks() > j3.bombe[i].timer + 2000) && j3.bombe[i].timer!=0){
          Detruire(&j3,&j1,&j2,&j4,i,jeu);
          j3.bombe[i].timer=0;
          j3.bombe[i].pos_x=0;
          j3.bombe[i].pos_y=0;
        }
      }

      for(int i=0; i<j4.nb_bomb; i++){
        if((SDL_GetTicks() > j4.bombe[i].timer + 2000) && j4.bombe[i].timer!=0){
          Detruire(&j4,&j1,&j3,&j2,i,jeu);
          j4.bombe[i].timer=0;
          j4.bombe[i].pos_x=0;
          j4.bombe[i].pos_y=0;
        }
      }

      if(j1.timer!=0 && (SDL_GetTicks() > j1.timer + 1000 - (100*j1.vitesse))){
        j1.timer=0;
      }

      if(j2.timer!=0 && (SDL_GetTicks() > j2.timer + 1000 - (100*j2.vitesse))){
        j2.timer=0;
      }

      if(j3.timer!=0 && (SDL_GetTicks() > j3.timer + 1000 - (100*j3.vitesse))){
        j3.timer=0;
      }

      if(j4.timer!=0 && (SDL_GetTicks() > j4.timer + 1000 - (100*j4.vitesse))){
        j4.timer=0;
      }


      if((gagnant=verifGagnant(&j1,&j2,&j3,&j4,jeu))!=NULL){
        return(gagnant);
      }

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
              switch(j1.direction){
                case 'N':
                  rectJ1N.x = w * j;
                  rectJ1N.y = h * i;
                  rectJ1N.w = w;
                  rectJ1N.h = h;
                  SDL_RenderCopy(renderer, bitmapJ1N, NULL, &rectJ1N);
                  break;
                case 'E':
                  rectJ1E.x = w * j;
                  rectJ1E.y = h * i;
                  rectJ1E.w = w;
                  rectJ1E.h = h;
                  SDL_RenderCopy(renderer, bitmapJ1E, NULL, &rectJ1E);
                  break;
                case 'S':
                  rectJ1S.x = w * j;
                  rectJ1S.y = h * i;
                  rectJ1S.w = w;
                  rectJ1S.h = h;
                  SDL_RenderCopy(renderer, bitmapJ1S, NULL, &rectJ1S);
                  break;
                case 'W':
                  rectJ1W.x = w * j;
                  rectJ1W.y = h * i;
                  rectJ1W.w = w;
                  rectJ1W.h = h;
                  SDL_RenderCopy(renderer, bitmapJ1W, NULL, &rectJ1W);
                  break;
              }
              break;
            case -2:             //joueur2
              switch(j2.direction){
                case 'N':
                  rectJ2N.x = w * j;
                  rectJ2N.y = h * i;
                  rectJ2N.w = w;
                  rectJ2N.h = h;
                  SDL_RenderCopy(renderer, bitmapJ2N, NULL, &rectJ2N);
                  break;
                case 'E':
                  rectJ2E.x = w * j;
                  rectJ2E.y = h * i;
                  rectJ2E.w = w;
                  rectJ2E.h = h;
                  SDL_RenderCopy(renderer, bitmapJ2E, NULL, &rectJ2E);
                  break;
                case 'S':
                  rectJ2S.x = w * j;
                  rectJ2S.y = h * i;
                  rectJ2S.w = w;
                  rectJ2S.h = h;
                  SDL_RenderCopy(renderer, bitmapJ2S, NULL, &rectJ2S);
                  break;
                case 'W':
                  rectJ2W.x = w * j;
                  rectJ2W.y = h * i;
                  rectJ2W.w = w;
                  rectJ2W.h = h;
                  SDL_RenderCopy(renderer, bitmapJ2W, NULL, &rectJ2W);
                  break;
              }
              break;
            case -3:              //joueur3
              switch(j3.direction){
                case 'N':
                  rectJ3N.x = w * j;
                  rectJ3N.y = h * i;
                  rectJ3N.w = w;
                  rectJ3N.h = h;
                  SDL_RenderCopy(renderer, bitmapJ3N, NULL, &rectJ3N);
                  break;
                case 'E':
                  rectJ3E.x = w * j;
                  rectJ3E.y = h * i;
                  rectJ3E.w = w;
                  rectJ3E.h = h;
                  SDL_RenderCopy(renderer, bitmapJ3E, NULL, &rectJ3E);
                  break;
                case 'S':
                  rectJ3S.x = w * j;
                  rectJ3S.y = h * i;
                  rectJ3S.w = w;
                  rectJ3S.h = h;
                  SDL_RenderCopy(renderer, bitmapJ3S, NULL, &rectJ3S);
                  break;
                case 'W':
                  rectJ3W.x = w * j;
                  rectJ3W.y = h * i;
                  rectJ3W.w = w;
                  rectJ3W.h = h;
                  SDL_RenderCopy(renderer, bitmapJ3W, NULL, &rectJ3W);
                  break;
              }
              break;
            case -4:                //joueur4
              switch(j4.direction){
                case 'N':
                  rectJ4N.x = w * j;
                  rectJ4N.y = h * i;
                  rectJ4N.w = w;
                  rectJ4N.h = h;
                  SDL_RenderCopy(renderer, bitmapJ4N, NULL, &rectJ4N);
                  break;
                case 'E':
                  rectJ4E.x = w * j;
                  rectJ4E.y = h * i;
                  rectJ4E.w = w;
                  rectJ4E.h = h;
                  SDL_RenderCopy(renderer, bitmapJ4E, NULL, &rectJ4E);
                  break;
                case 'S':
                  rectJ4S.x = w * j;
                  rectJ4S.y = h * i;
                  rectJ4S.w = w;
                  rectJ4S.h = h;
                  SDL_RenderCopy(renderer, bitmapJ4S, NULL, &rectJ4S);
                  break;
                case 'W':
                  rectJ4W.x = w * j;
                  rectJ4W.y = h * i;
                  rectJ4W.w = w;
                  rectJ4W.h = h;
                  SDL_RenderCopy(renderer, bitmapJ4W, NULL, &rectJ4W);
                  break;
              }
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
  // joueur1
  SDL_DestroyTexture(bitmapJ1N);
  SDL_DestroyTexture(bitmapJ1E);
  SDL_DestroyTexture(bitmapJ1S);
  SDL_DestroyTexture(bitmapJ1W);

  // joueur2
  SDL_DestroyTexture(bitmapJ2N);
  SDL_DestroyTexture(bitmapJ2E);
  SDL_DestroyTexture(bitmapJ2S);
  SDL_DestroyTexture(bitmapJ2W);

  // joueur3
  SDL_DestroyTexture(bitmapJ3N);
  SDL_DestroyTexture(bitmapJ3E);
  SDL_DestroyTexture(bitmapJ3S);
  SDL_DestroyTexture(bitmapJ3W);

  // joueur4
  SDL_DestroyTexture(bitmapJ4N);
  SDL_DestroyTexture(bitmapJ4E);
  SDL_DestroyTexture(bitmapJ4S);
  SDL_DestroyTexture(bitmapJ4W);

  SDL_DestroyTexture(bitmapBombeJ1);
  SDL_DestroyTexture(bitmapBombeJ2);
  SDL_DestroyTexture(bitmapBombeJ3);
  SDL_DestroyTexture(bitmapBombeJ4);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);


}
