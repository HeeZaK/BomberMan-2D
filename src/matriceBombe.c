#include <stdio.h>
#include <stdlib.h>
#include "../lib/matriceBombe.h"
#include <unistd.h>
#include <time.h>

/**
* \file matriceBombe.c
* \brief fonctions concernant la gestion de la matrice
* \author Ilango Rémi, Lardais Benjamin, Geslain Simon, Haran Andy
* \version 1
* \date 19 octobre 2021
*/

/**
* \fn void innitMatrice(int jeu[M][N])
* \brief fonction qui vide la matrice en mettant chaque case à 0
* \param jeu représente la matrice
*/
// vider la map totalement
void innitMatrice(int jeu[M][N]){
  for(int i=0; i<M;i++){
    for(int j=0; j<N;j++){
      jeu[i][j]=0;
    }
  }
}

/**
* \fn void placerMurIncassable(int jeu[M][N])
* \brief fonction qui place les murs incassables
* \param jeu représente la matrice
*/
// placer les murs incassable de la map
void placerMurIncassable(int jeu[M][N]){
  for(int i=0; i<M;i++){
    for(int j=0; j<N;j++){
      if(j==0 || i==0 || j==N-1 || i==M-1){  //on place les murs indestructible sur les bords
        jeu[i][j]=1;
      }
      else if(i%2==0 && j%2==0){  // on place les murs indestructible toutes les deux cases
        jeu[i][j]=1;
      }
    }
  }
}

/**
* \fn void placerMurCassable(int jeu[M][N], int proba)
* \brief fonction qui place les murs cassables. Mur cassable=2
* \param jeu représente la matrice
* \param proba représente la probabilité qu'un mur placé soit cassable
*/
// placer les murs cassable de la map
void placerMurCassable(int jeu[M][N], int proba){
  for(int i=1; i<M-1;i++){
    for(int j=1; j<N-1;j++){
      if(jeu[i][j]==0){
        if(rand()%100 < proba){
          jeu[i][j]=2;
        }
      }
    }
  }
  //Libération des places par défaut pour spawn dans les coins de la map
  jeu[1][1]=0;
  jeu[1][2]=0;
  jeu[2][1]=0;

  jeu[M-2][N-2]=0;
  jeu[M-3][N-2]=0;
  jeu[M-2][N-3]=0;

  jeu[1][N-2]=0;
  jeu[1][N-3]=0;
  jeu[2][N-2]=0;

  jeu[M-2][1]=0;
  jeu[M-2][2]=0;
  jeu[M-3][1]=0;

}

/**
* \fn void afficherMatrice(int jeu[M][N])
* \brief fonction qui affiche la matrice dans le terminal
* \param jeu représente la matrice
*/
// afficher la map dans le cmd
void afficherMatrice(int jeu[M][N]){
  for(int i=0; i<M;i++){
    for(int j=0; j<N;j++){
      switch (jeu[i][j]) {
        case 0:
          printf("  "); // pas de murs
          break;
        case 1:
          printf("* "); // murs pleins
          break;
        case 2:
          printf("# "); // murs creux
          break;
        case -1:
          printf("1 "); // joueur1
          break;
        case -2:
          printf("2 "); // joueur2
          break;
        case -3:
          printf("3 "); // joueur3
          break;
        case -4:
          printf("4 "); // joueur4
          break;
        default:
          printf("%i", jeu[i][j]);

        break;
      }
    }printf("\n");
  }
}
