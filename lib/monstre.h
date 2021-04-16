
#include "../lib/matriceBombe.h"

typedef struct monstre_s{
  //id des monstres : petit monstre : -5, monstre moyen: -6, grand monstre :  -7
  int id;
  // Position x et y du monstre
  int pos_x;
  int pos_y;
  // Direction vers laquelle le monstre regarde E,W,S,N pour east, west, south, north
  char direction;
  // nombre de vie des monstres
  int vie;
  // vitesse des monstres
  int vitesse;
}monstre_t;

// fonction pour deplacer les monstres
void deplacerMonstre(monstre_t *m, char direction ,int jeu[M][N]);


int checkCollisionM(monstre_t * m, int direction, int jeu[M][N]);
