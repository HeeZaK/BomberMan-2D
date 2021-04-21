#include <stdlib.h>
#include <stdio.h>
#include "../lib/menu.h"
#include <unistd.h>
#include <time.h>

int main(){

  int valMenu;
  int x;

  printf("Choix du menu (1: menu de base, 2: menu multijoueur, 3: menu solo) : \n");
  scanf("%d",&valMenu);
  printf("Affichage menu choisit : \n");

  if(valMenu == 1){
    x = menu();
  }
  else if(valMenu == 2){
    x = menuMultijoueur();
  }
  else if(valMenu == 3){
    x = menuSolo();
  }

  return 0;
}
