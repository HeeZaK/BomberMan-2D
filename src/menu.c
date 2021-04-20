#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../lib/bombe.h"
#include "../lib/affichage_map.h"
#include "../lib/menu.h"

/**
* \file menu.c
* \brief Ce fichier regroupe les différents menus qui permet de choisir les options que nous voulons. Il y a aussi tous les affichages textes qui ne sont pas sur la carte de jeu.
* \author Ilango Rémi, Lardais Benjamin, Geslain Simon, Haran Andy
* \date 19 avril 2021
* \version 1
*/


/**
*\fn int menu()
*\brief Cette fonction affiche un menu qui propose trois choix, le mode multijoueur, le mode ou exit pour quitter.
*\return Une valeur comprise entre 1 et 3 qui correspond au mode choisit et -1 si l'utilisateur décide de fermer la fenêtre.
*/
int menu(){
  TTF_Init();
  int val = 1; //1 : mode multi, 2 : mode solo, 3 : exit
  //Création de la fenêtre et du rendu
  int posX = 100, posY = 100, width = 840, height = 616;
  SDL_Window* win = NULL;
  win = SDL_CreateWindow("Menu", posX, posY, width, height, 0);

  SDL_Renderer *pRenderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);

  if(pRenderer){

      int continuer = 1;
      SDL_Event event;

      //Initialisation de la police d'écriture :
      TTF_Font *font = TTF_OpenFont("../assets/fonts/Mermaid1001.ttf", 35);

      SDL_Surface *MMorange, *MMblanc, *MSorange, *MSblanc, *ExitOrange, *ExitBlanc;
      SDL_Texture *textureMMorange, *textureMMblanc, *textureMSorange, *textureMSblanc, *textureExitOrange, *textureExitBlanc;
      SDL_Rect rect;
      SDL_Color blanc = {255, 255, 255, 0};
      SDL_Color orange = {255, 165, 0, 0};

      //Les différents textes affichés peuvent être de deux couleurs différentes
      MMorange = TTF_RenderText_Solid(font, "Mode multijoueur", orange);
      MMblanc = TTF_RenderText_Solid(font, "Mode multijoueur", blanc);
      textureMMorange = SDL_CreateTextureFromSurface(pRenderer, MMorange);
      textureMMblanc = SDL_CreateTextureFromSurface(pRenderer, MMblanc);

      MSorange = TTF_RenderText_Solid(font, "Mode solo", orange);
      MSblanc = TTF_RenderText_Solid(font, "Mode solo", blanc);
      textureMSorange = SDL_CreateTextureFromSurface(pRenderer, MSorange);
      textureMSblanc = SDL_CreateTextureFromSurface(pRenderer, MSblanc);

      ExitOrange = TTF_RenderText_Solid(font, "Exit", orange);
      ExitBlanc = TTF_RenderText_Solid(font, "Exit", blanc);
      textureExitOrange = SDL_CreateTextureFromSurface(pRenderer, ExitOrange);
      textureExitBlanc = SDL_CreateTextureFromSurface(pRenderer, ExitBlanc);


      //Boucle qui permet d'actualiser l'affichage en fonction de l'interaction
      while (continuer) {
          SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

          while (SDL_PollEvent(&event)) {
              switch (event.type) {
                //fermer la fenêtre
                case SDL_QUIT:
                  continuer=0;
                  return(-1);
                  break;

                case SDL_KEYDOWN:
                // La touche pressée :
                  switch (event.key.keysym.sym) {

                    case SDLK_UP:
                      if(val==1)
                        val = 3;
                      else
                        val--;
                      break;
                    case SDLK_DOWN:
                      if(val==3)
                        val = 1;
                      else
                        val++;
                      break;
                    case SDLK_RETURN:
                      continuer=0;
                      break;
                  }
                  break;
              }
          }

          //Affiche les textes de la bonne couleur en fonction du mode sélectionné
          if(val==1){
            rect.x = 200 - ((MMorange->w)/2);
            rect.y = 100 - ((MMorange->h)/2);
            rect.w = MMorange->w;
            rect.h = MMorange->h;
            SDL_RenderCopy(pRenderer, textureMMorange, NULL, &rect);

            rect.x = 200 - ((MSblanc->w)/2);
            rect.y = 200 - ((MSblanc->h)/2);
            rect.w = MSblanc->w;
            rect.h = MSblanc->h;
            SDL_RenderCopy(pRenderer, textureMSblanc, NULL, &rect);

            rect.x = 200 - ((ExitBlanc->w)/2);
            rect.y = 300 - ((ExitBlanc->h)/2);
            rect.w = ExitBlanc->w;
            rect.h = ExitBlanc->h;
            SDL_RenderCopy(pRenderer, textureExitBlanc, NULL, &rect);
          }
          else if(val==2){
            rect.x = 200 - ((MMblanc->w)/2);
            rect.y = 100 - ((MMblanc->h)/2);
            rect.w = MMblanc->w;
            rect.h = MMblanc->h;
            SDL_RenderCopy(pRenderer, textureMMblanc, NULL, &rect);

            rect.x = 200 - ((MSorange->w)/2);
            rect.y = 200 - ((MSorange->h)/2);
            rect.w = MSorange->w;
            rect.h = MSorange->h;
            SDL_RenderCopy(pRenderer, textureMSorange, NULL, &rect);

            rect.x = 200 - ((ExitBlanc->w)/2);
            rect.y = 300 - ((ExitBlanc->h)/2);
            rect.w = ExitBlanc->w;
            rect.h = ExitBlanc->h;
            SDL_RenderCopy(pRenderer, textureExitBlanc, NULL, &rect);
          }
          else if(val==3){
            rect.x = 200 - ((MMblanc->w)/2);
            rect.y = 100 - ((MMblanc->h)/2);
            rect.w = MMblanc->w;
            rect.h = MMblanc->h;
            SDL_RenderCopy(pRenderer, textureMMblanc, NULL, &rect);

            rect.x = 200 - ((MSblanc->w)/2);
            rect.y = 200 - ((MSblanc->h)/2);
            rect.w = MSblanc->w;
            rect.h = MSblanc->h;
            SDL_RenderCopy(pRenderer, textureMSblanc, NULL, &rect);

            rect.x = 200 - ((ExitOrange->w)/2);
            rect.y = 300 - ((ExitOrange->h)/2);
            rect.w = ExitOrange->w;
            rect.h = ExitOrange->h;
            SDL_RenderCopy(pRenderer, textureExitOrange, NULL, &rect);
          }



          SDL_RenderPresent(pRenderer);
          SDL_RenderClear(pRenderer);
      }

      //Destruction de toutes les textures
      SDL_DestroyTexture(textureMMorange);
      SDL_DestroyTexture(textureMMblanc);
      SDL_DestroyTexture(textureMSorange);
      SDL_DestroyTexture(textureMSblanc);
      SDL_DestroyTexture(textureExitOrange);
      SDL_DestroyTexture(textureExitBlanc);

      //Libération de toutes les surfaces
      SDL_FreeSurface(MMorange);
      SDL_FreeSurface(MMblanc);
      SDL_FreeSurface(MSorange);
      SDL_FreeSurface(MSblanc);
      SDL_FreeSurface(ExitOrange);
      SDL_FreeSurface(ExitBlanc);
      //Libération mémoire du rendu

      SDL_DestroyRenderer(pRenderer);
  }
  else{
      fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
      exit(EXIT_FAILURE);
  }

  if(win){

      //Libération mémoire de la fenêtre
      SDL_DestroyWindow(win);
  }
  else{
      fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
      exit(EXIT_FAILURE);
  }
  return (val);
}

