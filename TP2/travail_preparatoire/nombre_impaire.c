#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE* nombre_impaire;
	nombre_impaire=fopen("nombre_impaire.txt","w");
	int i;
	for(i=1;i<=200;i++){
		if(i%2!=0)
		fprintf(nombre_impaire,"%d ",i);
		}
	fclose(nombre_impaire);
	return EXIT_SUCCESS;
}
