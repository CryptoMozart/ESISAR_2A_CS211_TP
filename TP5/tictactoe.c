#include <stdio.h>
#include <stdlib.h>

#define NB 3 

typedef int ttt[NB][NB]; 

#define INFINITY 10000
#define WIN 1000 

#define P1 0x01 	// x
#define P2 0x10		// o 


// evaluate for player 1 P1 (x) 
// si player 1 gagne, score = WIN 
// si player 1 perd, score = -WIN 
// si nul, score = 0 

int evaluate(ttt t)
{
}

void affiche(ttt t)
{
	int l,c; 
	for (l=0;l<NB;l++) {
		for (c=0;c<NB;c++) {
			switch (t[l][c]) {
				case 0x00: printf("|   "); break; 
				case 0x01: printf("| x "); break; 
				case 0x10: printf("| o "); break; 
			}
		} 
		printf("|\n");
	}
	printf("score=%d\n",evaluate(t)); 
}


int fini(ttt t) 
{
}

int minimax (ttt t,int *position,int joueur)
{
}
	



int main() 
{	
	int val,move,joueur=P2; 

	ttt t={{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}}; 


	while (!fini(t)) {
		affiche(t); 
		printf("%d joueur\n",joueur); 
		if ( joueur == P1 ) { 
			printf("enter move\n"); 
			scanf("%d",&move);
			t[move/3][move%3]=P1;
			joueur=P2; 
		} else {
			move=-1; 
			val=minimax(t,&move,P2); 
			printf("best move %d (val=%d)\n",move,val); 
			if ( move != -1 ) { 			
				t[move/3][move%3]=P2;
			}
			joueur=P1; 

		}		  
	}
	affiche(t);
	return EXIT_SUCCESS;
}




