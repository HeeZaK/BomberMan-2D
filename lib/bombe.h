/*#include "../lib/joueur.h"
#include "../lib/matriceBombe.h"*/

#include "../lib/joueur.h"

int valides(int x, int y);

void effetBombe(joueur_t * j1, joueur_t * j2, joueur_t * j3, joueur_t * j4, int x, int y, int jeu[M][N]);

int checkPoseBombe(joueur_t * j, int jeu[M][N]);

void Detruire(joueur_t * j1, joueur_t * j2, joueur_t * j3, joueur_t * j4, int k, int jeu[M][N]);
