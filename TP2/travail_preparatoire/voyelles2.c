#include <stdio.h>
#include<stdlib.h>

int is_in(char tab[], char carac, int size){
	for(int i= 0; i<size;i++){
		if(carac == tab[i]) return 1;
	}
	return 0;
}
		
int main(){
	int cnt = 0;
	char carac;
	printf("Entre le nom du fichier à lire: ");
	FILE* flot;
	char nom[50];
	scanf("%s",&nom);
	flot = fopen(nom, "r");
 	char voyelle[12]={'a','e','i','o','u','y','A','E','I','O','U','Y'};
	if(flot == NULL) return EXIT_FAILURE;
	do{
		carac = fgetc(flot);
		if(is_in(voyelle, carac,12)) cnt++;
	}while(carac != EOF);
	printf("%d \n",cnt);
}
		