/**
*\fn int menuMultijoueur()
*\brief Cette fonction affiche un menu qui propose trois choix pour le nombre de joueur, 2, 3 ou 4.
*\return Une valeur comprise entre 2 et 4 qui correspond au mode choisit et -1 si l'utilisateur décide de fermer la fenêtre.
*/

int menuMultijoueur(){
  TTF_Init();
  int val = 2 ; // valeur du nombre de joueur
  //Création de la fenêtre et du rendu
  int posX = 100, posY = 100, width = 840, height = 616;
  SDL_Window* win = NULL;
  win = SDL_CreateWindow("Menu", posX, posY, width, height, 0);

  SDL_Renderer *pRenderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);


  if(pRenderer){


      int continuer = 1;
      SDL_Event event;

      //Initialisation de la police d'écriture :
      TTF_Font *font = TTF_OpenFont("../assets/fonts/Mermaid1001.ttf", 35);

      SDL_Surface *surface, *deuxOrange, *deuxBlanc, *troisOrange, *troisBlanc, *quatreOrange, *quatreBlanc;
      SDL_Texture *texture, *textureDeuxOrange, *textureDeuxBlanc, *textureTroisOrange, *textureTroisBlanc, *textureQuatreOrange, *textureQuatreBlanc;
      SDL_Rect rect;
      SDL_Color blanc = {255, 255, 255, 0};
      SDL_Color orange = {255, 165, 0, 0};

      //Les différents textes affichés peuvent être de deux couleurs différentes sauf pour "Nombre de joueur :"
      surface = TTF_RenderText_Solid(font, "Nombre de joueur :", orange);
      texture = SDL_CreateTextureFromSurface(pRenderer, surface);

      deuxOrange = TTF_RenderText_Solid(font, "2", orange);
      deuxBlanc = TTF_RenderText_Solid(font, "2", blanc);
      textureDeuxOrange = SDL_CreateTextureFromSurface(pRenderer, deuxOrange);
      textureDeuxBlanc = SDL_CreateTextureFromSurface(pRenderer, deuxBlanc);

      troisOrange = TTF_RenderText_Solid(font, "3", orange);
      troisBlanc = TTF_RenderText_Solid(font, "3", blanc);
      textureTroisOrange = SDL_CreateTextureFromSurface(pRenderer, troisOrange);
      textureTroisBlanc = SDL_CreateTextureFromSurface(pRenderer, troisBlanc);

      quatreOrange = TTF_RenderText_Solid(font, "4", orange);
      quatreBlanc = TTF_RenderText_Solid(font, "4", blanc);
      textureQuatreOrange = SDL_CreateTextureFromSurface(pRenderer, quatreOrange);
      textureQuatreBlanc = SDL_CreateTextureFromSurface(pRenderer, quatreBlanc);

      //Boucle qui permet d'actualiser l'affichage en fonction de l'interaction
      while (continuer) {
          SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

          while (SDL_PollEvent(&event)) {
              switch (event.type) {
                //fermer la fenêtre
                case SDL_QUIT:
                  continuer=0;
                  return(-1);
                  break;

                case SDL_KEYDOWN:
                // La touche pressée :
                  switch (event.key.keysym.sym) {

                    case SDLK_LEFT:
                      if(val==2)
                        val = 4;
                      else
                        val--;
                      break;
                    case SDLK_RIGHT:
                      if(val==4)
                        val = 2;
                      else
                        val++;
                      break;
                    case SDLK_RETURN:
                      continuer=0;
                      break;
                  }
                  break;
              }
          }


          //Affiche le texte "Nombre de joueur :" en orange
          rect.x = 200 - ((surface->w)/2);
          rect.y = 200 - ((surface->h)/2);
          rect.w = surface->w;
          rect.h = surface->h;
          SDL_RenderCopy(pRenderer, texture, NULL, &rect);

          //Affiche les textes de la bonne couleur en fonction du mode sélectionné
          if(val==2){
            rect.x = 400 - ((deuxOrange->w)/2);
            rect.y = 200 - ((deuxOrange->h)/2);
            rect.w = deuxOrange->w;
            rect.h = deuxOrange->h;
            SDL_RenderCopy(pRenderer, textureDeuxOrange, NULL, &rect);

            rect.x = 500 - ((troisBlanc->w)/2);
            rect.y = 200 - ((troisBlanc->h)/2);
            rect.w = troisBlanc->w;
            rect.h = troisBlanc->h;
            SDL_RenderCopy(pRenderer, textureTroisBlanc, NULL, &rect);

            rect.x = 600 - ((quatreBlanc->w)/2);
            rect.y = 200 - ((quatreBlanc->h)/2);
            rect.w = quatreBlanc->w;
            rect.h = quatreBlanc->h;
            SDL_RenderCopy(pRenderer, textureQuatreBlanc, NULL, &rect);
          }
          else if(val==3){
            rect.x = 400 - ((deuxBlanc->w)/2);
            rect.y = 200 - ((deuxBlanc->h)/2);
            rect.w = deuxBlanc->w;
            rect.h = deuxBlanc->h;
            SDL_RenderCopy(pRenderer, textureDeuxBlanc, NULL, &rect);

            rect.x = 500 - ((troisOrange->w)/2);
            rect.y = 200 - ((troisOrange->h)/2);
            rect.w = troisOrange->w;
            rect.h = troisOrange->h;
            SDL_RenderCopy(pRenderer, textureTroisOrange, NULL, &rect);

            rect.x = 600 - ((quatreBlanc->w)/2);
            rect.y = 200 - ((quatreBlanc->h)/2);
            rect.w = quatreBlanc->w;
            rect.h = quatreBlanc->h;
            SDL_RenderCopy(pRenderer, textureQuatreBlanc, NULL, &rect);
          }
          else if(val==4){
            rect.x = 400 - ((deuxBlanc->w)/2);
            rect.y = 200 - ((deuxBlanc->h)/2);
            rect.w = deuxBlanc->w;
            rect.h = deuxBlanc->h;
            SDL_RenderCopy(pRenderer, textureDeuxBlanc, NULL, &rect);

            rect.x = 500 - ((troisBlanc->w)/2);
            rect.y = 200 - ((troisBlanc->h)/2);
            rect.w = troisBlanc->w;
            rect.h = troisBlanc->h;
            SDL_RenderCopy(pRenderer, textureTroisBlanc, NULL, &rect);

            rect.x = 600 - ((quatreOrange->w)/2);
            rect.y = 200 - ((quatreOrange->h)/2);
            rect.w = quatreOrange->w;
            rect.h = quatreOrange->h;
            SDL_RenderCopy(pRenderer, textureQuatreOrange, NULL, &rect);
          }


          SDL_RenderPresent(pRenderer);
          SDL_RenderClear(pRenderer);
      }
      //Destruction de toutes les textures
      SDL_DestroyTexture(textureDeuxOrange);
      SDL_DestroyTexture(texture);
      SDL_DestroyTexture(textureDeuxBlanc);
      SDL_DestroyTexture(textureTroisOrange);
      SDL_DestroyTexture(textureTroisBlanc);
      SDL_DestroyTexture(textureQuatreOrange);
      SDL_DestroyTexture(textureQuatreBlanc);

      //Libération de toutes les surfaces
      SDL_FreeSurface(surface);
      SDL_FreeSurface(deuxOrange);
      SDL_FreeSurface(deuxBlanc);
      SDL_FreeSurface(troisOrange);
      SDL_FreeSurface(troisBlanc);
      SDL_FreeSurface(quatreOrange);
      SDL_FreeSurface(quatreBlanc);

      //Libération mémoire du rendu

      SDL_DestroyRenderer(pRenderer);
  }
  else{
      fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
      exit(EXIT_FAILURE);
  }

  if(win){

      //Libération mémoire de la fenêtre
      SDL_DestroyWindow(win);
  }
  else{
      fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
      exit(EXIT_FAILURE);
  }

  return(val);
}


