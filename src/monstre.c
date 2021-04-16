#include <stdio.h>
#include <stdlib.h>

#include "../lib/monstre.h"



  int checkCollisionM(monstre_t * m, int direction, int jeu[M][N]){
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
        return 0;
        break;

      case 1:
        if(jeu[m->pos_x+1][m->pos_y]==0){
          return 1;
        }
        else if(jeu[m->pos_x+1][m->pos_y]>=3){

          return 1;
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
        return 0;
        break;

      case 3:
        if(jeu[m->pos_x-1][m->pos_y]==0){
          return 1;
        }
        else if(jeu[m->pos_x-1][m->pos_y]>=3){

          return 1;
        }
        return 0;
        break;
    }
  }

  void deplacerMonstre(monstre_t *m, char direction, int jeu[M][N]){
    //Direction prend 0 : droite, 1 : bas, 2 : gauche, 3 : haut
    switch(direction){
      //bas
      case 'S':
        //Vérifie si le joueur ne va pas dans un mur ou dans un joueur
        if(checkCollisionM(m,1,jeu)){
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
        //Vérifie si le joueur ne va pas dans un mur ou dans un joueur
        if(checkCollisionM(m,3,jeu)){
          jeu[m->pos_x][m->pos_y]=0;
          jeu[m->pos_x-1][m->pos_y]=m->id;
          m->pos_x--;
          m->direction='N';
        }
        else{
          m->direction='S';
        }
        break;
    }
  }
