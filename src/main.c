#include <stdlib.h>
#include <stdio.h>
#include <matriceBombe.h>

void partie(){
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
}
// Programme principal

int main(void){
    srand( time(NULL));
	menu();
}