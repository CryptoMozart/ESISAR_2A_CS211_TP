#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE* flot;
	flot = fopen("nombre_impaire2.txt","w");
	for(int i = 1; i<200;i +=2){
		fprintf(flot,"%d ",i);
	}
	printf("\n");
	fclose(flot);
}	
