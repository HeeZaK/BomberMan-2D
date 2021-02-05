#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define N 15
#define M 11

// vider la map totalement
void innitMatrice(int jeu[M][N]){
  for(int i=0; i<M;i++){
    for(int j=0; j<N;j++){
      jeu[i][j]=0;
    }
  }
}
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
// placer les murs cassable de la map
void placerMurCassable(int jeu[M][N]){
  for(int i=1; i<M-1;i++){
    for(int j=1; j<N-1;j++){
      if(jeu[i][j]==0){
        if(rand()%100 < 85){
          jeu[i][j]=2;
        }
      }
    }
  }
  //place par défaut pour spawn dans les coins de la map
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
// afficher la map dans le cmd
void afficherMatrice(int jeu[M][N]){
  for(int i=0; i<M;i++){
    for(int j=0; j<N;j++){
      if(jeu[i][j]==1){
        printf("● "); // murs pleins
      }else if(jeu[i][j]==2){
        printf("# "); // murs creux
      }else{
        printf("○ "); // pas de murs
      }
    }printf("\n");
  }
}


