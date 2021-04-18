#include <stdio.h>
#include <stdlib.h>
#include "../lib/matriceBombe.h"


typedef struct bombe_s{
  // Position X et Y de la bombe
  int pos_x;
  int pos_y;
  // Timer à laquelle la bombe a été placée. Egale a 0 si la bombe n´est pas placee
  int timer;
}bombe_t;

typedef struct joueur_s{
  // Id du joueur, de -1 a -4 pour joueur 1 a 4 (Le nombre est négatif pour simplifier le placement dans la matrice
  int id;
  // Position X et Y du joueur
  int pos_x;
  int pos_y;
  // Direction vers la quelle le joueur regarde, E,W,S,N pour east west south et north
  char direction;
  // Nombre de vie du joueur, en multijoueur peut etre augmenté a 2 avec le shield
  int vie;
  // Variable determinant la vitesse a la quelle le joueur bouge
  int vitesse;
  // Variable déterminant si un mouvement est en cours
  int timer;
  // Variable determinant le nombre de bombe maximal que le joueur peux placer, de 1 a 9
  int nb_bomb;
  // Variable determinant la puissance de chaque bombe
  int puissance;
  // Variable determinant l´id de la bombe du joueur par rapport a la matrice
  int id_bombe;

  // Variable contenant les informations des jusqu´a 9 bombes du joueur
  bombe_t bombe[9];

}joueur_t;

void effetPouvoir(joueur_t * j, int x, int y, int jeu[M][N]);

int checkCollision(joueur_t * j, int direction, int jeu[M][N]);

void changerRotaJoueur(joueur_t * j);

void deplacerJ(joueur_t * j, int direction ,int jeu[M][N]);

joueur_t * verifGagnant(joueur_t * j1, joueur_t * j2, joueur_t * j3, joueur_t * j4, int jeu[M][N]);