/**
*\fn int lancerPartieMulti(int nb_joueur)
*\brief Cette fonction lance une partie en mutlijoueur local en fonction du nombre de joueur sélectionné dans le menu.
*\param int nb_joueur correspond au nombre de joueur qui joue
*\return  L'identifiant du gagnant qui a réussi à éliminer tout ses adversaires.
*/

int lancerPartieMulti(int nb_joueur){
  int jeu[M][N];
  joueur_t * gagnant;

  //Initialisation des bombes
  bombe_t bombe_vide[9];

  //Initialisation d'un joueur qui ne sera pas sur la carte, nécessaire lorsqu'il y a moins de quatre joueurs
  joueur_t joueurNULL = {0, -1, -1, 'E', 0, 0, 0, 0, 0, 0, bombe_vide};

  //Initialisation des quatre joueurs
  joueur_t joueur1 = {-1, 1, 1, 'E', 0, 0, 0, 1, 1, -11, bombe_vide};
  joueur_t joueur2 = {-2, 9, 13, 'W', 0, 0, 0, 1, 1, -12, bombe_vide};
  joueur_t joueur3 = {-3, 9, 1, 'E', 0, 0, 0, 1, 1, -13, bombe_vide};
  joueur_t joueur4 = {-4, 1, 13, 'W',0, 0, 0, 1, 1, -14, bombe_vide};


  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  //Initialisation de la matrice
  innitMatrice(jeu);
  placerMurIncassable(jeu);
  placerMurCassable(jeu, 85);


  //Place les joueurs sur la matrice en fonction de leur positions.
  switch(nb_joueur){
    case 2:
      joueur3 = joueurNULL;
      joueur4 = joueurNULL;
      //Placer les joueurs sur la map
      jeu[joueur1.pos_x][joueur1.pos_y]=joueur1.id;
      jeu[joueur2.pos_x][joueur2.pos_y]=joueur2.id;
      break;
    case 3:
      joueur4 = joueurNULL;

      //Placer les joueurs sur la map
      jeu[joueur1.pos_x][joueur1.pos_y]=joueur1.id;
      jeu[joueur2.pos_x][joueur2.pos_y]=joueur2.id;
      jeu[joueur3.pos_x][joueur3.pos_y]=joueur3.id;
      break;
    case 4:

      //Placer les joueurs sur la map
      jeu[joueur1.pos_x][joueur1.pos_y]=joueur1.id;
      jeu[joueur2.pos_x][joueur2.pos_y]=joueur2.id;
      jeu[joueur3.pos_x][joueur3.pos_y]=joueur3.id;
      jeu[joueur4.pos_x][joueur4.pos_y]=joueur4.id;
      break;
  }

  //Lancement de la partie avec la fonction afficherMap qui va retourner le gagnant
  gagnant = afficherMap(joueur1, joueur2, joueur3, joueur4, jeu);

  if(gagnant!=NULL){
    return (gagnant->id)*(-1);
  }
  else{
    return 0;
  }
}

