#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../lib/bombe.h"
#include "../lib/monstre.h"
#include "../lib/matriceBombe.h"

/**
* \file monstre.c
* \brief programmes concernant la gestion des monstres
* \author Rémi Ilango Benjamin Lardais Simon Geslain Andy Haran
* \version 1
* \date 19 octobre 2021
*/

/**
* \fn void effetBombeMonstre(joueur_t * j1, monstre_t * m1, monstre_t * m2, monstre_t * m3, int x, int y, int jeu[M][N])
* \brief fonction qui applique l'effet de la bombe sur le joueur, les murs, les monstres. Un mur cassé peut laisser un bonus.
* \param j1 représente le joueur, m1,m2,m3 représentent les monstres, x,y représentent les coordonnées de l'impact de la bombe, jeu représente la matrice
*/
void effetBombeMonstre(joueur_t * j1, monstre_t * m1, monstre_t * m2, monstre_t * m3, int x, int y, int jeu[M][N]){

  //effet de la bombe sur un joueur sur la trajectoire de la bombe
  if(x==j1->pos_x && y==j1->pos_y){
    if(j1->vie==1){
      j1->vie=0;
    }
    else{
      j1->pos_x = -1;
      j1->pos_y = -1;
      jeu[x][y]=0;
    }
  }

  //effet de la bombe sur un mur cassable
  else if(jeu[x][y]==2){
    jeu[x][y] = rand()%4 + 3;
    if(rand()%100 < 25){ // il y a 25% de chance qu'un mur explosé ne donne pas de pouvoir
      jeu[x][y]=0;
    }
  }

  //supprime le pouvoir au sol
  else if(jeu[x][y]>=3){
    jeu[x][y]=0;
  }

    //effet de la bombe sur un monstre sur la trajectoire de la bombe
  if(x==m1->pos_x && y==m1->pos_y){
    if(m1->vie>0){
      m1->vie--;
    }
    else{
      m1->pos_x = -1;
      m1->pos_y = -1;
      jeu[x][y]=0;
    }
  }
  //effet de la bombe sur un monstre sur la trajectoire de la bombe
  if(x==m2->pos_x && y==m2->pos_y){
    if(m2->vie>0){
      m2->vie--;
    }
    else{
      m2->pos_x = -1;
      m2->pos_y = -1;
      jeu[x][y]=0;
    }
  }
  //effet de la bombe sur un monstre sur la trajectoire de la bombe
  if(x==m3->pos_x && y==m3->pos_y){
    if(m3->vie>0){
      m3->vie--;
    }
    else{
      m3->pos_x = -1;
      m3->pos_y = -1;
      jeu[x][y]=0;
    }
  }
}

/**
* \fn void DetruireMonstre(joueur_t * j1, monstre_t * m1, monstre_t * m2, monstre_t * m3, int k, int jeu[M][N])
* \brief fonction qui détruit les monstres à l'indice de la bombe qu'utilise le joueur
* \param j1 représente le joueur, m1,m2,m3 représentent les monstres, k, jeu représente la matrice
*/

//une bombe détruit dans les 4 directions les objets cassable (mur cassable, pouvoir au sol, joueur)
void DetruireMonstre(joueur_t * j1, monstre_t * m1, monstre_t * m2, monstre_t * m3, int k, int jeu[M][N]){
  int i;
  int puissB=j1->puissance;
  int x = j1->bombe[k].pos_x;
  int y = j1->bombe[k].pos_y;

    jeu[x][y] = 0;
    /*Cette instruction permet d'enlever
    tout les cas impossible à modifier et
    cela permet de rester dans la matrice*/
    for(i=0; i<puissB && (valides(x,y-i) && (jeu[x][y-i]==0 && jeu[x][y-i]!=1)); i++);
    //Effet de la bombe vers la gauche
    effetBombeMonstre(j1,m1,m2,m3,x,y-i,jeu);

    for(i=0; i<puissB && (valides(x,y+i) && (jeu[x][y+i]==0 && jeu[x][y+i]!=1)); i++);
    //Effet de la bombe vers la droite
    effetBombeMonstre(j1,m1,m2,m3,x,y+i,jeu);


    for(i=0; i<puissB && (valides(x-i,y) && (jeu[x-i][y]==0 && jeu[x-i][y]!=1)); i++);
    //Effet de la bombe vers le haut
    effetBombeMonstre(j1,m1,m2,m3,x-i,y,jeu);


    for(i=0; i<puissB && (valides(x+i,y) && (jeu[x+i][y]==0 && jeu[x+i][y]!=1)); i++);
    //Effet de la bombe vers le bas
    effetBombeMonstre(j1,m1,m2,m3,x+i,y,jeu);


}

