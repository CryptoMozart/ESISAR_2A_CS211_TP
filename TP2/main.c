#include "fonctions.h"
#include<stdio.h>


int main(){
    //Préparation
    nombres_impairs();
    printf("Compte voyelles : %d\n", compte_voyelles("transporteur.txt"));

    /*
     * Explication à faire en français avant de le coder (préparation) :
     *
     * L'algorithme va parcourir chaque caractère du fichier puis va
     * déterminer si le caractère est une majuscule ou une minuscule.
     * Cela donne un bit qui est ajouté à un buffer d'une taille d'un octet.
     * Le principe de ce buffer est qu'on rajoute chaque bit "à droite" jusqu'à ce
     * que le buffer soit plein. Une fois que le buffer est plein, on l'enregistre
     * dans le fichier.
     */
    txt_steganography("transporteur.txt");
    bmp_steganography("transporteur.bmp");
    bmp_encode("source.jpg", "originel.bmp", "result.bmp");
    bmp_steganography("result.bmp");
    return 0;
}