/**
*\fn void afficheGagnant(int id_joueur)
*\brief Cette fonction affiche le gagnant à l'écran
*\param int id_joueur, identifiant du joueur qui a gagné la partie
*/
void afficheGagnant(int id_joueur){

  TTF_Init();
  //Création de la fenêtre et du rendu
  int posX = 100, posY = 100, width = 840, height = 616;
  SDL_Window* win = NULL;
  win = SDL_CreateWindow("Bomberman 2D", posX, posY, width, height, 0);

  SDL_Renderer *pRenderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);

  if(pRenderer){

      //Initialisation de la police d'écriture :
      TTF_Font *font = TTF_OpenFont("../assets/fonts/Mermaid1001.ttf", 35);

      SDL_Surface *vJ1, *vJ2, *vJ3, *vJ4, *erreur, *perdu;
      SDL_Texture *textureVJ1, *textureVJ2, *textureVJ3, *textureVJ4, *textureErreur, *texturePerdu;
      SDL_Rect rect;
      SDL_Color blanc = {255, 255, 255, 0};
      SDL_Color rouge = {255, 0, 0, 0};
      SDL_Color bleu = {0, 0, 205, 0};
      SDL_Color jaune = {255, 255, 0, 0};
      SDL_Color vert = {0, 255, 0, 0};

      //Initialisation des textes en fonction du joueur
      vJ1 = TTF_RenderText_Solid(font, "Victoire du joueur 1!", rouge);
      textureVJ1 = SDL_CreateTextureFromSurface(pRenderer, vJ1);
      vJ2 = TTF_RenderText_Solid(font, "Victoire du joueur 2!", bleu);
      textureVJ2 = SDL_CreateTextureFromSurface(pRenderer, vJ2);
      vJ3 = TTF_RenderText_Solid(font, "Victoire du joueur 3!", jaune);
      textureVJ3 = SDL_CreateTextureFromSurface(pRenderer, vJ3);
      vJ4 = TTF_RenderText_Solid(font, "Victoire du joueur 4!", vert);
      textureVJ4 = SDL_CreateTextureFromSurface(pRenderer, vJ4);
      perdu = TTF_RenderText_Solid(font, "T'as perdu contre les monstres...", blanc);
      texturePerdu = SDL_CreateTextureFromSurface(pRenderer, perdu);
      erreur = TTF_RenderText_Solid(font, "Erreur! Personne n'a gagne...", blanc);
      textureErreur = SDL_CreateTextureFromSurface(pRenderer, erreur);

      int continuer = 1;
      SDL_Event event;

      while (continuer) {
          SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

          while (SDL_PollEvent(&event)) {
              switch (event.type) {
                //fermer la fenêtre
                case SDL_QUIT:
                  continuer=0;
                  break;
              }
          }

          //Affiche les textes en fonction du mode gagnant
          switch(id_joueur){
            case 1:
              rect.x = 200 - ((vJ1->w)/2);
              rect.y = 200 - ((vJ1->h)/2);
              rect.w = vJ1->w;
              rect.h = vJ1->h;
              SDL_RenderCopy(pRenderer, textureVJ1, NULL, &rect);
              break;
            case 2:
              rect.x = 200 - ((vJ2->w)/2);
              rect.y = 200 - ((vJ2->h)/2);
              rect.w = vJ2->w;
              rect.h = vJ2->h;
              SDL_RenderCopy(pRenderer, textureVJ2, NULL, &rect);
              break;
            case 3:
              rect.x = 200 - ((vJ3->w)/2);
              rect.y = 200 - ((vJ3->h)/2);
              rect.w = vJ3->w;
              rect.h = vJ3->h;
              SDL_RenderCopy(pRenderer, textureVJ3, NULL, &rect);
              break;
            case 4:
              rect.x = 200 - ((vJ4->w)/2);
              rect.y = 200 - ((vJ4->h)/2);
              rect.w = vJ4->w;
              rect.h = vJ4->h;
              SDL_RenderCopy(pRenderer, textureVJ4, NULL, &rect);
              break;
            case 0:
              rect.x = 300 - ((perdu->w)/2);
              rect.y = 200 - ((perdu->h)/2);
              rect.w = perdu->w;
              rect.h = perdu->h;
              SDL_RenderCopy(pRenderer, texturePerdu, NULL, &rect);
              break;
            default:
              rect.x = 300 - ((erreur->w)/2);
              rect.y = 200 - ((erreur->h)/2);
              rect.w = erreur->w;
              rect.h = erreur->h;
              SDL_RenderCopy(pRenderer, textureErreur, NULL, &rect);
              break;
          }
          SDL_RenderPresent(pRenderer);
      }

      SDL_DestroyTexture(textureVJ1);
      SDL_DestroyTexture(textureVJ2);
      SDL_DestroyTexture(textureVJ3);
      SDL_DestroyTexture(textureVJ4);
      SDL_DestroyTexture(textureErreur);
      SDL_DestroyTexture(texturePerdu);

      SDL_FreeSurface(vJ1);
      SDL_FreeSurface(vJ2);
      SDL_FreeSurface(vJ3);
      SDL_FreeSurface(vJ4);
      SDL_FreeSurface(erreur);
      SDL_FreeSurface(perdu);

      //Libération mémoire du rendu

      SDL_DestroyRenderer(pRenderer);
  }
  else{
      fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
      exit(EXIT_FAILURE);
  }

  if(win){

      //Libération mémoire de la fenêtre
      SDL_DestroyWindow(win);
  }
  else{
      fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
      exit(EXIT_FAILURE);
  }

}