/**
* \fn int checkCollisionM(joueur_t * j1, monstre_t * m, int direction, int jeu[M][N])
* \brief
* \param j1 représente le joueur, m représentent les monstres, direction, jeu représente la matrice
* \return
*/
int checkCollisionM(joueur_t * j1, monstre_t * m, int direction, int jeu[M][N]){
  //La fonction renvoie 0 si le déplacement n'est pas possible, 1 si il l'est
  //Direction prend 0 : droite, 1 : bas, 2 : gauche, 3 : haut
  switch(direction){
    case 0:
      if(jeu[m->pos_x][m->pos_y+1]==0){
        return 1;
      }
      else if(jeu[m->pos_x][m->pos_y+1]>=3){

        return 1;
      }

      else if(jeu[m->pos_x][m->pos_y+1]==j1->id){
        if(j1->vie==1){
          j1->vie=0;
        }
        else{
          j1->pos_x = -1;
          j1->pos_y = -1;
        }
      }
      return 0;
      break;

    case 1:
      if(jeu[m->pos_x+1][m->pos_y]==0){
        return 1;
      }

      else if(jeu[m->pos_x+1][m->pos_y]>=3){

        return 1;
      }

      else if(jeu[m->pos_x+1][m->pos_y]==j1->id){
        if(j1->vie==1){
          j1->vie=0;
        }
        else{
          j1->pos_x = -1;
          j1->pos_y = -1;
        }
      }
      return 0;
      break;

    case 2:
      if(jeu[m->pos_x][m->pos_y-1]==0){
        return 1;
      }
      else if(jeu[m->pos_x][m->pos_y-1]>=3){

        return 1;
      }

      else if(jeu[m->pos_x][m->pos_y-1]==j1->id){
        if(j1->vie==1){
          j1->vie=0;
        }
        else{
          j1->pos_x = -1;
          j1->pos_y = -1;

        }
      }
      return 0;
      break;

    case 3:
      if(jeu[m->pos_x-1][m->pos_y]==0){
        return 1;
      }
      else if(jeu[m->pos_x-1][m->pos_y]>=3){

        return 1;
      }

      else if(jeu[m->pos_x-1][m->pos_y]==j1->id){
        if(j1->vie==1){
          j1->vie=0;
        }
        else{
          j1->pos_x = -1;
          j1->pos_y = -1;

        }
      }

      return 0;
      break;
  }

}

void deplacerMonstre(joueur_t *j1,monstre_t *m, char direction, int jeu[M][N]){
  //Direction prend 0 : droite, 1 : bas, 2 : gauche, 3 : haut
  switch(direction){
    //bas
    case 'S':
      //Vérifie si le monstre ne va pas dans un mur ou dans un joueur
      if(checkCollisionM(j1,m,1,jeu)){
        jeu[m->pos_x][m->pos_y]=0;
        jeu[m->pos_x+1][m->pos_y]=m->id;
        m->pos_x++;
        m->direction='S';
      }
      else{
        m->direction='N';
      }

      break;

    //haut
    case 'N':
      //Vérifie si le monstre ne va pas dans un mur ou dans un joueur
      if(checkCollisionM(j1,m,3,jeu)){
        jeu[m->pos_x][m->pos_y]=0;
        jeu[m->pos_x-1][m->pos_y]=m->id;
        m->pos_x--;
        m->direction='N';
      }
      else{
        m->direction='S';
      }
      break;

      //droite
      case 'E':
        //Vérifie si le monstre ne va pas dans un mur ou dans un joueur
        if(checkCollisionM(j1,m,0,jeu)){
          jeu[m->pos_x][m->pos_y]=0;
          jeu[m->pos_x][m->pos_y+1]=m->id;
          m->pos_y++;
          m->direction='E';
        }
        else{
          m->direction='W';
        }
        break;

        //gauche
        case 'W':
          //Vérifie si le monstre ne va pas dans un mur ou dans un joueur
          if(checkCollisionM(j1,m,2,jeu)){
            jeu[m->pos_x][m->pos_y]=0;
            jeu[m->pos_x][m->pos_y-1]=m->id;
            m->pos_y--;
            m->direction='W';
          }
          else{
            m->direction='E';
          }
          break;
  }
}

