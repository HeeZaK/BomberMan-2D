#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../lib/matriceBombe.h"
#include "../lib/monstre.h"
#include <unistd.h>
#include <time.h>
#define N 15
#define M 11

void placerMonstre(int jeu[M][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if(jeu[i][j]==0) // place sur mur cassable
      jeu[i][j]=7; // 7->valeur du monstre1
      printf("%d",jeu[i][j]);
    }
    printf("\n" );
  }
}
