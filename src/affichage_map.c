#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../lib/bombe.h"
#include "../lib/affichage_map.h"
#include <unistd.h>
#include <time.h>
#include <string.h>

/**
* \file affichage_map.c
* \brief Ce fichier contient les deux fonctions nécessaires pour l'affichage de la carte de jeu avec les pouvoirs des joueurs qu'ils ont. C'est aussi un fichier qui permet d'actualiser la carte et le score avec les interactions sur la matrice.
* \author Ilango Rémi, Lardais Benjamin, Geslain Simon, Haran Andy
* \date 19 avril 2021
* \version 1
*/


/**
* \fn void afficherScore(joueur_t j1, SDL_Renderer ** renderer, int x, int y, int w, int h, SDL_Color color)
* \brief fonction qui permet d'afficher le score. Affiche les points de vitesses, de puissances, le nombre de bombe, et si le joueur possède un bouclier ou non.
* \param j1 représente le joueur 1
* \param renderer représente l'espace où l'on peut écrire
* \param x représente la ligne dans la matrice
* \param y représente la colonne dans la matrice
* \param w représente la largeur de l'objet affiché
* \param h représente la hauteur de l'objet affiché
* \param color représente la couleur que l'on veut afficher
*/
void afficherScore(joueur_t j1, SDL_Renderer ** renderer, int x, int y, int w, int h, SDL_Color color){  //fonction pour afficher les bonus qu'a le joueur

  SDL_Surface *MMvitesse, *MMpuissance, *MMbombe, *MMshield;
  SDL_Texture *textureMMvitesse, *textureMMpuissance, *textureMMbombe, *textureMMshield;
  SDL_Rect rectVitesse, rectPuissance, rectBombe, rectShield;
  TTF_Font *font = TTF_OpenFont("../assets/fonts/arial.ttf", 300);

  /////////////////////////////// Vitesse ////////////////////////////////////
    char nb_v[1]; // nb_v correspond aux nombres de vitesse qu'a le joueur
    char vitesse[16]= "Vitesse : ";
    sprintf(nb_v,"%i", j1.vitesse);
    strcat(vitesse, nb_v); // nous mettons nb_v dans la chaine de caractères vitesse

          rectVitesse.x = x;
          rectVitesse.y = y;
          rectVitesse.w = w;
          rectVitesse.h = h;

      MMvitesse = TTF_RenderText_Solid(font, vitesse, color);
      textureMMvitesse = SDL_CreateTextureFromSurface(*renderer, MMvitesse);
      SDL_RenderCopy(*renderer, textureMMvitesse, NULL, &rectVitesse);
      SDL_DestroyTexture(textureMMvitesse);
      SDL_FreeSurface(MMvitesse);

//////////////////////////////////////////////////////////////////////////////

/////////////////////////////// Puissance ////////////////////////////////////
    char nb_p[1]; // nb_p correspond aux nombres de puissance qu'a le joueur
    char puissance[16]= "Puissance : ";
    sprintf(nb_p,"%i", j1.puissance);
    strcat(puissance, nb_p); // nous mettons nb_p dans la chaine de caractères vitesse

          rectPuissance.x = x;
          rectPuissance.y = y +30;
          rectPuissance.w = w + 40;
          rectPuissance.h = h;

      MMpuissance = TTF_RenderText_Solid(font, puissance, color);
      textureMMpuissance = SDL_CreateTextureFromSurface(*renderer, MMpuissance);
      SDL_RenderCopy(*renderer, textureMMpuissance, NULL, &rectPuissance);
      SDL_DestroyTexture(textureMMpuissance);
      SDL_FreeSurface(MMpuissance);
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////// Bombe ////////////////////////////////////
   char nb_b[1]; // nb_b correspond aux nombres de bombe qu'a le joueur
   char bombe[16]= "Bombe : ";
   sprintf(nb_b,"%i", j1.nb_bomb);
   strcat(bombe, nb_b); // nous mettons nb_b dans la chaine de caractères vitesse

         rectBombe.x = x;
         rectBombe.y = y+60;
         rectBombe.w = w;
         rectBombe.h = h;

     MMbombe = TTF_RenderText_Solid(font, bombe, color);
     textureMMbombe = SDL_CreateTextureFromSurface(*renderer, MMbombe);
     SDL_RenderCopy(*renderer, textureMMbombe, NULL, &rectBombe);
     SDL_DestroyTexture(textureMMbombe);
     SDL_FreeSurface(MMbombe);
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////// Shield ////////////////////////////////////
  char nb_s[1]; // nb_s correspond aux nombres de bouclier qu'a le joueur
  char shield[16]= "Bouclier : ";
   sprintf(nb_s,"%i", j1.vie);
   strcat(shield, nb_s); // nous mettons nb_s dans la chaine de caractères vitesse

         rectShield.x = x;
         rectShield.y = y+90;
         rectShield.w = w;
         rectShield.h = h;

     MMshield = TTF_RenderText_Solid(font, shield, color);
     textureMMshield = SDL_CreateTextureFromSurface(*renderer, MMshield);
     SDL_RenderCopy(*renderer, textureMMshield, NULL, &rectShield);
     SDL_DestroyTexture(textureMMshield);
     SDL_FreeSurface(MMshield);
//////////////////////////////////////////////////////////////////////////////
TTF_CloseFont(font);
}

