#include <stdio.h> 
#include <stdlib.h>
#include <strings.h> 
#include <string.h> 
#include <unistd.h> 
#include "AlgoGenetique.h" 


#define lire(gene,i) (i%2)?(gene[i/2]&0x03):(gene[i/2]>>4)

#define is_operande(i) ((i+1)%2) //permet une meilleure lecture du code
#define is_type_add(res) (res<=0x01) 


//On definit des constantes pour les operateurs
#define multiplication 0x02
#define division 0x03

#define addition 0x00
#define soustraction 0x01


void affiche(unsigned char *gene)
{
	char code[]="+-*/"; 
	int i=0,res;  
	// the last gene is useless 
	while (i<(NBGENE-1)) {
		res=lire(gene,i); 
		if (i%2)
			printf("%c",code[res%4]); 
		else 
			printf("%d",res);	
		i=i+1; 
	}
	printf("\n"); 
}

int calcul(serpent *g){
	

	// variables pour la lecture et le calcul
	int j = 0;
	unsigned char res; //permet le stockage temporaire de chaque gêne
	int save = 0; //permet le stockage lors des iterations

	char flag_prod = 0; 

	//tableaux pour les operations de type addition
	char operateur[NBGENE/2];
	unsigned int operande[NBGENE/2];
	//initialisation des tableaux
	for(int i = 0; i<NBGENE/2; i++){
		operateur[i] = 0;
		operande[i] = 0;
	}

	for (int i = 0; i<NBGENE-1; i++){

		res=lire(g->gene,i); //res est forcement un entier positif

		if (is_operande(i)){

			if (flag_prod){ //si un type produit est detecté à l'iteration precedente

				switch(flag_prod){ //on fait une disjonction en fonction de l'operation à effectuer

					case multiplication:
							save = save * res;
					break;

					case division:
						if(res == 0){
							return MAX; //cas d'une division par 0
						}
						else save = save / res;
					break;

				}
			}
			else save = res; //sinon on enregistre l'operande pour la prochaine iteration
		}

		else {	//Le gêne actuel est un operateur
			if (is_type_add(res)){ //si c'est un type addition on :

				operande[j] = save; //sauvegarde la variable save dans le tableau des calculs d'addition
				operateur[j] = res; //sauvegarde de l'operateur correspondant dans l'autre tableau

				flag_prod=0; //on indique à l'iteration suivante qu'il n'y avait pas de type produit
				j++;
			}
			else flag_prod = res; //sinon on indique à l'iteration suivante que c'est un type produit et on donne son type (* ou /)
		}
	}

	operande[j] = save; //on sauvegarde le dernier element du tableau


	//on commence les operations du type addition.
	save = operande[0];

	for(int k =1; k<NBGENE/2; k++){ //on lit tout le tableau operande et on effectue les operations correspondantes (contenue dans operateur)
		switch (operateur[k-1]){
			case addition:

					save += operande[k];

				break;

			case soustraction:

					save -= operande[k];

				break;
		}
	}

	return save; //on retourne la valeur de l'expression arithmetique
}


void testCalcul() {

int i,expect; 
serpent test[]={
	{"\x67\xc6\x69\x73\x51\xff\x4a\xec\x29\xcd\xba\xab\xf2\xfb\xe3\x46\x7c\xc2\x54\xf8\x1b\xe8\xe7\x8d\x76\x5a\x2e\x63\x33\x9f\xc9\x9a",660},
	{"\x66\x32\x0d\xb7\x31\x58\xa3\x5a\x25\x5d\x05\x17\x58\xe9\x5e\xd4\xab\xb2\xcd\xc6\x9b\xb4\x54\x11\x0e\x82\x74\x41\x21\x3d\xdc\x87",735},
	{"\x70\xe9\x3e\xa1\x41\xe1\xfc\x67\x3e\x01\x7e\x97\xea\xdc\x6b\x96\x8f\x38\x5c\x2a\xec\xb0\x3b\xfb\x32\xaf\x3c\x54\xec\x18\xdb\x5c",694},
	{"\x02\x1a\xfe\x43\xfb\xfa\xaa\x3a\xfb\x29\xd1\xe6\x05\x3c\x7c\x94\x75\xd8\xbe\x61\x89\xf9\x5c\xbb\xa8\x99\x0f\x95\xb1\xeb\xf1\xb3",646},
	{"\x05\xef\xf7\x00\xe9\xa1\x3a\xe5\xca\x0b\xcb\xd0\x48\x47\x64\xbd\x1f\x23\x1e\xa8\x1c\x7b\x64\xc5\x14\x73\x5a\xc5\x5e\x4b\x79\x63",MAX},
	{"\x3b\x70\x64\x24\x11\x9e\x09\xdc\xaa\xd4\xac\xf2\x1b\x10\xaf\x3b\x33\xcd\xe3\x50\x48\x47\x15\x5c\xbb\x6f\x22\x19\xba\x9b\x7d\xf5",543},
	{"\x0b\xe1\x1a\x1c\x7f\x23\xf8\x29\xf8\xa4\x1b\x13\xb5\xca\x4e\xe8\x98\x32\x38\xe0\x79\x4d\x3d\x34\xbc\x5f\x4e\x77\xfa\xcb\x6c\x05",1302},
	{"\xac\x86\x21\x2b\xaa\x1a\x55\xa2\xbe\x70\xb5\x73\x3b\x04\x5c\xd3\x36\x94\xb3\xaf\xe2\xf0\xe4\x9e\x4f\x32\x15\x49\xfd\x82\x4e\xa9",MAX},
	{"\x08\x70\xd4\xb2\x8a\x29\x54\x48\x9a\x0a\xbc\xd5\x0e\x18\xa8\x44\xac\x5b\xf3\x8e\x4c\xd7\x2d\x9b\x09\x42\xe5\x06\xc4\x33\xaf\xcd",MAX},
	{"\xa3\x84\x7f\x2d\xad\xd4\x76\x47\xde\x32\x1c\xec\x4a\xc4\x30\xf6\x20\x23\x85\x6c\xfb\xb2\x07\x04\xf4\xec\x0b\xb9\x20\xba\x86\xc3",MAX},
	{"\x3e\x05\xf1\xec\xd9\x67\x33\xb7\x99\x50\xa3\xe3\x14\xd3\xd9\x34\xf7\x5e\xa0\xf2\x10\xa8\xf6\x05\x94\x01\xbe\xb4\xbc\x44\x78\xfa",727}
	}; 

	for(i=0;i<sizeof(test)/sizeof(serpent);i++) {
		expect=test[i].score; 
		//affiche(&test[i].gene);
		int result = calcul(&test[i]);
		printf("expect : %d, result : %d\n\n", expect, result);
		if (expect != test[i].score) printf("error\n");  
	}
}

