#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/loader.h"

BITMAP* image_loader(const char* filepath){
    // on vérifie que les BITMAPS ont bien été initialisés
    char clion_filepath[100];
    strcpy(clion_filepath, "../");
    strcat(clion_filepath, filepath);
    BITMAP *img = load_bitmap(clion_filepath, NULL);
    if (!img) {
        img = load_bitmap(filepath, NULL);
        if (!img) {
            allegro_message("Erreur d'importation d'd'image");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
    return img;
}

SAMPLE* sound_loader(const char* filepath){
    // on vérifie que les BITMAPS ont bien été initialisés
    SAMPLE * sound = load_sample(filepath);
    if (!sound) {
        char clion_filepath[100];
        strcpy(clion_filepath, "../");
        strcat(clion_filepath, filepath);
        sound = load_sample(clion_filepath);

        if (!sound) {
            allegro_message("Erreur d'importation d'image : %s", filepath);
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
    return sound;
}

FILE *file_loader(const char* filepath, const char* mode){
    FILE *file = fopen(filepath, mode);
    if (!file) {
        char clion_filepath[100];
        strcpy(clion_filepath, "../");
        strcat(clion_filepath, filepath);
        file = fopen(clion_filepath, mode);
        if (!file) {
            allegro_message("Erreur d'importation de fichier : %s", filepath);
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
    return file;
}