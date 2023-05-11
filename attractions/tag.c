
/*
 ! By Léon DALLE - ECE ING1 - TD13 
 *
 *    ████████╗███╗   ██╗████████╗    ████████╗ █████╗  ██████╗ 
 *    ╚══██╔══╝████╗  ██║╚══██╔══╝    ╚══██╔══╝██╔══██╗██╔════╝ 
 *       ██║   ██╔██╗ ██║   ██║          ██║   ███████║██║  ███╗
 *       ██║   ██║╚██╗██║   ██║          ██║   ██╔══██║██║   ██║
 *       ██║   ██║ ╚████║   ██║          ██║   ██║  ██║╚██████╔╝
 *       ╚═╝   ╚═╝  ╚═══╝   ╚═╝          ╚═╝   ╚═╝  ╚═╝ ╚═════╝ 
 *
 * Jeu : Reproduction d'un jeu de chat (tnt tag, attrape-loup, etc.)
 * Objectif : Fluidité du jeu, gestion des collisions, gestion des scores sans fichier externe
 * Contrainte : Utilisation d'animations ?                                                       
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

// Structure pour le bonhomme
typedef struct {
    BITMAP *sprite;     // Sprite du bonhomme
    int x, y;           // Coordonnées du bonhomme
    double xspeed, yspeed; // Vitesse horizontale et verticale du bonhomme
} Bonhomme;

void init_allegro(){ //¤Initialisation des serpents (direction aléatoire)
    //Initialisation de la seed pour les nombres aléatoires
    srand(time(NULL));
    //Initialisation d'Allegro
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_window_title("Chat");
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0) {
        allegro_message("Erreur relative à Allegro");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}
void mouvement(Bonhomme *bonhomme, int groundLevel, int HORIZONTAL_SPEED, int MAX_JUMP_HEIGHT, double GRAVITY, double MAX_FALL_SPEED, int UP, int RIGHT, int LEFT){
    // Update bonhomme's position
    bonhomme->x += bonhomme->xspeed;
    bonhomme->y += (int)bonhomme->yspeed;

    // Handle keyboard input
    if (key[RIGHT]) {
        // Move right
        bonhomme->xspeed = HORIZONTAL_SPEED;
    } else if (key[LEFT]) {
        // Move left
        bonhomme->xspeed = -HORIZONTAL_SPEED;
    } else {
        // Stop horizontal movement
        bonhomme->xspeed = 0;
    }

    // Jump only if the bonhomme is on the ground
    if (key[UP] && bonhomme->y == groundLevel) {
        bonhomme->yspeed = -MAX_JUMP_HEIGHT; // Set the initial vertical speed for the jump
    }

    // Apply gravity
    bonhomme->yspeed += GRAVITY;

    // Limit the maximum falling speed
    if (bonhomme->yspeed >= MAX_FALL_SPEED) {
        bonhomme->yspeed = MAX_FALL_SPEED;
    }

    // Limit the maximum height of the jump
    if (bonhomme->y > groundLevel) {
        bonhomme->y = groundLevel;
        bonhomme->yspeed = 0;
    }
}
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

int main()
{
    // Initialisation d'Allegro
    init_allegro();

    //! Initialisation des variables du mouvement
    double GRAVITY = 0.5;
    double MAX_FALL_SPEED = 12;
    int HORIZONTAL_SPEED = 7;
    int MAX_JUMP_HEIGHT = 12;
    int groundLevel = SCREEN_HEIGHT - 100;
    //!##########################################

    // Création du buffer
    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Création du bonhomme
    Bonhomme bonhomme1 = {image_loader("assets/palais_des_glaces/player_1.bmp"), SCREEN_WIDTH/2, groundLevel, 0, 0};
    Bonhomme bonhomme2 = {image_loader("assets/palais_des_glaces/player_2.bmp"), SCREEN_WIDTH/3, groundLevel, 0, 0};

    // Boucle principale
    while (!key[KEY_ESC]) {
        
        // Update bonhomme's position
        mouvement(&bonhomme1, groundLevel, HORIZONTAL_SPEED, MAX_JUMP_HEIGHT, GRAVITY, MAX_FALL_SPEED, KEY_UP, KEY_RIGHT, KEY_LEFT);
        mouvement(&bonhomme2, groundLevel, HORIZONTAL_SPEED, MAX_JUMP_HEIGHT, GRAVITY, MAX_FALL_SPEED, KEY_W, KEY_D, KEY_A);

        // Effacer l'écran précédent
        clear(buffer);

        // Draw bonhomme sprite at its updated position
        draw_sprite(buffer, bonhomme1.sprite, bonhomme1.x, bonhomme1.y);
        draw_sprite(buffer, bonhomme2.sprite, bonhomme2.x, bonhomme2.y);

        // Refresh screen
        vsync();
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    destroy_bitmap(bonhomme1.sprite);
    destroy_bitmap(bonhomme2.sprite);
    destroy_bitmap(buffer);

    // Fermeture d'Allegro
    allegro_exit();
    return 0;
}END_OF_MAIN();