// la fonction retourne 0 lorsque le joueur perd et 1 quand il gagne
int afficherMapMonstre(joueur_t j1, monstre_t m1, monstre_t m2, monstre_t m3, int jeu[M][N]) {

  SDL_Window *win = NULL;
  SDL_Renderer *renderer = NULL;

  SDL_Texture *bitmapFond, *bitmapMurI, *bitmapMurC;
  SDL_Texture *bitmapJ1N, *bitmapJ1E, *bitmapJ1S, *bitmapJ1W;
  SDL_Texture *bitmapM1, *bitmapM2, *bitmapM3;
  SDL_Texture *bitmapBombeJ1;
  SDL_Texture *bitmapPlusBombe, *bitmapVitesse, *bitmapPuissance, *bitmapShield;



  int posX = 100, posY = 100, width = 840, height = 616, w = 56, h = 56;
  SDL_Rect rectMurI, rectMurC;
  SDL_Rect rectM1, rectM2, rectM3;
  SDL_Rect bombeJ1;
  SDL_Rect rectJ1N, rectJ1E, rectJ1S, rectJ1W;
  SDL_Rect plusBombe, vitesse, puissance, shield;

  int temps_monstre=0;
  int timer=SDL_GetTicks();


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

  bitmapM1 = IMG_LoadTexture(renderer, "../assets/monstres/petit/monstreAvant.png");   //monstre petit
  bitmapM2 = IMG_LoadTexture(renderer, "../assets/monstres/moyen/2hp/monstreAvant.png");
  bitmapM3 = IMG_LoadTexture(renderer, "../assets/monstres/grand/3hp/monstreAvant.png");

  bitmapBombeJ1 = IMG_LoadTexture(renderer, "../assets/bombe/bombe_rouge.png");   //bombe J1

  bitmapPlusBombe = IMG_LoadTexture(renderer, "../assets/powerups/plusbombe.png");   //PV nombre de bombe augmenté
  bitmapVitesse = IMG_LoadTexture(renderer, "../assets/powerups/plusvitesse.png");   //PV vitesse augmenté
  bitmapPuissance = IMG_LoadTexture(renderer, "../assets/powerups/puissance.png");   //PV puissance augmenté
  bitmapShield = IMG_LoadTexture(renderer, "../assets/powerups/shield.png");   //PV bouclier
  //



    SDL_Event event;
    int continuer = 1;
    int gagnant=0;
    while( continuer ){
      SDL_PollEvent(&event);
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
              }
              break;
            case SDLK_e:
              //changer rotation
              changerRotaJoueur(&j1);
              break;
          }
          break;
      }

      for(int i=0; i<j1.nb_bomb; i++){
        if((SDL_GetTicks() > j1.bombe[i].timer + 2000) && j1.bombe[i].timer!=0){
          DetruireMonstre(&j1,&m1,&m2,&m3,i,jeu);
          j1.bombe[i].timer=0;
          j1.bombe[i].pos_x=0;
          j1.bombe[i].pos_y=0;
        }
      }

      //deplacerMonstre(&m, m.direction, jeu);

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

            case -5:
            rectM1.x = w * j;
            rectM1.y = h * i;
            rectM1.w = w;
            rectM1.h = h;
            SDL_RenderCopy(renderer, bitmapM1, NULL, &rectM1);
            break;
            case -6:
            rectM2.x = w * j;
            rectM2.y = h * i;
            rectM2.w = w;
            rectM2.h = h;
            SDL_RenderCopy(renderer, bitmapM2, NULL, &rectM2);
            break;
            case -7:
            rectM3.x = w * j;
            rectM3.y = h * i;
            rectM3.w = w;
            rectM3.h = h;
            SDL_RenderCopy(renderer, bitmapM3, NULL, &rectM3);
            break;
            case -11:
            bombeJ1.x = w * j;
            bombeJ1.y = h * i;
            bombeJ1.w = w;
            bombeJ1.h = h;
            SDL_RenderCopy(renderer, bitmapBombeJ1, NULL, &bombeJ1);
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

// déplacement des monstres
      if(temps_monstre == 0){
          temps_monstre = SDL_GetTicks();

       }
      if(SDL_GetTicks() > temps_monstre + 1000){
          deplacerMonstre(&j1,&m1,m1.direction,jeu);
          deplacerMonstre(&j1,&m2,m2.direction,jeu);
          deplacerMonstre(&j1,&m3,m3.direction,jeu);
          temps_monstre=0;
      }

      if(timer > SDL_GetTicks()+1000*120){
        gagnant=0;
        continuer=0;
      }

      if(j1.pos_x==-1){
        gagnant=0;
        continuer=0;
      }

      if(m1.pos_x==-1 && m2.pos_x==-1 && m3.pos_x==-1 ){
        gagnant=1;
        continuer=0;
      }



      SDL_RenderPresent(renderer); //affichage de tout

      SDL_Delay(1000/60);
      SDL_RenderClear(renderer);

  }

  return gagnant;

  SDL_DestroyTexture(bitmapFond); //Fond
  SDL_DestroyTexture(bitmapMurI); //Mur Incassable
  SDL_DestroyTexture(bitmapMurC); //Mur MurCassable
  // joueur1
  SDL_DestroyTexture(bitmapJ1N);
  SDL_DestroyTexture(bitmapJ1E);
  SDL_DestroyTexture(bitmapJ1S);
  SDL_DestroyTexture(bitmapJ1W);


  SDL_DestroyTexture(bitmapM1); // monstre petit
  SDL_DestroyTexture(bitmapM3); // montre moyen
  SDL_DestroyTexture(bitmapM2); // monstre grand
  SDL_DestroyTexture(bitmapBombeJ1);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);


}
