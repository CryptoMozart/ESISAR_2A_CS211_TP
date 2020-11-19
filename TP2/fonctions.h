#include "bitmap.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int nombres_impairs();

int is_in_tab(char search, char needle[], int length);

int compte_voyelles(char* filepath);

int txt_steganography(char* filepath);

void debug_file_header(fichierEntete file_header);
void debug_picture_header(imageEntete picture_header);
void debug_color_pallet(couleurPallete color_pallet);

int bmp_steganography(char* filepath);
int bmp_encode(char* filepath_source, char* filepath_original, char* filepath_transporter);