/**
*\fn int menuSolo()
*\brief Cette fonction affiche un menu qui propose trois choix pour le niveau contre les monstres, 1, 2 ou 3.
*\return Une valeur comprise entre 1 et 3 qui correspond au niveau choisit et -1 si l'utilisateur décide de fermer la fenêtre.
*/
int menuSolo(){
  TTF_Init();
  int val = 1 ; // valeur du nombre de joueur
  //Création de la fenêtre et du rendu
  int posX = 100, posY = 100, width = 840, height = 616;
  SDL_Window* win = NULL;
  win = SDL_CreateWindow("Menu", posX, posY, width, height, 0);

  SDL_Renderer *pRenderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);

  if(pRenderer){

      //Programme du jeu
      int continuer = 1;
      SDL_Event event;

      //Initialisation de la police d'écriture :
      TTF_Font *font = TTF_OpenFont("../assets/fonts/Mermaid1001.ttf", 35);

      SDL_Surface *surface, *unOrange, *unBlanc, *deuxOrange, *deuxBlanc, *troisOrange, *troisBlanc;
      SDL_Texture *texture, *textureUnOrange, *textureUnBlanc, *textureDeuxOrange, *textureDeuxBlanc, *textureTroisOrange, *textureTroisBlanc;
      SDL_Rect rect;
      SDL_Color blanc = {255, 255, 255, 0};
      SDL_Color orange = {255, 165, 0, 0};

      //Les différents textes affichés peuvent être de deux couleurs différentes sauf pour "Choix du niveau :"
      surface = TTF_RenderText_Solid(font, "Choix du niveau :", orange);
      texture = SDL_CreateTextureFromSurface(pRenderer, surface);

      unOrange = TTF_RenderText_Solid(font, "1", orange);
      unBlanc = TTF_RenderText_Solid(font, "1", blanc);
      textureUnOrange = SDL_CreateTextureFromSurface(pRenderer, unOrange);
      textureUnBlanc = SDL_CreateTextureFromSurface(pRenderer, unBlanc);

      deuxOrange = TTF_RenderText_Solid(font, "2", orange);
      deuxBlanc = TTF_RenderText_Solid(font, "2", blanc);
      textureDeuxOrange = SDL_CreateTextureFromSurface(pRenderer, deuxOrange);
      textureDeuxBlanc = SDL_CreateTextureFromSurface(pRenderer, deuxBlanc);

      troisOrange = TTF_RenderText_Solid(font, "3", orange);
      troisBlanc = TTF_RenderText_Solid(font, "3", blanc);
      textureTroisOrange = SDL_CreateTextureFromSurface(pRenderer, troisOrange);
      textureTroisBlanc = SDL_CreateTextureFromSurface(pRenderer, troisBlanc);


      while (continuer) {
          SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

          while (SDL_PollEvent(&event)) {
              switch (event.type) {
                //fermer la fenêtre
                case SDL_QUIT:
                  continuer=0;
                  return(-1);
                  break;

                case SDL_KEYDOWN:
                // La touche pressée :
                  switch (event.key.keysym.sym) {

                    case SDLK_LEFT:
                      if(val==1)
                        val = 3;
                      else
                        val--;
                      break;
                    case SDLK_RIGHT:
                      if(val==3)
                        val = 2;
                      else
                        val++;
                      break;
                    case SDLK_RETURN:
                      continuer=0;
                      break;
                  }
                  break;
              }
          }

          //Affiche le texte "Choix du niveau :" en orange
          rect.x = 200 - ((surface->w)/2);
          rect.y = 200 - ((surface->h)/2);
          rect.w = surface->w;
          rect.h = surface->h;
          SDL_RenderCopy(pRenderer, texture, NULL, &rect);

          //Affiche les textes de la bonne couleur en fonction du mode sélectionné
          if(val==1){
            rect.x = 400 - ((unOrange->w)/2);
            rect.y = 200 - ((unOrange->h)/2);
            rect.w = unOrange->w;
            rect.h = unOrange->h;
            SDL_RenderCopy(pRenderer, textureUnOrange, NULL, &rect);

            rect.x = 500 - ((deuxBlanc->w)/2);
            rect.y = 200 - ((deuxBlanc->h)/2);
            rect.w = deuxBlanc->w;
            rect.h = deuxBlanc->h;
            SDL_RenderCopy(pRenderer, textureDeuxBlanc, NULL, &rect);

            rect.x = 600 - ((troisBlanc->w)/2);
            rect.y = 200 - ((troisBlanc->h)/2);
            rect.w = troisBlanc->w;
            rect.h = troisBlanc->h;
            SDL_RenderCopy(pRenderer, textureTroisBlanc, NULL, &rect);
          }
          else if(val==2){
            rect.x = 400 - ((unBlanc->w)/2);
            rect.y = 200 - ((unBlanc->h)/2);
            rect.w = unBlanc->w;
            rect.h = unBlanc->h;
            SDL_RenderCopy(pRenderer, textureUnBlanc, NULL, &rect);

            rect.x = 500 - ((deuxOrange->w)/2);
            rect.y = 200 - ((deuxOrange->h)/2);
            rect.w = deuxOrange->w;
            rect.h = deuxOrange->h;
            SDL_RenderCopy(pRenderer, textureDeuxOrange, NULL, &rect);

            rect.x = 600 - ((troisBlanc->w)/2);
            rect.y = 200 - ((troisBlanc->h)/2);
            rect.w = troisBlanc->w;
            rect.h = troisBlanc->h;
            SDL_RenderCopy(pRenderer, textureTroisBlanc, NULL, &rect);
          }
          else if(val==3){
            rect.x = 400 - ((unBlanc->w)/2);
            rect.y = 200 - ((unBlanc->h)/2);
            rect.w = unBlanc->w;
            rect.h = unBlanc->h;
            SDL_RenderCopy(pRenderer, textureUnBlanc, NULL, &rect);

            rect.x = 500 - ((deuxBlanc->w)/2);
            rect.y = 200 - ((deuxBlanc->h)/2);
            rect.w = deuxBlanc->w;
            rect.h = deuxBlanc->h;
            SDL_RenderCopy(pRenderer, textureDeuxBlanc, NULL, &rect);

            rect.x = 600 - ((troisOrange->w)/2);
            rect.y = 200 - ((troisOrange->h)/2);
            rect.w = troisOrange->w;
            rect.h = troisOrange->h;
            SDL_RenderCopy(pRenderer, textureTroisOrange, NULL, &rect);
          }



          SDL_RenderPresent(pRenderer);
          SDL_RenderClear(pRenderer);
      }

      //Destruction de toutes les textures
      SDL_DestroyTexture(texture);
      SDL_DestroyTexture(textureUnOrange);
      SDL_DestroyTexture(textureUnBlanc);
      SDL_DestroyTexture(textureDeuxOrange);
      SDL_DestroyTexture(textureDeuxBlanc);
      SDL_DestroyTexture(textureTroisOrange);
      SDL_DestroyTexture(textureTroisBlanc);

      //Libération de toutes les surfaces
      SDL_FreeSurface(surface);
      SDL_FreeSurface(unOrange);
      SDL_FreeSurface(unBlanc);
      SDL_FreeSurface(deuxOrange);
      SDL_FreeSurface(deuxBlanc);
      SDL_FreeSurface(troisOrange);
      SDL_FreeSurface(troisBlanc);

      //Libération mémoire du rendu

      SDL_DestroyRenderer(pRenderer);
  }
  else{
      fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
      exit(EXIT_FAILURE);
  }

  if(win){

      //Libération mémoire de la fenêtre
      SDL_DestroyWindow(win);
  }
  else{
      fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
      exit(EXIT_FAILURE);
  }

  return(val);
}
