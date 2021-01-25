#include <stdio.h>

int somme(int entier){
	int somme=0, i;
	for (i = 1; i < entier; i++) {
		somme=somme+entier;
	}
	return somme;
}

int Double(int entier){
	return somme(entier)*2;
}

int main() {
	printf("%d\n",somme(4));
	printf("%d\n",Double(4));
	return 0;
}


 
