#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Ici, on est obligé d'utiliser la notation struct xxx,
car la structure s'auto-référence!*/
typedef struct node {
		char data ;
		struct node *link ;
		} Lnode ;


/* Insertion en "tête de liste" */
void insertionTete(Lnode **ph,char item){
	Lnode *nouveau = malloc(sizeof(Lnode));
	if(nouveau == NULL)
		exit(EXIT_FAILURE);
	
	/* insertion d'un nouvel élément en début de queue */
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
	 /*  on créer une liste temporaire pour se déplace dans la liste chainée */
	while(liste_temp -> link != NULL)
		liste_temp = liste_temp -> link;
	liste_temp -> link = nouveau;
	
}	

/* Suppression en "tête de liste" */
void suppressionTete(Lnode **ph){
	 if(*ph == NULL)
		exit(EXIT_FAILURE);
	Lnode *asupprimer = *ph;
	 /* création de l'élément à supprimer en tête de liste */ 
	*ph = (*ph) -> link;
	 /* le premier élément de la liste devient le second element de la liste. Donc link de link de la liste */
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

/* Procédure d'affichage de la liste. Ne doit pas être modifiée!!! */
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

/* Programme principal. Ne doit pas être modifié!!! */
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
