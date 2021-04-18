#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../lib/joueur.h"



void effetPouvoir(joueur_t * j, int x, int y, int jeu[M][N]){
  //PV de la vitesse
  if(jeu[x][y]==3){
    //Vitesse max : 9
    if(j->vitesse<9){
      j->vitesse++;
      /*Augmenter de 10% la vitesse*/
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
