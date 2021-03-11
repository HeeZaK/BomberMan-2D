#define N 15
#define M 11

typedef struct joueur_s{
  int id;
  int pos_x;
  int pos_y;
  int vie;
  int vitesse;
  int nb_bomb;
  int puissance;
}joueur_t;

void deplacerJoueur(joueur_t, int jeu[M][N]);

void Bombe(joueur_t j1, joueur_t j2, joueur_t j3, joueur_t j4, int x, int y, int jeu[M][N]);

int valides(int x, int y);

void effetBombe(joueur_t j1, joueur_t j2, joueur_t j3, joueur_t j4, int x, int y, int jeu[M][N]);

void Detruire(joueur_t j1, joueur_t j2, joueur_t j3, joueur_t j4, int x, int y, int jeu[M][N]);

void effetPouvoir(joueur_t j, int x, int y, int jeu[M][N]);
