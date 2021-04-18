#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../lib/bombe.h"
#include "../lib/affichage_map.h"
#include <unistd.h>
#include <time.h>

/*void partie(){
  int jeu[M][N];
  innitMatrice(jeu);
  placerMurIncassable(jeu);
  placerMurCassable(jeu);
  afficherMatrice(jeu);
  menu();
}
void menu(){
	int choix;	// Choix de l'utilisateur
	do
	{	// Affichage du menu
		printf("\nMenu :\n");
		printf(" 1 - Lancer une nouvelle partie\n");
		printf("Votre choix : ");
		scanf("%i",&choix);

		// Traitement du choix de l'utilisateur
		switch(choix)
		{	case 1 : (partie()); break;
			default: printf("Erreur: votre choix doit etre 1\n");
		}
	}
	while(choix!=1);
	printf("Au revoir !\n");
	return EXIT_SUCCESS;
}*/
// Programme principal

int main(int argc, char ** argv){
  srand( time(NULL));

  int jeu[M][N];
  joueur_t * gagnant;

  bombe_t bombe_vide[9];

  //Initialise les 4 joueurs
  joueur_t joueur1 = {-1, 1, 1, 'E', 0, 0, 0, 1, 1, -11, bombe_vide};
  joueur_t joueur2 = {-2, 9, 13, 'W', 0, 0, 0, 1, 1, -12, bombe_vide};
  joueur_t joueur3 = {-3, 9, 1, 'E', 0, 0, 0, 1, 1, -13, bombe_vide};
  joueur_t joueur4 = {-4, 1, 13, 'W',0, 0, 0, 1, 1, -14, bombe_vide};

  SDL_Init(SDL_INIT_VIDEO);


  innitMatrice(jeu);
  placerMurIncassable(jeu);
  placerMurCassable(jeu, 85);

  //Placer les joueurs sur la map
  jeu[joueur1.pos_x][joueur1.pos_y]=joueur1.id;
  jeu[joueur2.pos_x][joueur2.pos_y]=joueur2.id;
  jeu[joueur3.pos_x][joueur3.pos_y]=joueur3.id;
  jeu[joueur4.pos_x][joueur4.pos_y]=joueur4.id;

  gagnant = afficherMap(joueur1, joueur2, joueur3, joueur4, jeu);

  //Faire écran de victoire
  if(gagnant!=NULL){
    printf("Victoire du joueur %d\n", (gagnant->id)*(-1));
  }
  else{
    printf("Erreur! Personne n'a gagné\n");
  }


  SDL_Quit();
}
