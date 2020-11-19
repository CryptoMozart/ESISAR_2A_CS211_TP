#include <stdlib.h>
#include <stdio.h>


char caractere_tab(char caractere, char tab[], int longueur){
	int i;
	for(i=0;i<longueur;i++)
		if(caractere==tab[i])
			return 1;
	return 0;
}

int main(){
	printf("entre le nom du fichier à lire: ");
	char* nom[50];
	scanf("%s",nom);
	char voyelle[12]={'a','e','i','o','u','y','A','E','I','O','U','Y'};
	FILE* fichier = NULL;
	fichier = fopen(nom,"r");
	int compteur= 0;
	if(fichier != NULL){
		int compteur_caractere;
		do {
			compteur_caractere=fgetc(fichier);
			if(caractere_tab(compteur_caractere,voyelle,12))
				compteur++;
			}while(compteur_caractere != EOF);
	fclose(fichier);
	}
	printf("%d", compteur);
}
	
