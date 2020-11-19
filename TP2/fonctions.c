#include "fonctions.h"


// 1ere question

int nombres_impairs(){
    FILE *file_numbers;
    if((file_numbers = fopen("./nombres_impairs.txt", "w")) != NULL){
        for(int i = 1; i < 100; i += 2){
            fprintf(file_numbers, "%d\n", i);
        }

        fclose(file_numbers);
    }else{
        printf("ERROR");
    }
    return 0;
}

//2eme question

int is_in_tab(char search, char needle[], int length){
    int is_in_tab = 0;
    for(int i = 0; i < length; i++){
        if(search == needle[i]){
            is_in_tab = 1;
            break;
        }
    }
    return is_in_tab;
}

int compte_voyelles(char* filepath){
    FILE* file;
    char vowels[12] = {'a', 'e', 'i', 'o', 'u', 'y', 'A', 'E', 'I', 'O', 'U', 'Y'};
    int counter = 0;
    int character_counter;
    if((file = fopen(filepath, "r")) != NULL){
        while(character_counter != EOF){
            character_counter = fgetc(file);
            if(is_in_tab(character_counter, vowels, 12)){
                counter++;
            }
        }
        fclose(file);
    }else{
        printf("ERROR");
    }
    return counter;
}

//3eme question
int txt_steganography(char* filepath){
    FILE *source, *destination;

    int current_char = 0;
    int current_bit = 0, buffer_size = 0;
    unsigned char current_buffer = 0;

    source = fopen(filepath, "r");
    destination = fopen("result.txt", "w");
    if(source == NULL || destination == NULL){
        printf("ERROR");
        return 1;
    }

    while(current_char != EOF){
        current_char = fgetc(source);
        if(isalpha(current_char)){
            current_bit = isupper(current_char) > 0;
            if(buffer_size < 8){
                current_buffer = current_buffer  << 1;
                current_buffer += current_bit;
                buffer_size++;
            }else{
                fputc(current_buffer, destination);
                buffer_size = 1;
                current_buffer = current_bit;
            }
        }
    }
    fclose(source);
    fclose(destination);
    return 0;
}

int bmp_steganography(char* filepath){
    FILE *picture, *destination;
    fichierEntete file_header;
    imageEntete picture_header;
    couleurPallete color_pallet;
    picture = fopen(filepath, "r");
    destination = fopen("source.jpg", "w");

    if(picture == NULL || destination == NULL){
        printf("ERROR");
        return 1;
    }

    fread(&file_header, sizeof(fichierEntete), 1, picture);
    fseek(picture, sizeof(fichierEntete), SEEK_SET);
    debug_file_header(file_header);

    fread(&picture_header, sizeof(imageEntete), 1, picture);
    fseek(picture, sizeof(imageEntete), SEEK_CUR);
    debug_picture_header(picture_header);
    fseek(picture, file_header.offset, SEEK_SET);

    int buffer_size = 0;
    unsigned char *picture_pixels;
    unsigned char current_buffer = 0;

    picture_pixels = malloc(sizeof(char)*picture_header.tailleImage);
    if(picture_pixels == NULL){
        printf("ERROR");
    }else{
        fread(picture_pixels, sizeof(char)*picture_header.tailleImage, 1, picture);


        for(int i = 0; i < (picture_header.tailleImage); i++){
            if(buffer_size < 8){
                current_buffer = current_buffer << 1;
                current_buffer += picture_pixels[i] & 1;
                buffer_size++;
            }else{
                fputc(current_buffer, destination);
                current_buffer = picture_pixels[i];
                buffer_size = 1;
            }
        }
    }
    // Dans le premier fichier nous avions ce lien
    // File source : https://commons.wikimedia.org/wiki/File:Richard_Stallman_-_F%C3%AAte_de_l%27Humanit%C3%A9_2014_-_010.jpg
    free(picture_pixels);
    fclose(picture);
    fclose(destination);
    return 0;
}

