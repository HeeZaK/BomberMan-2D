
typedef struct monstre_s{
  int id;
  int pos_x;
  int pos_y;
  char direction;
  int vie;
  int vitesse;
}monstre_t;

void placerMonstre(int jeu[M][N]);
