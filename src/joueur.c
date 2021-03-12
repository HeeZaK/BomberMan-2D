#include <stdio.h>
#include <stdlib.h>
#include <matriceBombe.h>
#include <joueur.h>
#include <unistd.h>

void deplacerJoueur(joueur_t j, joueur_t j2, joueur_t j3, joueur_t j4, int jeu[M][N]){
  //Si une touche a ete pressee
  /*if( event.type == SDL_KEYDOWN ){
    switch (event.type){
      case SDL_KEYDOWN:
      // La touche pressée :
        switch (event.key.keysym.scancode) {
          //Les 4 touches différentes pour avoir 4 joueurs en local sur le même clavier
          case SDL_SCANCODE_Z:
          case SDL_SCANCODE_T:
          case SDL_SCANCODE_I:
          case SDL_SCANCODE_UP:
            //Vérifie si le joueur ne va pas dans un mur ou dans un joueur
            if((j.pos_x+1)==0 || (j.pos_x+1)>=3)){
              //Vérifie si le joueur marche sur un pouvoir
              if((j.pos_x+1)>=3)){
                effetPouvoir(j, j.pos_x+1, j.pos_y, jeu);
              }
              j.pos_x = j.pos_x++;
            }
            j.direction='N';
            break;

          //Les 4 touches différentes pour avoir 4 joueurs en local sur le même clavier
          case SDL_SCANCODE_Q:
          case SDL_SCANCODE_F:
          case SDL_SCANCODE_J:
          case SDL_SCANCODE_LEFT:
            //Vérifie si le joueur ne va pas dans un mur ou dans un joueur
            if((j.pos_y-1)==0 || (j.pos_y-1)>=3)){
              //Vérifie si le joueur marche sur un pouvoir
              if((j.pos_y-1)>=3)){
                effetPouvoir(j, j.pos_x, j.pos_y-1, jeu);
              }
              j.pos_y = j.pos_y--;
            }
            j.direction='W';
            break;

          //Les 4 touches différentes pour avoir 4 joueurs en local sur le même clavier
          case SDL_SCANCODE_S:
          case SDL_SCANCODE_G:
          case SDL_SCANCODE_K:
          case SDL_SCANCODE_DOWN:
            //Vérifie si le joueur ne va pas dans un mur ou dans un joueur
            if((j.pos_x-1)==0 || (j.pos_x-1)>=3)){
              //Vérifie si le joueur marche sur un pouvoir
              if((j.pos_x-1)>=3)){
                effetPouvoir(j, j.pos_x-1, j.pos_y, jeu);
              }
              j.pos_x = j.pos_x--;
            }
            j.direction='S';
            break;

          //Les 4 touches différentes pour avoir 4 joueurs en local sur le même clavier
          case SDL_SCANCODE_D:
          case SDL_SCANCODE_H:
          case SDL_SCANCODE_L:
          case SDL_SCANCODE_RIGHT:
            //Vérifie si le joueur ne va pas dans un mur ou dans un joueur
            if((j.pos_y+1)==0 || (j.pos_y+1)>=3)){
              //Vérifie si le joueur marche sur un pouvoir
              if((j.pos_y+1)>=3)){
                effetPouvoir(j, j.pos_x, j.pos_y+1, jeu);
              }
              j.pos_y = j.pos_y++;
            }
            j.direction='E';
            break;

          //Les 4 touches différentes pour poser une bombe
          case SDL_SCANCODE_A:
          case SDL_SCANCODE_R:
          case SDL_SCANCODE_U:
          case SDL_SCANCODE_RCTRL:
            //Direction Nord
            if(j.direction=='N'){
              Detruire(j,j2,j3,j4,j.pos_x+1,j.pos_y,jeu);
            }
            //Direction Ouest
            else if(j.direction=='W'){
              Detruire(j,j2,j3,j4,j.pos_x,j.pos_y-1,jeu);
            }
            //Direction Sud
            else if(j.direction=='S'){
              Detruire(j,j2,j3,j4,j.pos_x-1,j.pos_y,jeu);
            }
            //Direction Est
            else if(j.direction=='E'){
              Detruire(j,j2,j3,j4,j.pos_x,j.pos_y+1,jeu);
            }
        }
    }
  }*/
}