int bmp_encode(char* filepath_source, char* filepath_original, char* filepath_transporter){
    FILE *source, *original, *transporter;

    fichierEntete original_file_header;
    imageEntete original_picture_header;
    couleurPallete original_color_pallet;

    source = fopen(filepath_source, "r");
    original = fopen(filepath_original, "r");
    transporter = fopen(filepath_transporter, "w");

    if(source == NULL || original == NULL || transporter == NULL){
        printf("ERROR OPENING FILES");
        return 1;
    }

    fread(&original_file_header, sizeof(fichierEntete), 1, original);
    fwrite(&original_file_header, sizeof(fichierEntete), 1, transporter);
    fseek(original, sizeof(fichierEntete), SEEK_SET);

    fread(&original_picture_header, sizeof(imageEntete), 1, original);
    fwrite(&original_picture_header, sizeof(imageEntete), 1, transporter);
    fseek(original, sizeof(imageEntete), SEEK_CUR);

    fseek(original, original_file_header.offset, SEEK_SET);
    fseek(transporter, original_file_header.offset, SEEK_SET);

    unsigned char *source_data;
    unsigned char *original_picture_pixels;
    unsigned char source_buffer = 0;
    unsigned char current_buffer = 0;

    fseek(source, 0, SEEK_END);
    int source_size = ftell(source);
    fseek(source, 0, SEEK_SET);
    source_data = malloc(sizeof(char)*source_size);

    original_picture_pixels = malloc(sizeof(char)*original_picture_header.tailleImage);

    if(source_data == NULL || original_picture_pixels == NULL){
        printf("ERROR MEMORY ALLOCATION");
    }else{
        fread(source_data, sizeof(char)*source_size, 1, source);
        fread(original_picture_pixels, sizeof(char)*original_picture_header.tailleImage, 1, original);

        for (int index_source = 0; index_source < original_picture_header.tailleImage; index_source++) {
            if(index_source < source_size){
                source_buffer = source_data[index_source];
                for(int i = 0; i < 8; i++){
                    current_buffer = original_picture_pixels[i + 8*index_source];
                    if(source_buffer >> (7-i) & 1){
                        current_buffer = current_buffer | 1;
                    }else{
                        current_buffer = current_buffer & 0xFE;
                    }
                    fputc(current_buffer, transporter);
                }
            }else if(index_source >= 8*source_size){
                fputc(original_picture_pixels[index_source], transporter);
            }

        }
        free(source_data);
        free(original_picture_pixels);
    }

    fclose(source);
    fclose(original);
    fclose(transporter);
    return 0;
}

void debug_file_header(fichierEntete file_header){
    printf("signature : %d\n", file_header.signature);
    printf("tailleFichier : %d\n", file_header.tailleFichier);
    printf("reserve : %d\n", file_header.reserve);
    printf("offset : %d\n", file_header.offset);
}
void debug_picture_header(imageEntete picture_header){
    printf("tailleEntete : %d\n", picture_header.tailleEntete);
    printf("largeur : %d\n", picture_header.largeur);
    printf("hauteur : %d\n", picture_header.hauteur);
    printf("plan : %d\n", picture_header.plan);
    printf("profondeur : %d\n", picture_header.profondeur);
    printf("compression : %d\n", picture_header.compression);
    printf("tailleImage : %d\n", picture_header.tailleImage);
    printf("resolutionHorizontale : %d\n", picture_header.resolutionHorizontale);
    printf("resolutionVerticale : %d\n", picture_header.resolutionVerticale);
    printf("nombreCouleurs : %d\n", picture_header.nombreCouleurs);
    printf("nombreCouleursImportantes : %d\n", picture_header.nombreCouleursImportantes);
}
void debug_color_pallet(couleurPallete color_pallet){
    printf("R : %d\n", color_pallet.R);
    printf("V : %d\n", color_pallet.V);
    printf("B : %d\n", color_pallet.B);
    printf("reserve : %d\n", color_pallet.reserve);
}
