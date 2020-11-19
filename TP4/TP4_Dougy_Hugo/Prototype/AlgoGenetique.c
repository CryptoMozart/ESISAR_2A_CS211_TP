#include <stdio.h> 
#include <stdlib.h>
#include <strings.h> 
#include <string.h> 
#include <time.h>
#include <unistd.h> 
#include "AlgoGenetique.h" 
#include <math.h>


#define lire(gene,i)    (i%2)?(gene[i/2]&0xF):(gene[i/2]>>4); 

void affiche(unsigned char *gene)
{
	char code[]="+-*/"; 
	int i=0,res;  
	// the last gene is useless 
	while (i<(NBGENE-1)) {
		res=lire(gene,i); 
		if (i%2)
			printf("%c ",code[res%4]); 
		else 
			printf("0x%x ",res);	
		i=i+1; 
	}
	printf("\n"); 
}

int calcul(serpent *g)
{
	char code[] = "+-*/";
	int i=0,res;
	char tab[NBGENE];
	while (i<(NBGENE-1)) {
		res = lire(g -> gene, i);
		if(i%2)
			tab[i] = code[res%4];
		else
			tab[i] = res;
		i++;
	}
	afficher_tab(tab,NBGENE);
	convert_tab(tab, NBGENE); //on converti les operateurs avec les constantes définies dans AlgoGenetique.h
	 for(int k = 0; k < NBGENE-1; k++){
		printf("%d ", tab[k]);
	}
	printf("\n");
	int indice = 0;
	//on parcour le tableau pour savoir si on a une multiplication ou une division.
	// On stocke le résultat dans le premier opérande et on décale ensuite le tableau de 2 et on met 0 0 dans les deux dernières cases (pour faire "+ 0"
	while(indice < NBGENE-1) {
		if(indice % 2){
			if(tab[indice] == multiplication){
				tab[indice -1] = tab[indice -1] * tab[indice +1];
				decalertab(tab,NBGENE,indice);
			}
			else if(tab[indice] == division){
				if(tab[indice+1] == 0)
					return MAX;
				else
					tab[indice -1] = tab[indice -1] / tab[indice +1];

				decalertab(tab,NBGENE,indice);
			}
	}
		if(tab[indice+2] == multiplication || tab[indice+2] == division)
			indice --;
		else
			indice ++;
	}
	 for(int k = 0; k < NBGENE-1; k++){
		printf("%d ", tab[k]);
	}
	 printf("\n");
	for(int j = 0; j< NBGENE-1; j++){
		if(j%2 == 0){
			if(tab[j] == addition)
				tab[j+1] = tab[j-1] = tab[j+1];
			else if (tab[j] == soustraction)
				tab[j+1] = tab[j-1] - tab[j+1];
	}
	}
	g -> score = tab[NBGENE-1];
	//on ajoute ou on soustrait les operandes et on les stocke dans le deuxième operande. Ainsi le score du serpent sera le dernier opérande
	return (g -> score);
}

void convert_tab(char *tab, int taille){
	for(int i= 0; i<taille;i++){
		if(i%2){
			if(tab[i] == '+')
				tab[i] = addition;
			else if(tab[i] == '-')
				tab[i] = soustraction;
			else if(tab[i] == '*')
				tab[i] = multiplication;
			else if(tab[i] == '/')
				tab[i] = division;
		}
	}
}

void afficher_tab(char *tab, int taille){
	 for(int k = 0; k < taille-1; k++){
		if(k%2) 
			printf("%c ",tab[k]);
		else 
			printf("%d ",tab[k]);
	}
	 printf("\n");
	//peremt d'afficher l'expression arithmétique
}

void decalertab(char *tab, int taille, int indice){
        for(int i =indice; i<taille-2-indice;i++){
                tab[i] = tab[i+2];
        }
        tab[taille-3] = 0;
        tab[taille-2] = 0;
}


void testCalcul() 
{
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
		calcul(&test[i]);
		if (expect != test[i].score) 
			printf("error\n");	
		else
			printf("ok\n");
	}
}

void selection(groupe *population,groupe *parents)
{
	//pour séléctionner les meilleurs membres de la population, on trie les membres en fonction de leur resultat
	//On effectue un tri par insertion
	int i,j;
	serpent value;
	 for (i=0; i < population->nombre; i++){
                j = i;
                value = population->membres[i];
                while (j >0 && value.score < (population->membres[j-1]).score){
                        population->membres[j] = population->membres[j-1];
                        j--;
                }
                population->membres[j] = value;
        }
	for( int i =0; i < NBPARENTS; i++){
		parents -> membres[i] = population->membres[i];
	}
}

int evaluation(groupe *population) 
{	
	int resultat;
	int score;
	int result; 
	int somme_score = 0;
	int moyenne;
	for(int i = 0; i < population->nombre; i++){
		//on effectue les actions pour tous les membres de la population
		resultat = calcul(&(population->membres[i]));
		//on calcule l'expression arithmétique pour chaque serpent de la population
		score = abs(resultat - 0x666);
		//on calcule le fitness
		(population->membres[i]).score = score;
		//on associe le score de chaque serpent et on regarde si on a un serpent maléfique
		if((population -> membres [i]).score == SEEK)
			result =  0;
		else
			result =  1;
		//calcul de la somme des termes 
		somme_score += (population -> membres[i]).score;
	}
	moyenne = somme_score / (population -> nombre);
	printf("Moyenne: %d\n", moyenne);
	return result;
}

void generationAleatoire(groupe *population)
{
	// la structure groupe est un groupe de serpent. n tableau de NBGENE/2.
	for( int i = 0; i < population -> nombre; i++){ 
		//on remplie le groupe jusqu'au nombre de la population
		for(int j = 0; j < NBGENE/2; j++){
			//on parcoure le tableau de chaque serpent et on le remplie avec un bit aléatoire
			//on présice que gene est un tableau d'unsigned char
			(population -> membres[i]).gene[j] =  (unsigned char) rand();
		}
	}
}

void reproduction(groupe *population,groupe *parents)
{
	int parent1;
	int parent2;
	for(int i=0;i< NBPARENTS; i++){
		parent1 = rand() % NBPARENTS;
		parent2 = rand() % NBPARENTS;
		//on choisit deux parent aléatoirement parmis les meilleurs serpent chosit à la selection
		while(parent1 == parent2)
			parent2 = rand() % NBPARENTS;
		//si les deux parents sont les mêmes (ca serait bizarre sinon) , on retire le 2ème parent
		crossing_over(&(parents -> membres[parent1]),&( parents -> membres[parent2]), &(population->membres[i]));
	}

}

void crossing_over(serpent *parent1, serpent *parent2, serpent *fils){
	int croisement = rand() % (NBGENE/2);
	//on affecte la première partie du gène du parent1 au fils 
	for(int i = 0; i<croisement; i++)
		fils -> gene[i] = parent1 -> gene[i];
	
	//on affecte la seconde partie du gene du parent2 au fils
	for(int j = croisement; j< NBGENE/2; j++)
		fils -> gene[j] = parent2 -> gene[j];
		

}


void mutation (groupe *population)
{
for(int i = 0; i < NBPOPULATION; i++){

                for(int j = 0; j < NBGENE/2; j++){

                        if((rand()%200) < TAUX_MUT)
				population->membres[i].gene[j] = (char)rand();
                }
        }

}


