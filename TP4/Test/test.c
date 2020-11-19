#include <stdio.h>
#include <stdlib.h>



void decalertab(int *tab, int taille){
	for(int i =0; i<taille-2;i++){
		tab[i] = tab[i+2];
	}
	tab[taille-3] = 0;
	tab[taille-2] = 0;
}

int main(){
	int tab[11] = {0,1,2,3,4,5,6,7,8,9};
	decalertab(tab, 11);
	for(int i = 0; i<10; i++){
		printf("%d ",tab[i]);
	}
}
