#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../lib/bombe.h"
#include "../lib/affichage_map.h"
#include "../lib/menu.h"

int menu(){
  TTF_Init();
  int val = 1; //1 : mode multi, 2 : mode solo, 3 : exit
  //Création de la fenêtre et du rendu
  int posX = 100, posY = 100, width = 840, height = 616;
  SDL_Window* win = NULL;
  win = SDL_CreateWindow("Menu", posX, posY, width, height, 0);

  SDL_Renderer *pRenderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);

  if(pRenderer){

      //Programme du jeu
      int continuer = 1;
      SDL_Event event;

      TTF_Font *font = TTF_OpenFont("../assets/fonts/Mermaid1001.ttf", 35);

      SDL_Surface *MMorange, *MMblanc, *MSorange, *MSblanc, *ExitOrange, *ExitBlanc;
      SDL_Texture *textureMMorange, *textureMMblanc, *textureMSorange, *textureMSblanc, *textureExitOrange, *textureExitBlanc;
      SDL_Rect rect;
      SDL_Color blanc = {255, 255, 255, 0};
      SDL_Color orange = {255, 165, 0, 0};

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



      while (continuer) {
          SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

          while (SDL_PollEvent(&event)) {
              switch (event.type) {
                //fermer la fenêtre
                case SDL_QUIT:
                  continuer=0;
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

      SDL_DestroyTexture(textureMMorange);
      SDL_DestroyTexture(textureMMblanc);
      SDL_DestroyTexture(textureMSorange);
      SDL_DestroyTexture(textureMSblanc);
      SDL_DestroyTexture(textureExitOrange);
      SDL_DestroyTexture(textureExitBlanc);
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


int menuMultijoueur(){
  TTF_Init();
  int val = 2 ; // valeur du nombre de joueur
  //Création de la fenêtre et du rendu
  int posX = 100, posY = 100, width = 840, height = 616;
  SDL_Window* win = NULL;
  win = SDL_CreateWindow("Menu", posX, posY, width, height, 0);

  SDL_Renderer *pRenderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);


  if(pRenderer){

      //Programme du jeu
      int continuer = 1;
      SDL_Event event;

      TTF_Font *font = TTF_OpenFont("../assets/fonts/Mermaid1001.ttf", 35);

      SDL_Surface *surface, *deuxOrange, *deuxBlanc, *troisOrange, *troisBlanc, *quatreOrange, *quatreBlanc;
      SDL_Texture *texture, *textureDeuxOrange, *textureDeuxBlanc, *textureTroisOrange, *textureTroisBlanc, *textureQuatreOrange, *textureQuatreBlanc;
      SDL_Rect rect;
      SDL_Color blanc = {255, 255, 255, 0};
      SDL_Color orange = {255, 165, 0, 0};

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


      while (continuer) {
          SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

          while (SDL_PollEvent(&event)) {
              switch (event.type) {
                //fermer la fenêtre
                case SDL_QUIT:
                  continuer=0;
                  return(0);
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


          rect.x = 200 - ((surface->w)/2);
          rect.y = 200 - ((surface->h)/2);
          rect.w = surface->w;
          rect.h = surface->h;
          SDL_RenderCopy(pRenderer, texture, NULL, &rect);

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

      SDL_DestroyTexture(textureDeuxOrange);
      SDL_DestroyTexture(textureDeuxBlanc);
      SDL_DestroyTexture(textureTroisOrange);
      SDL_DestroyTexture(textureTroisBlanc);
      SDL_DestroyTexture(textureQuatreOrange);
      SDL_DestroyTexture(textureQuatreBlanc);

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


int lancerPartieMulti(int nb_joueur){
  int jeu[M][N];
  joueur_t * gagnant;

  bombe_t bombe_vide[9];
  joueur_t joueurNULL = {0, -1, -1, 'E', 0, 0, 0, 0, 0, 0, bombe_vide};

  joueur_t joueur1 = {-1, 1, 1, 'E', 0, 0, 0, 1, 1, -11, bombe_vide};
  joueur_t joueur2 = {-2, 9, 13, 'W', 0, 0, 0, 1, 1, -12, bombe_vide};
  joueur_t joueur3 = {-3, 9, 1, 'E', 0, 0, 0, 1, 1, -13, bombe_vide};
  joueur_t joueur4 = {-4, 1, 13, 'W',0, 0, 0, 1, 1, -14, bombe_vide};


  SDL_Init(SDL_INIT_VIDEO);


  innitMatrice(jeu);
  placerMurIncassable(jeu);
  placerMurCassable(jeu, 85);


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

  gagnant = afficherMap(joueur1, joueur2, joueur3, joueur4, jeu);

  //Faire écran de victoire
  if(gagnant!=NULL){
    return (gagnant->id)*(-1);
  }
  else{
    return 0;
  }
}

void afficheGagnant(int id_joueur){

  TTF_Init();
  //Création de la fenêtre et du rendu
  int posX = 100, posY = 100, width = 840, height = 616;
  SDL_Window* win = NULL;
  win = SDL_CreateWindow("Menu", posX, posY, width, height, 0);

  SDL_Renderer *pRenderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);

  if(pRenderer){

      TTF_Font *font = TTF_OpenFont("../assets/fonts/Mermaid1001.ttf", 35);

      SDL_Surface *vJ1, *vJ2, *vJ3, *vJ4, *erreur;
      SDL_Texture *textureVJ1, *textureVJ2, *textureVJ3, *textureVJ4, *textureErreur;
      SDL_Rect rect;
      SDL_Color blanc = {255, 255, 255, 0};
      SDL_Color rouge = {255, 0, 0, 0};
      SDL_Color bleu = {0, 0, 205, 0};
      SDL_Color jaune = {255, 255, 0, 0};
      SDL_Color vert = {0, 255, 0, 0};

      vJ1 = TTF_RenderText_Solid(font, "Victoire du joueur 1!", rouge);
      textureVJ1 = SDL_CreateTextureFromSurface(pRenderer, vJ1);
      vJ2 = TTF_RenderText_Solid(font, "Victoire du joueur 2!", bleu);
      textureVJ2 = SDL_CreateTextureFromSurface(pRenderer, vJ2);
      vJ3 = TTF_RenderText_Solid(font, "Victoire du joueur 3!", jaune);
      textureVJ3 = SDL_CreateTextureFromSurface(pRenderer, vJ3);
      vJ4 = TTF_RenderText_Solid(font, "Victoire du joueur 4!", vert);
      textureVJ4 = SDL_CreateTextureFromSurface(pRenderer, vJ4);
      erreur = TTF_RenderText_Solid(font, "Erreur! Personne n'a gagné...", blanc);
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

      TTF_Font *font = TTF_OpenFont("../assets/fonts/Mermaid1001.ttf", 35);

      SDL_Surface *surface, *unOrange, *unBlanc, *deuxOrange, *deuxBlanc, *troisOrange, *troisBlanc;
      SDL_Texture *texture, *textureUnOrange, *textureUnBlanc, *textureDeuxOrange, *textureDeuxBlanc, *textureTroisOrange, *textureTroisBlanc;
      SDL_Rect rect;
      SDL_Color blanc = {255, 255, 255, 0};
      SDL_Color orange = {255, 165, 0, 0};

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
                  return(0);
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

          rect.x = 200 - ((surface->w)/2);
          rect.y = 200 - ((surface->h)/2);
          rect.w = surface->w;
          rect.h = surface->h;
          SDL_RenderCopy(pRenderer, texture, NULL, &rect);

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

      SDL_DestroyTexture(textureUnOrange);
      SDL_DestroyTexture(textureUnBlanc);
      SDL_DestroyTexture(textureDeuxOrange);
      SDL_DestroyTexture(textureDeuxBlanc);
      SDL_DestroyTexture(textureTroisOrange);
      SDL_DestroyTexture(textureTroisBlanc);

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
