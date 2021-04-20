#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


#include "../lib/bombe.h"

#include <unistd.h>
#include <time.h>


/**
* \file bombe.c
* \brief fonctions concernant la gestion des bombes
* \author Ilango Rémi, Lardais Benjamin, Geslain Simon, Haran Andy
* \version 1
* \date 19 avril 2021
*/


/**
* \fn int valides(int x, int y)
* \brief fonction qui permet de savoir si une case est dans la matrice
* \param x représente la colonne dans la matrice
* \param y représente la colonne dans la matrice
* \return retourne si la case est valide ou non
*/
int valides(int x, int y){
  return((x>0 && x<M-1) && (y>0 && y<N-1));
}

/**
* \fn void effetBombe(joueur_t * j1, joueur_t * j2, joueur_t * j3, joueur_t * j4, int x, int y, int jeu[M][N])
* \brief fonction qui applique l'effet des bombes sur les joueurs
* \param j1 représente le joueur 1
* \param j2 représente le joueur 2
* \param j3 représente le joueur 3
* \param j4 représente le joueur 4
* \param x représente la colonne dans la matrice
* \param y représente la colonne dans la matrice
* \param jeu représente la matrice
*/
void effetBombe(joueur_t * j1, joueur_t * j2, joueur_t * j3, joueur_t * j4, int x, int y, int jeu[M][N]){

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

  if(x==j2->pos_x && y==j2->pos_y){
    if(j2->vie==1){
      j2->vie=0;
    }
    else{
      j2->pos_x = -1;
      j2->pos_y = -1;
      jeu[x][y]=0;
    }
  }

  if(x==j3->pos_x && y==j3->pos_y){
    if(j3->vie==1){
      j3->vie=0;
    }
    else{
      j3->pos_x = -1;
      j3->pos_y = -1;
      jeu[x][y]=0;
    }
  }

  if(x==j4->pos_x && y==j4->pos_y){
    if(j4->vie==1){
      j4->vie=0;
    }
    else{
      j4->pos_x = -1;
      j4->pos_y = -1;
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
}

/**
* \fn int checkPoseBombe(joueur_t * j, int jeu[M][N])
* \brief fonction qui vérifie si une bombe peut être posée
* \param j représente le joueur
* \param jeu représente la matrice
* \return retourne vrai si le joueur peut poser la bombe et 0 s'il ne peut pas
*/
int checkPoseBombe(joueur_t * j, int jeu[M][N]){
  int x=0, y=0;

  if(j->direction=='N'){
    x = (j->pos_x)-1;
    y = (j->pos_y);
  }
  else if(j->direction=='W'){
    x = (j->pos_x);
    y = (j->pos_y)-1;
  }
  else if(j->direction=='S'){
    x = (j->pos_x)+1;
    y = (j->pos_y);
  }
  else if(j->direction=='E'){
    x = (j->pos_x);
    y = (j->pos_y)+1;
  }

  for(int i=0; i<(j->nb_bomb);i++){
    if((jeu[x][y]==0 || jeu[x][y]>=3) && (j->bombe[i].timer == 0)){
      j->bombe[i].pos_x = x;
      j->bombe[i].pos_y = y;
      j->bombe[i].timer = SDL_GetTicks();
      jeu[x][y] = j->id_bombe;
      return (i+1);
    }
  }


  return 0;
}

/**
* \fn void Detruire(joueur_t * j1, joueur_t * j2, joueur_t * j3, joueur_t * j4, int k, int jeu[M][N])
* \brief fonction qui fait exploser la bombe
* \param j1 représente le joueur 1
* \param j2 représente le joueur 2
* \param j3 représente le joueur 3
* \param j4 représente le joueur 4
* \param k représente l'indice de la bombe qu'utilise le joueur
* \param jeu représente la matrice
*/
//une bombe détruit dans les 4 directions les objets cassable (mur cassable, pouvoir au sol, joueur)
void Detruire(joueur_t * j1, joueur_t * j2, joueur_t * j3, joueur_t * j4, int k, int jeu[M][N]){
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
    effetBombe(j1,j2,j3,j4,x,y-i,jeu);

    for(i=0; i<puissB && (valides(x,y+i) && (jeu[x][y+i]==0 && jeu[x][y+i]!=1)); i++);
    //Effet de la bombe vers la droite
    effetBombe(j1,j2,j3,j4,x,y+i,jeu);

    for(i=0; i<puissB && (valides(x-i,y) && (jeu[x-i][y]==0 && jeu[x-i][y]!=1)); i++);
    //Effet de la bombe vers le haut
    effetBombe(j1,j2,j3,j4,x-i,y,jeu);

    for(i=0; i<puissB && (valides(x+i,y) && (jeu[x+i][y]==0 && jeu[x+i][y]!=1)); i++);
    //Effet de la bombe vers le bas
    effetBombe(j1,j2,j3,j4,x+i,y,jeu);

}
