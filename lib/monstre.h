


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

}monstre_t;

// fonction pour deplacer les monstres




void deplacerMonstre(joueur_t *j1, monstre_t *m, char direction ,int jeu[M][N]);

void effetBombeMonstre(joueur_t * j1, monstre_t * m1, monstre_t * m2, monstre_t * m3, int x, int y, int jeu[M][N]);

int checkCollisionM(joueur_t * j1, monstre_t * m, int direction, int jeu[M][N]);

int afficherMapMonstre(joueur_t j1, monstre_t m1, monstre_t m2, monstre_t m3, int jeu[M][N]);

//une bombe détruit dans les 4 directions les objets cassable (mur cassable, pouvoir au sol, joueur)
void DetruireMonstre(joueur_t * j1, monstre_t * m1, monstre_t * m2, monstre_t * m3, int k, int jeu[M][N]);
