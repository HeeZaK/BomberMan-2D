#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../lib/menu.h"
#include <unistd.h>
#include <time.h>
#include "../lib/level.h"


/**
* \file main.c
* \brief fonction regroupant tous les modes de jeux avec les menus
* \author Ilango Rémi, Lardais Benjamin, Geslain Simon, Haran Andy
* \version 1
* \date 19 avril 2021
*/


int main(int argc, char ** argv){
  srand( time(NULL));



  int valMenu = menu();

  if(valMenu==1){
    int nb_joueur = menuMultijoueur();
    if(nb_joueur!=0){
      int gagnant = lancerPartieMulti(nb_joueur);
      afficheGagnant(gagnant);
    }
  }
  else if(valMenu==2){
    //Mode solo
    int num_niv = menuSolo();
    if(num_niv==1){
      level1();
    }
    else if(num_niv==2){
      level2();
    }
    else if(num_niv==3){
      level3();
    }
  }
  else{
    //Exit
  }



  SDL_Quit();
}
