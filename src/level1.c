#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../lib/bombe.h"
#include "../lib/monstre.h"
#include <unistd.h>
#include <time.h>
#include "../lib/level.h"


/**
* \file level1.c
* \brief fonction du premier niveau
* \author Ilango Rémi, Lardais Benjamin, Geslain Simon, Haran Andy
* \version 1
* \date 19 avril 2021
*/

/**
* \fn int level1()
* \brief fonction qui permet de savoir si une case est dans la matrice
* \return 1 quand le joueur gagne et 0 quand il perd
*/
int level1(){
  srand( time(NULL));

  int timer=SDL_GetTicks();

  int jeu[M][N];

  //Initialisation des bombes
  bombe_t bombe_vide[9];

  //Initialise le joueur
  joueur_t joueur1 = {-1, 1, 1, 'E', 0, 0, 0, 1, 1, -11, bombe_vide};

  //Initialise les trois monstres
  monstre_t m1={-5,5,8,'N',1};
  monstre_t m2={-5,3,5,'S',1};
  monstre_t m3={-5,6,4,'S',1};

  SDL_Init(SDL_INIT_VIDEO);

  //Initialisation de la matrice
  innitMatrice(jeu);
  placerMurIncassable(jeu);
  placerMurCassable(jeu, 70);

  //Placer les personnages sur la map
  jeu[joueur1.pos_x][joueur1.pos_y]=joueur1.id;

  jeu[m1.pos_x][m1.pos_y]=m1.id;
  jeu[m1.pos_x-1][m1.pos_y]=0;
  jeu[m1.pos_x+1][m1.pos_y]=0;

  jeu[m2.pos_x][m2.pos_y]=m2.id;
  jeu[m2.pos_x-1][m2.pos_y]=0;
  jeu[m2.pos_x+1][m2.pos_y]=0;

  jeu[m3.pos_x][m3.pos_y]=m3.id;
  jeu[m3.pos_x-1][m3.pos_y]=0;
  jeu[m3.pos_x+1][m3.pos_y]=0;

  //Lancement de la partie avec la fonction afficherMapMonstre qui va retourner si le joueur a gagné où s'il a perdu
  int  gagnant = afficherMapMonstre(joueur1, m1, m2, m3, jeu);

  return gagnant;

  SDL_Quit();
}
