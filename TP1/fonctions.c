#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"


void swap(int* a, int* b){
	int c = *a;
	*a = *b;
	*b = c;
}

void affiche(int* a, int n){
	int i;
	for (i = 0 ; i < n ; i++){
		printf("%d ", a[i]);
	}
	printf("\n\n");
}

int bubblesort(int* array, int size){
	int i = 0, j, nb_comparison=0;
	do{
		for(j = 0; j < size-1-i; j++){
			if(array[j] > array[j+1]){
				swap(&array[j], &array[j+1]);
			}
			nb_comparison++;
		}	
		i++;
	}while(!is_sorted(array, size, asc));
	return nb_comparison;
}

int asc(int first_value, int second_value){
    return first_value <= second_value;
}

int desc(int first_value, int second_value){
    return first_value >= second_value;
}

int bubblesort_pointer(int* array, int size, int (*sort_type)(int, int)){
    int i = 0, j, nb_comparison=0;
    do{
        for(j = 0; j < size-1-i; j++){
            if(!(*sort_type)(array[j], array[j+1])){
                swap(&array[j], &array[j+1]);
            }
            nb_comparison++;
        }
        i++;
    }while(!is_sorted(array, size, (*sort_type)));
    return nb_comparison;
}

int insertionsort(int* array, int size){
	int i,j, nb_comparison = 0, value;
	for(i = 1; i < size; i++){
		value = array[i];
		j=i-1;
		while(j >= 0 && array[j] > value){
			array[j+1] = array[j];
			j--;
			nb_comparison++;
		}
		array[j+1] = value;
	}
	return nb_comparison;
}

int is_sorted(int* array, int size, int (*sort_type)(int, int)){
	int i, sorted;
	for(i = 0; i < size-1; i++){
		sorted = (*sort_type)(array[i], array[i+1]);
		if(!sorted){
			break;
		}
	}
	return sorted;
}
int compare(int* a, int *b, int n){
	int i;
	for(i=0; i < n ; i++){
		if (a[i] != b[i]){
			printf("Comparison FAILED at index %d\n\n", i);
			return i;
		}
	}
	printf("Comparison OK\n\n");
	return -1;	
}



void merge(int* tab, int* tmp, int left, int mid, int right, int* cnt) {
	int lpos=left;
    int rpos=mid;
    int i=0;
    while ((lpos<=mid-1 || rpos <=right)&&i<=right-left+1)
    {
    if((tab[lpos]<tab[rpos] || rpos>right)&& lpos <= mid-1)
    {
        tmp[i+left]= tab[lpos];
        lpos++;
        (*cnt)++;
    }
    else
    {
        tmp[i+left] = tab[rpos];
        rpos++;
        (*cnt)++;
    }
    i++;


    }
	for (i=0;i<right-left+1;i++)
	{
  		tab[i+left]=tmp[i+left];
}
	
}

int mergesort_recursive(int* tab, int* tmp, int left, int right, int* cnt){ 
  int x=1;
  while(x<right-left+1)
    {
    	x*=2;
    }
  	x=x/2;
  	if(right-left>1)
  	{

    	mergesort_recursive(tab,tmp,left,left+x-1,cnt);
    	mergesort_recursive(tab,tmp,left+x,right,cnt);



	}
  	if(right-left>=1)
  	{
    	merge(tab,tmp,left,left+x,right,cnt);
  	}
    
	
}

int mergesort(int* tab, int size){
    int cnt = 0;
    int *tmp= (int*)malloc(size);
    mergesort_recursive(tab, tmp, 0, size-1, &cnt);
    free(tmp);
    return cnt;
}