/**
* \fn joueur_t * afficherMap(joueur_t j1, joueur_t j2, joueur_t j3, joueur_t j4, int jeu[M][N])
* \brief fonction qui permet d'afficher la matrice avec les joueurs et les pouvoirs
* \param j1 représente le joueur 1
* \param j2 représente le joueur 2
* \param j3 représente le joueur 3
* \param j4 représente le joueur 4
* \param jeu représente la matrice.
* \return retourne le joueur qui a gagné
*/
joueur_t * afficherMap(joueur_t j1, joueur_t j2, joueur_t j3, joueur_t j4, int jeu[M][N]) {

  SDL_Color rouge = {255, 0, 0, 0};
  SDL_Color bleu = {0, 0, 255, 0};
  SDL_Color jaune = {255, 255, 0, 0};
  SDL_Color vert = {0, 128, 0, 0};
  SDL_Window *win = NULL;
  SDL_Renderer *renderer = NULL;


  SDL_Texture *bitmapFond, *bitmapMurI, *bitmapMurC;
  SDL_Texture *bitmapJ1N, *bitmapJ1E, *bitmapJ1S, *bitmapJ1W;
  SDL_Texture *bitmapJ2N, *bitmapJ2E, *bitmapJ2S, *bitmapJ2W;
  SDL_Texture *bitmapJ3N, *bitmapJ3E, *bitmapJ3S, *bitmapJ3W;
  SDL_Texture *bitmapJ4N, *bitmapJ4E, *bitmapJ4S, *bitmapJ4W;
  SDL_Texture *bitmapBombeJ1, *bitmapBombeJ2, *bitmapBombeJ3, *bitmapBombeJ4;
  SDL_Texture *bitmapPlusBombe, *bitmapVitesse, *bitmapPuissance, *bitmapShield;

  int posX = 100, posY = 100, width = 1150, height = 926, w = 56, h = 56;
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
  bitmapJ1N = IMG_LoadTexture(renderer, "../assets/bonhomme/rouge/bonhommeArriere.png"); // position du joueur 1 regardant vers le haut
  bitmapJ1E = IMG_LoadTexture(renderer, "../assets/bonhomme/rouge/bonhommeDroite.png"); // position du joueur 1 regardant vers la droite
  bitmapJ1S = IMG_LoadTexture(renderer, "../assets/bonhomme/rouge/bonhommeAvant.png"); // position du joueur 1 regardant vers le bas
  bitmapJ1W = IMG_LoadTexture(renderer, "../assets/bonhomme/rouge/bonhommeGauche.png"); // position du joueur 1 regardant vers la gauche

  //joueur2
  bitmapJ2N = IMG_LoadTexture(renderer, "../assets/bonhomme/bleu/bonhommeArriere.png"); // position du joueur 2 regardant vers le haut
  bitmapJ2E = IMG_LoadTexture(renderer, "../assets/bonhomme/bleu/bonhommeDroite.png"); // position du joueur 2 regardant vers la droite
  bitmapJ2S = IMG_LoadTexture(renderer, "../assets/bonhomme/bleu/bonhommeAvant.png"); // position du joueur 2 regardant vers le bas
  bitmapJ2W = IMG_LoadTexture(renderer, "../assets/bonhomme/bleu/bonhommeGauche.png"); // position du joueur 2 regardant vers la gauche

  //joueur3
  bitmapJ3N = IMG_LoadTexture(renderer, "../assets/bonhomme/jaune/bonhommeArriere.png"); // position du joueur 3 regardant vers le haut
  bitmapJ3E = IMG_LoadTexture(renderer, "../assets/bonhomme/jaune/bonhommeDroite.png"); // position du joueur 3 regardant vers la droite
  bitmapJ3S = IMG_LoadTexture(renderer, "../assets/bonhomme/jaune/bonhommeAvant.png"); // position du joueur 3 regardant vers le bas
  bitmapJ3W = IMG_LoadTexture(renderer, "../assets/bonhomme/jaune/bonhommeGauche.png"); // position du joueur 3 regardant vers la gauche

  //joueur4
  bitmapJ4N = IMG_LoadTexture(renderer, "../assets/bonhomme/vert/bonhommeArriere.png"); // position du joueur 4 regardant vers le haut
  bitmapJ4E = IMG_LoadTexture(renderer, "../assets/bonhomme/vert/bonhommeDroite.png"); // position du joueur 4 regardant vers la droite
  bitmapJ4S = IMG_LoadTexture(renderer, "../assets/bonhomme/vert/bonhommeAvant.png"); // position du joueur 4 regardant vers le bas
  bitmapJ4W = IMG_LoadTexture(renderer, "../assets/bonhomme/vert/bonhommeGauche.png"); // position du joueur 4 regardant vers la gauche

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

      //Les quatre boucles permettent de faire exploser la bombe 2 secondes après l'avoir posée
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

      //Les quatres if permettent de faire déplacer le joueur en fonction de la vitesse
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

      //retourne un gagnant s'il y en a un
      if((gagnant=verifGagnant(&j1,&j2,&j3,&j4,jeu))!=NULL){
        return(gagnant);
      }

      //Affichage de la carte avec ses éléments
      SDL_RenderCopy(renderer, bitmapFond, NULL, NULL);
      for(int i=0; i<M;i++){
        for(int j=0; j<N;j++){
          switch (jeu[i][j]) {
            case 0:
                                // pas de murs
            break;
            case 1:            //MurIncassable
            rectMurI.x = w * j+150;
            rectMurI.y = h * i+150;
            rectMurI.w = w;
            rectMurI.h = h;
            SDL_RenderCopy(renderer, bitmapMurI, NULL, &rectMurI);
            break;
            case 2:            //MurCassable
            rectMurC.x = w * j+150;
            rectMurC.y = h * i+150;
            rectMurC.w = w;
            rectMurC.h = h;
            SDL_RenderCopy(renderer, bitmapMurC, NULL, &rectMurC);
            break;
            case -1:            //joueur1
              switch(j1.direction){
                case 'N':
                  rectJ1N.x = w * j+150;
                  rectJ1N.y = h * i+150;
                  rectJ1N.w = w;
                  rectJ1N.h = h;
                  SDL_RenderCopy(renderer, bitmapJ1N, NULL, &rectJ1N);
                  break;
                case 'E':
                  rectJ1E.x = w * j+150;
                  rectJ1E.y = h * i+150;
                  rectJ1E.w = w;
                  rectJ1E.h = h;
                  SDL_RenderCopy(renderer, bitmapJ1E, NULL, &rectJ1E);
                  break;
                case 'S':
                  rectJ1S.x = w * j+150;
                  rectJ1S.y = h * i+150;
                  rectJ1S.w = w;
                  rectJ1S.h = h;
                  SDL_RenderCopy(renderer, bitmapJ1S, NULL, &rectJ1S);
                  break;
                case 'W':
                  rectJ1W.x = w * j+150;
                  rectJ1W.y = h * i+150;
                  rectJ1W.w = w;
                  rectJ1W.h = h;
                  SDL_RenderCopy(renderer, bitmapJ1W, NULL, &rectJ1W);
                  break;
              }
              break;
            case -2:             //joueur2
              switch(j2.direction){
                case 'N':
                  rectJ2N.x = w * j+150;
                  rectJ2N.y = h * i+150;
                  rectJ2N.w = w;
                  rectJ2N.h = h;
                  SDL_RenderCopy(renderer, bitmapJ2N, NULL, &rectJ2N);
                  break;
                case 'E':
                  rectJ2E.x = w * j+150;
                  rectJ2E.y = h * i+150;
                  rectJ2E.w = w;
                  rectJ2E.h = h;
                  SDL_RenderCopy(renderer, bitmapJ2E, NULL, &rectJ2E);
                  break;
                case 'S':
                  rectJ2S.x = w * j+150;
                  rectJ2S.y = h * i+150;
                  rectJ2S.w = w;
                  rectJ2S.h = h;
                  SDL_RenderCopy(renderer, bitmapJ2S, NULL, &rectJ2S);
                  break;
                case 'W':
                  rectJ2W.x = w * j+150;
                  rectJ2W.y = h * i+150;
                  rectJ2W.w = w;
                  rectJ2W.h = h;
                  SDL_RenderCopy(renderer, bitmapJ2W, NULL, &rectJ2W);
                  break;
              }
              break;
            case -3:              //joueur3
              switch(j3.direction){
                case 'N':
                  rectJ3N.x = w * j+150;
                  rectJ3N.y = h * i+150;
                  rectJ3N.w = w;
                  rectJ3N.h = h;
                  SDL_RenderCopy(renderer, bitmapJ3N, NULL, &rectJ3N);
                  break;
                case 'E':
                  rectJ3E.x = w * j+150;
                  rectJ3E.y = h * i+150;
                  rectJ3E.w = w;
                  rectJ3E.h = h;
                  SDL_RenderCopy(renderer, bitmapJ3E, NULL, &rectJ3E);
                  break;
                case 'S':
                  rectJ3S.x = w * j+150;
                  rectJ3S.y = h * i+150;
                  rectJ3S.w = w;
                  rectJ3S.h = h;
                  SDL_RenderCopy(renderer, bitmapJ3S, NULL, &rectJ3S);
                  break;
                case 'W':
                  rectJ3W.x = w * j+150;
                  rectJ3W.y = h * i+150;
                  rectJ3W.w = w;
                  rectJ3W.h = h;
                  SDL_RenderCopy(renderer, bitmapJ3W, NULL, &rectJ3W);
                  break;
              }
              break;
            case -4:                //joueur4
              switch(j4.direction){
                case 'N':
                  rectJ4N.x = w * j+150;
                  rectJ4N.y = h * i+150;
                  rectJ4N.w = w;
                  rectJ4N.h = h;
                  SDL_RenderCopy(renderer, bitmapJ4N, NULL, &rectJ4N);
                  break;
                case 'E':
                  rectJ4E.x = w * j+150;
                  rectJ4E.y = h * i+150;
                  rectJ4E.w = w;
                  rectJ4E.h = h;
                  SDL_RenderCopy(renderer, bitmapJ4E, NULL, &rectJ4E);
                  break;
                case 'S':
                  rectJ4S.x = w * j+150;
                  rectJ4S.y = h * i+150;
                  rectJ4S.w = w;
                  rectJ4S.h = h;
                  SDL_RenderCopy(renderer, bitmapJ4S, NULL, &rectJ4S);
                  break;
                case 'W':
                  rectJ4W.x = w * j+150;
                  rectJ4W.y = h * i+150;
                  rectJ4W.w = w;
                  rectJ4W.h = h;
                  SDL_RenderCopy(renderer, bitmapJ4W, NULL, &rectJ4W);
                  break;
              }
            break;
            case -11:
            bombeJ1.x = w * j+150;
            bombeJ1.y = h * i+150;
            bombeJ1.w = w;
            bombeJ1.h = h;
            SDL_RenderCopy(renderer, bitmapBombeJ1, NULL, &bombeJ1);
            break;
            case -12:
            bombeJ2.x = w * j+150;
            bombeJ2.y = h * i+150;
            bombeJ2.w = w;
            bombeJ2.h = h;
            SDL_RenderCopy(renderer, bitmapBombeJ2, NULL, &bombeJ2);
            break;
            case -13:
            bombeJ3.x = w * j+150;
            bombeJ3.y = h * i+150;
            bombeJ3.w = w;
            bombeJ3.h = h;
            SDL_RenderCopy(renderer, bitmapBombeJ3, NULL, &bombeJ3);
            break;
            case -14:
            bombeJ4.x = w * j+150;
            bombeJ4.y = h * i+150;
            bombeJ4.w = w;
            bombeJ4.h = h;
            SDL_RenderCopy(renderer, bitmapBombeJ4, NULL, &bombeJ4);
            break;
            case 3:
            vitesse.x = w * j+150;
            vitesse.y = h * i+150;
            vitesse.w = w;
            vitesse.h = h;
            SDL_RenderCopy(renderer, bitmapVitesse, NULL, &vitesse);
            break;
            case 4:
            puissance.x = w * j+150;
            puissance.y = h * i+150;
            puissance.w = w;
            puissance.h = h;
            SDL_RenderCopy(renderer, bitmapPuissance, NULL, &puissance);
            break;
            case 5:
            plusBombe.x = w * j+150;
            plusBombe.y = h * i+150;
            plusBombe.w = w;
            plusBombe.h = h;
            SDL_RenderCopy(renderer, bitmapPlusBombe, NULL, &plusBombe);
            break;
            case 6:
            shield.x = w * j+150;
            shield.y = h * i+150;
            shield.w = w;
            shield.h = h;
            SDL_RenderCopy(renderer, bitmapShield, NULL, &shield);
            break;
          }
        }
      }


      afficherScore(j1, &renderer, 5, 20, 160, 28, rouge); // on affiche le score pour le joueur 1 à une position donné par rapport a son spawn de départ
      afficherScore(j2, &renderer, 942, 800, 160, 28, bleu); // on affiche le score pour le joueur 2 à une position donné par rapport a son spawn de départ
      afficherScore(j3, &renderer, 5, 800, 160, 28, jaune); // on affiche le score pour le joueur 3 à une position donné par rapport a son spawn de départ
      afficherScore(j4, &renderer, 942, 20, 160, 28, vert); // on affiche le score pour le joueur 4 à une position donné par rapport a son spawn de départ


      SDL_RenderPresent(renderer); //affichage de tout
      SDL_Delay(1000/60);
      SDL_RenderClear(renderer);


  }

  SDL_DestroyTexture(bitmapFond);  // destructions de la texture qui contient le Fond
  SDL_DestroyTexture(bitmapMurI); // destructions de la texture qui contient le Mur Incassable
  SDL_DestroyTexture(bitmapMurC); //destructions de la texture qui contient le Mur MurCassable
  // joueur1
  SDL_DestroyTexture(bitmapJ1N); // destructions de la texture qui contient le joueur 1 regardant vers le haut
  SDL_DestroyTexture(bitmapJ1E); // destructions de la texture qui contient le joueur 1 regardant vers la droite
  SDL_DestroyTexture(bitmapJ1S); // destructions de la texture qui contient le joueur 1 regardant vers le bas
  SDL_DestroyTexture(bitmapJ1W); // destructions de la texture qui contient le joueur 1 regardant vers le gauche

  // joueur2
  SDL_DestroyTexture(bitmapJ2N); // destructions de la texture qui contient le joueur 2 regardant vers le haut
  SDL_DestroyTexture(bitmapJ2E); // destructions de la texture qui contient le joueur 2 regardant vers la droite
  SDL_DestroyTexture(bitmapJ2S); // destructions de la texture qui contient le joueur 2 regardant vers le bas
  SDL_DestroyTexture(bitmapJ2W); // destructions de la texture qui contient le joueur 2 regardant vers le gauche

  // joueur3
  SDL_DestroyTexture(bitmapJ3N); // destructions de la texture qui contient le joueur 3 regardant vers le haut
  SDL_DestroyTexture(bitmapJ3E); // destructions de la texture qui contient le joueur 3 regardant vers la droite
  SDL_DestroyTexture(bitmapJ3S); // destructions de la texture qui contient le joueur 3 regardant vers le bas
  SDL_DestroyTexture(bitmapJ3W); // destructions de la texture qui contient le joueur 3 regardant vers le gauche

  // joueur4
  SDL_DestroyTexture(bitmapJ4N); // destructions de la texture qui contient le joueur 4 regardant vers le haut
  SDL_DestroyTexture(bitmapJ4E); // destructions de la texture qui contient le joueur 4 regardant vers la droite
  SDL_DestroyTexture(bitmapJ4S); // destructions de la texture qui contient le joueur 4 regardant vers le bas
  SDL_DestroyTexture(bitmapJ4W); // destructions de la texture qui contient le joueur 4 regardant vers le gauche

  // bombes joueurs
  SDL_DestroyTexture(bitmapBombeJ1); // destructions de la texture qui contient la bombe joueur 1
  SDL_DestroyTexture(bitmapBombeJ2); // destructions de la texture qui contient la bombe joueur 2
  SDL_DestroyTexture(bitmapBombeJ3); // destructions de la texture qui contient la bombe joueur 3
  SDL_DestroyTexture(bitmapBombeJ4); // destructions de la texture qui contient la bombe joueur 4

  // Bonus
  SDL_DestroyTexture(bitmapPlusBombe); //destructions de la texture qui contient le bonus plus de bombe
  SDL_DestroyTexture(bitmapVitesse); // destructions de la texture qui contient le bonus vitesse
  SDL_DestroyTexture(bitmapPuissance); // destructions de la texture qui contient le bonus puissance
  SDL_DestroyTexture(bitmapShield); // destructions de la texture qui contient le bonus bouclier





  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);


}
