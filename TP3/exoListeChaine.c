#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Ici, on est oblig� d'utiliser la notation struct xxx,
car la structure s'auto-r�f�rence!*/
typedef struct node {
		char data ;
		struct node *link ;
		} Lnode ;


/* Insertion en "t�te de liste" */
void insertionTete(Lnode **ph,char item){
	Lnode *nouveau = malloc(sizeof(Lnode));
	if(nouveau == NULL)
		exit(EXIT_FAILURE);
	
	/* insertion d'un nouvel �l�ment en d�but de queue */
	nouveau -> data = item; 
	nouveau -> link = *ph;
	*ph = nouveau;

}

/* Insertion en "queue de liste" */
void insertionQueue(Lnode **ph,char item)	{
	  Lnode *nouveau = malloc(sizeof(Lnode));	
	if(nouveau == NULL)
		exit(EXIT_FAILURE);

	nouveau -> data = item;
	nouveau -> link = NULL;
	Lnode *liste_temp;
        liste_temp = *ph;
	 /*  on cr�er une liste temporaire pour se d�place dans la liste chain�e */
	while(liste_temp -> link != NULL)
		liste_temp = liste_temp -> link;
	liste_temp -> link = nouveau;
	
}	

/* Suppression en "t�te de liste" */
void suppressionTete(Lnode **ph){
	 if(*ph == NULL)
		exit(EXIT_FAILURE);
	Lnode *asupprimer = *ph;
	 /* cr�ation de l'�l�ment � supprimer en t�te de liste */ 
	*ph = (*ph) -> link;
	 /* le premier �l�ment de la liste devient le second element de la liste. Donc link de link de la liste */
	free(asupprimer);

}

/* Suppression en "Queue" de liste" */
void suppressionQueue(Lnode **ph){
	Lnode *asupprimer = *ph;
	Lnode *liste_temp = *ph;
	while(liste_temp -> link != NULL) {
		asupprimer = liste_temp;
		liste_temp = liste_temp -> link; }
	asupprimer -> link = NULL;
	free(liste_temp);
}

/* Proc�dure d'affichage de la liste. Ne doit pas �tre modifi�e!!! */
void listeAffiche(Lnode * ptr){
	if ( NULL == ptr )
		printf("Liste vide!") ;
	else 
		printf("Contenu de la liste : ") ;
	while ( NULL != ptr ) 	{
		printf("%c ",ptr->data);
		ptr = ptr->link ;
		}
	printf("\n") ;
	}

/* Programme principal. Ne doit pas �tre modifi�!!! */
int main(void) {
	Lnode *tete = NULL ;

	listeAffiche(tete) ;
	insertionTete(&tete,'a') ;
	listeAffiche(tete) ;
	insertionTete(&tete,'c') ;
	listeAffiche(tete) ;
	insertionQueue(&tete,'t') ;
	listeAffiche(tete) ;
	insertionQueue(&tete,'s') ;
	listeAffiche(tete) ;
	suppressionTete(&tete) ;
	listeAffiche(tete) ;
	suppressionTete(&tete) ;
	listeAffiche(tete) ;
	suppressionQueue(&tete) ;
	listeAffiche(tete) ;
	suppressionTete(&tete) ;
	listeAffiche(tete) ;

   return EXIT_SUCCESS;
   }	