void selection(groupe *population,groupe *parents){

	int j = 0;

	//Début d'un tri par insertion sur la population par rapport au score
	for (int i = 0; i < population->nombre; i++){

		j = i;

		serpent vipere = population->membres[i];

		while (j >0 && vipere.score < population->membres[j-1].score){

			population->membres[j] = population->membres[j-1];
			j = j-1;
		}
		population->membres[j] = vipere;
	}
	//Fin du tri par insertion

	//On fait une selection elitiste i.e. on selectionne les X premiers membres
	for (int i = 0; i < parents->nombre; i++){

		parents->membres[i] = population->membres[i];

	}

	//printf("Meilleur score : %d\n", parents->membres[0].score);
}

int evaluation(groupe *population){

	unsigned int somme = 0;
	int reponse = 1;
	int resultat;

	static int counter = 0;

	for(int i=0; i < (population->nombre) ; i++){ //iteration sur toute la population

		resultat = calcul(&(population->membres[i]));

		int score = (resultat-0x666 < 0)? 0x666-resultat : resultat-0x666; //on calcul le score

		population->membres[i].score = score; //On le stock dans la structure

		if(resultat == SEEK) reponse = 0; //Si un serpent vaut 0x666, on a terminer

		somme += score;//on somme tout les score pour effectuer la moyenne
	}

	if(counter >= 5){ //affichage de la moyenne toutes les 5 evaluations

		printf("Moyenne du groupe : %d\n", somme/(population->nombre));

		counter = 0;

	}

	counter++;

	return reponse;
}




void generationAleatoire(groupe *population){

	for(int i = 0; i < population->nombre; i++){

		for(int j = 0; j<(NBGENE/2); j++){ //on parcourt les genes de la population

			population->membres[i].gene[j] = (char)(rand()); //on cast un nombre random dans sur chaque octets des genes
		}
	}
}

void crossing_over(serpent *couple, serpent *serpent, int indice_parent_source, int indice_cross){
	//fonction permettant d'effectuer un cross-over entre deux parents

	for(int k = 0; k < NBGENE/2; k++){

		if(k < indice_cross){

			serpent->gene[k] = couple[indice_parent_source].gene[k];

		}
		else{

			if(k == indice_cross) indice_parent_source = (indice_parent_source+1)%2; 
			//si on est sur l'indice de cross-over, 
			//on change le parent source

			serpent->gene[k] = couple[indice_parent_source].gene[k];
		}

	}

}

void reproduction(groupe *population,groupe *parents){

	for(int i = 0; i < parents->nombre; i= i+2){ //On itere sur les parents

		for(int j = 0; j < ((2*population->nombre)/parents->nombre); j++){ //On génere X enfant/couple

			serpent tableau[2] = {parents->membres[i], parents->membres[i+1]}; //on definit un tableau contenant les deux parents

			int indice_parent_source = rand()%2; //On choisi le 1er parent source au hasard

			if((rand()%100) < PROBA_CROSSOVER){ //si on a un crossover sur l'enfant

				int indice_cross = rand()%(NBGENE/2); //on choisit un indice de cross-over

				crossing_over(tableau, &population->membres[i], indice_parent_source, indice_cross); //on effectue la copie des genes

			}
			else {
				crossing_over(tableau, &population->membres[i], indice_parent_source, NBGENE/2); //on effectue la copie complete du parent source
			}

		}

	}

}


void mutation (groupe *population){

	for(int i = 0; i < population->nombre; i++){

		for(int j = 0; j < NBGENE/2; j++){

			if((rand()%1000) < PROBA_MUTATION){

				population->membres[i].gene[j] = (char)rand();
				//On parcours tout les octets des genes de la population, 
				//On effectue un tirage aleatoire pour savoir si l'on effectue une mutation
				//Si oui on les remplace par un octet généré aleatoirement

			}
		}
	}
}



