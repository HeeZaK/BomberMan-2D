#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../lib/joueur.h"


/**
* \file joueur.c
* \brief fonctions concernant la gestion des joueurs
* \author Ilango Rémi, Lardais Benjamin, Geslain Simon, Haran Andy 
* \version 1
* \date 19 avril 2021
*/


/**
* \fn void effetPouvoir(joueur_t * j, int x, int y, int jeu[M][N])
* \brief fonction qui applique les effets des pouvoirs sur les joueurs
* \param j représente le joueur,
* \param x représente la ligne dans la matrice
* \param y représente la colonne dans la matrice
* \param jeu représente la matrice
*/
void effetPouvoir(joueur_t * j, int x, int y, int jeu[M][N]){
  //PV de la vitesse
  if(jeu[x][y]==3){
    //Vitesse max : 9
    if(j->vitesse<9){
      j->vitesse++;
    }
  }

  //PV de la puissance
  else if(jeu[x][y]==4){
    //Puissance max : 9
    if(j->puissance<9){
      j->puissance++;
    }
  }

  //Nombre de bombe du joueur
  else if(jeu[x][y]==5){
    //Nombre de bombe max : 9
    if(j->nb_bomb<9){
      j->nb_bomb++;
    }
  }

  //Pouvoir d'une vie en plus
  else if(jeu[x][y]==6){
    //Nombre de vie en plus max : 1
    if(j->vie==0){
      j->vie++;
    }
  }
}

/**
* \fn int checkCollision(joueur_t * j, int direction, int jeu[M][N])
* \brief fonction qui vérifie si le joueur peut se déplacer
* \param j représente le joueur
* \param direction représente la direction dans laquelle regarde le joueur
* \param jeu représente la matrice
* \return retourne 0 si le déplacement n'est pas possible, 1 si il l'est
*/
int checkCollision(joueur_t * j, int direction, int jeu[M][N]){
  //La fonction renvoie 0 si le déplacement n'est pas possible, 1 si il l'est
  //Direction prend 0 : droite, 1 : bas, 2 : gauche, 3 : haut
  switch(direction){
    case 0:
      if(jeu[j->pos_x][j->pos_y+1]==0){
        return 1;
      }
      else if(jeu[j->pos_x][j->pos_y+1]>=3){
        effetPouvoir(j, j->pos_x, j->pos_y+1, jeu);
        return 1;
      }
      return 0;
      break;

    case 1:
      if(jeu[j->pos_x+1][j->pos_y]==0){
        return 1;
      }
      else if(jeu[j->pos_x+1][j->pos_y]>=3){
        effetPouvoir(j, j->pos_x+1, j->pos_y, jeu);
        return 1;
      }
      return 0;
      break;

    case 2:
      if(jeu[j->pos_x][j->pos_y-1]==0){
        return 1;
      }
      else if(jeu[j->pos_x][j->pos_y-1]>=3){
        effetPouvoir(j, j->pos_x, j->pos_y-1, jeu);
        return 1;
      }
      return 0;
      break;

    case 3:
      if(jeu[j->pos_x-1][j->pos_y]==0){
        return 1;
      }
      else if(jeu[j->pos_x-1][j->pos_y]>=3){
        effetPouvoir(j, j->pos_x-1, j->pos_y, jeu);
        return 1;
      }
      return 0;
      break;
  }
}

/**
* \fn void changerRotaJoueur(joueur_t * j)
* \brief fonction qui change la direction dans laquelle regarde le joueur
* \param j représente le joueur
*/
void changerRotaJoueur(joueur_t * j){
  switch(j->direction){
    case 'N':
      j->direction='E';
      break;
    case 'E':
      j->direction='S';
      break;
    case 'S':
      j->direction='W';
      break;
    case 'W':
      j->direction='N';
      break;
  }
}

/**
* \fn void deplacerJ(joueur_t * j, int direction ,int jeu[M][N])
* \brief fonction qui déplace le joueur en fonction de sa direction
* \param j représente le joueur
* \param direction représente la direction dans laquelle regarde le joueur
* \param jeu représente la matrice
*/
void deplacerJ(joueur_t * j, int direction ,int jeu[M][N]){
  //Direction prend 0 : droite, 1 : bas, 2 : gauche, 3 : haut
  switch(direction){
    case 0:
      //Vérifie si le joueur ne va pas dans un mur ou dans un joueur
      if(checkCollision(j,0,jeu)){
        jeu[j->pos_x][j->pos_y]=0;
        jeu[j->pos_x][j->pos_y+1]=j->id;
        j->pos_y++;
      }
      else{
        //introduire son collision
      }
      j->direction='E';
      break;

    case 1:
      //Vérifie si le joueur ne va pas dans un mur ou dans un joueur
      if(checkCollision(j,1,jeu)){
        jeu[j->pos_x][j->pos_y]=0;
        jeu[j->pos_x+1][j->pos_y]=j->id;
        j->pos_x++;
      }
      else{
        //introduire son collision
      }
      j->direction='S';
      break;

    case 2:
      //Vérifie si le joueur ne va pas dans un mur ou dans un joueur
      if(checkCollision(j,2,jeu)){
        jeu[j->pos_x][j->pos_y]=0;
        jeu[j->pos_x][j->pos_y-1]=j->id;
        j->pos_y--;
      }
      else{
        //introduire son collision
      }
      j->direction='W';
      break;

    case 3:
      //Vérifie si le joueur ne va pas dans un mur ou dans un joueur
      if(checkCollision(j,3,jeu)){
        jeu[j->pos_x][j->pos_y]=0;
        jeu[j->pos_x-1][j->pos_y]=j->id;
        j->pos_x--;
      }
      else{
        //introduire son collision
      }
      j->direction='N';
      break;
  }
  j->timer = SDL_GetTicks();

}

/**
* \fn joueur_t * verifGagnant(joueur_t * j1, joueur_t * j2, joueur_t * j3, joueur_t * j4, int jeu[M][N])
* \brief fonction qui vérifie qui a gagné parmi les joueurs
* \param j1 représente le joueur 1
* \param j2 représente le joueur 2
* \param j3 représente le joueur 3
* \param j4 représente le joueur 4
* \param jeu représente la matrice.
* \return retourne le gagnant
*/
joueur_t * verifGagnant(joueur_t * j1, joueur_t * j2, joueur_t * j3, joueur_t * j4, int jeu[M][N]){

  if(j2->pos_x==-1 && j3->pos_x==-1 && j4->pos_x==-1 )
    return (j1);
  else if(j1->pos_x==-1 && j3->pos_x==-1 && j4->pos_x==-1 )
    return (j2);
  else if(j1->pos_x==-1 && j2->pos_x==-1 && j4->pos_x==-1 )
    return (j3);
  else if(j1->pos_x==-1 && j2->pos_x==-1 && j3->pos_x==-1 )
    return (j4);
  return (NULL);
}
