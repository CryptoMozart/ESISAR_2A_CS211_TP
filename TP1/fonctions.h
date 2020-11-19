#include <stdio.h>



void swap(int* a, int* b);
int asc(int first_value, int second_value);
int desc(int first_value, int second_value);

int compare(int* a, int *b, int n);
void affiche(int* a, int n);
void merge (int* tab, int* tmp, int left, int mid, int right, int* cnt);
int bubblesort(int* array, int size);
int bubblesort_pointer(int* array, int size, int (*sort_type)(int, int));
int insertionsort(int* array, int size);
int is_sorted(int* array, int size, int (*sort_type)(int, int));
int mergesort_recursive(int* tab, int* tmp, int left, int right, int* cnt);
int mergesort(int* tab, int size);