void Bombe(joueur_t j1, joueur_t j2, joueur_t j3, joueur_t j4, int x, int y, int jeu[M][N]){
  if(valides(x,y) && jeu[x][y]!=2 && jeu[x][y]!=1){
    Detruire(j1,j2,j3,j4,x,y,jeu);
  }
}

//Verifie si les coordonnées sont dans la matrice
int valides(int x, int y){
  return((x>0 && x<M-1) && (y>0 && y<N-1));
}

void effetBombe(joueur_t j1, joueur_t j2, joueur_t j3, joueur_t j4, int x, int y, int jeu[M][N]){
  srand( time(NULL));

  //effet de la bombe sur un joueur sur la trajectoire de la bombe
  if(x==j1.pos_x && y==j1.pos_y){
    if(j1.vie==1){
      j1.vie=0;
    }
    else{
      /*MORT*/
    }
  }

  if(x==j2.pos_x && y==j2.pos_y){
    if(j2.vie==1){
      j2.vie=0;
    }
    else{
      /*MORT*/
    }
  }

  if(x==j3.pos_x && y==j3.pos_y){
    if(j3.vie==1){
      j3.vie=0;
    }
    else{
      /*MORT*/
    }
  }

  if(x==j4.pos_x && y==j4.pos_y){
    if(j4.vie==1){
      j4.vie=0;
    }
    else{
      /*MORT*/
    }
  }

  //effet de la bombe sur un mur cassable
  else if(jeu[x][y]==2){
    jeu[x][y] = -5;
    sleep(1); // aide pour l'affichage
    jeu[x][y] = rand()%4 + 3; // a vérifier pour faire apparaitre les pouvoir au sol
    if(rand()%100 < 25){ // il y a 25% de chance qu'un mur explosé ne donne pas de pouvoir
      jeu[x][y]=0;
    }
  }

  //supprime le pouvoir au sol
  else if(jeu[x][y]>=3){
    jeu[x][y] = -5;
    sleep(1); // aide pour l'affichage

    jeu[x][y]=0;
  }
}

//une bombe détruit dans les 4 directions les objets cassable (mur cassable, pouvoir au sol, joueur)
void Detruire(joueur_t j1, joueur_t j2, joueur_t j3, joueur_t j4, int x, int y, int jeu[M][N]){
  int i;
  int puissB=j1.puissance;

  /*Cette instruction permet d'enlever
  tout les cas impossible à modifier et
  cela permet de rester dans la matrice*/
  for(i=0; i<puissB && (valides(x,y-i) && (jeu[x][y-i]==0 && jeu[x][y-i]!=1)); i++);
  //Effet de la bombe vers la gauche
  effetBombe(j1,j2,j3,j4,x,y-i,jeu);

  for(i=0; i<puissB && (valides(x,y+i) && (jeu[x][y+i]==0 && jeu[x][y+i]!=1)); i++);
  //Effet de la bombe vers la droite
  effetBombe(j1,j2,j3,j4,x,y+i,jeu);

  for(i=0; i<puissB && (valides(x-i,y) && (jeu[x-i][y]==0 && jeu[x-i][y]!=1)); i++);
  //Effet de la bombe vers le haut
  effetBombe(j1,j2,j3,j4,x-i,y,jeu);

  for(i=0; i<puissB && (valides(x+i,y) && (jeu[x+i][y]==0 && jeu[x+i][y]!=1)); i++);
  //Effet de la bombe vers le bas
  effetBombe(j1,j2,j3,j4,x+i,y,jeu);
}

void effetPouvoir(joueur_t j, int x, int y, int jeu[M][N]){
  //PV de la vitesse
  if(jeu[x][y]==3){
    //Vitesse max : 9
    if(j.vitesse<9){
      j.vitesse++;
      /*Augmenter de 10% la vitesse*/
    }
  }

  //PV de la puissance
  else if(jeu[x][y]==4){
    //Puissance max : 9
    if(j.puissance<9){
      j.puissance++;
    }
  }

  //Nombre de bombe du joueur
  else if(jeu[x][y]==5){
    //Nombre de bombe max : 9
    if(j.nb_bomb<9){
      j.nb_bomb++;
    }
  }

  //Pouvoir d'une vie en plus
  else if(jeu[x][y]==6){
    //Nombre de vie en plus max : 1
    if(j.vie==0){
      j.vie++;
    }
  }
}
