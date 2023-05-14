
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
    int previous_x;   // Position X précédente du bonhomme
    int previous_y;   // Position Y précédente du bonhomme
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

void mouvement(Bonhomme *bonhomme, BITMAP *calque_collision, int groundLevel, int HORIZONTAL_SPEED, int MAX_JUMP_HEIGHT, double GRAVITY, double MAX_FALL_SPEED, int UP, int RIGHT, int LEFT) {
    // Update bonhomme's position
    bonhomme->previous_x = bonhomme->x;
    bonhomme->previous_y = bonhomme->y;

    // Update bonhomme's position
    bonhomme->x += bonhomme->xspeed;
    bonhomme->y += (int)bonhomme->yspeed;

    //colors of each corners of the bonhomme
    int color_down_left = getpixel(calque_collision, (bonhomme->x)*calque_collision->w/SCREEN_W, (bonhomme->y + bonhomme->sprite->h/1.3)*calque_collision->h/SCREEN_H + 7);
    int color_down_right = getpixel(calque_collision, (bonhomme->x + bonhomme->sprite->w)*calque_collision->w/SCREEN_W, (bonhomme->y + bonhomme->sprite->h/1.3)*calque_collision->h/SCREEN_H + 7);
    int color_up_left = getpixel(calque_collision, (bonhomme->x)*calque_collision->w/SCREEN_W, (bonhomme->y + bonhomme->sprite->h)*calque_collision->h/SCREEN_H - 25);  
    int color_up_right = getpixel(calque_collision, (bonhomme->x + bonhomme->sprite->w)*calque_collision->w/SCREEN_W, (bonhomme->y + bonhomme->sprite->h)*calque_collision->h/SCREEN_H - 25);
    int color_mid_right = getpixel(calque_collision, (bonhomme->x + bonhomme->sprite->w)*calque_collision->w/SCREEN_W, (bonhomme->y + bonhomme->sprite->h/1.3)*calque_collision->h/SCREEN_H);
    int color_mid_left = getpixel(calque_collision, (bonhomme->x)*calque_collision->w/SCREEN_W, (bonhomme->y + bonhomme->sprite->h/1.3)*calque_collision->h/SCREEN_H );
    int wall = makecol(255, 0, 0);
    int isOnGround = (color_down_left == wall || color_down_right == wall) ? TRUE : FALSE;
    int isHeadOnCeiling = (color_up_left == wall || color_up_right == wall) ? TRUE : FALSE;

    // Handle keyboard input
    if (key[RIGHT]) {
        // Move right
        if (bonhomme->xspeed >= 0 && color_mid_right != wall) {
            bonhomme->xspeed = HORIZONTAL_SPEED;
        } else {
            bonhomme->xspeed = 0;
        }
    } else if (key[LEFT]) {
        // Move left
        if (bonhomme->xspeed <= 0 && color_mid_left != wall) {
            bonhomme->xspeed = -HORIZONTAL_SPEED;
        } else {
            bonhomme->xspeed = 0;
        }
    } else {
        // Stop horizontal movement
        bonhomme->xspeed = 0;
    }

    // Prevent bonhomme from falling through the ground
    if ((color_down_left == wall && color_up_left != wall)|| (color_down_right == wall && color_up_right != wall)) {
        bonhomme->y = bonhomme->previous_y;
        bonhomme->yspeed = 0;
        printf("On est collé au mur\n");

    }

    // Prevent Bonhomme from going head first into a platform
    if ((color_up_left == wall || color_up_right == wall)) {
        bonhomme->y = bonhomme->previous_y;
        bonhomme->yspeed = 0;
    }

    // Prevent Bonhomme from going through a wall horizontally
    if (((color_down_left == wall && color_mid_left == wall && color_up_left == wall ) || (color_down_right == wall && color_mid_right == wall && color_up_right == wall))) {
        bonhomme->x = bonhomme->previous_x;
        
    }


    // Jump only if the bonhomme is on the ground or on a platform
    if (key[UP] && isOnGround) {
        bonhomme->yspeed = -MAX_JUMP_HEIGHT; // Set the initial vertical speed for the jump
    }

    //when the middle of the bonhomme is on a platform, he goes back to previous position
    if (color_mid_left == wall && color_mid_right == wall) {
        bonhomme->x = bonhomme->previous_x;
    }

    // Apply gravity
    bonhomme->yspeed += GRAVITY;

    // Limit the falling speed
    if (bonhomme->yspeed > MAX_FALL_SPEED) {
        bonhomme->yspeed = MAX_FALL_SPEED;
    }

    // Limit the movements to the screen's size
    if (bonhomme->x < 0) {
        bonhomme->x = 0;
        bonhomme->xspeed = 0;
    } else if (bonhomme->x > SCREEN_W - bonhomme->sprite->w) {
        bonhomme->x = SCREEN_W - bonhomme->sprite->w;
        bonhomme->xspeed = 0;
    } else if (bonhomme->y < 0) {
        bonhomme->y = 0;
        bonhomme->yspeed = 0;
    } else if (bonhomme->y > SCREEN_H - bonhomme->sprite->h) {
        bonhomme->y = SCREEN_H - bonhomme->sprite->h;
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
    double GRAVITY = 0.3;
    double MAX_FALL_SPEED = 12;
    int HORIZONTAL_SPEED = 6;
    int MAX_JUMP_HEIGHT = 14;
    int groundLevel = SCREEN_HEIGHT - 110;
    //!##########################################

    // Création du buffer
    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP * map = image_loader("assets/tag/map.bmp");
    BITMAP * calque_collisions = image_loader("assets/tag/map_collisions.bmp");

    // Création du bonhomme
    Bonhomme bonhomme1 = {image_loader("assets/tag/player_1.bmp"), SCREEN_WIDTH/2, groundLevel, 0, 0};
    Bonhomme bonhomme2 = {image_loader("assets/tag/player_2.bmp"), SCREEN_WIDTH/3, groundLevel, 0, 0};

    // Boucle principale
    while (!key[KEY_ESC]) {
        
        // Update bonhomme's position
        mouvement(&bonhomme1, calque_collisions, groundLevel, HORIZONTAL_SPEED, MAX_JUMP_HEIGHT, GRAVITY, MAX_FALL_SPEED, KEY_UP, KEY_RIGHT, KEY_LEFT);
        mouvement(&bonhomme2, calque_collisions, groundLevel, HORIZONTAL_SPEED, MAX_JUMP_HEIGHT, GRAVITY, MAX_FALL_SPEED, KEY_W, KEY_D, KEY_A);

        // Effacer l'écran précédent
        clear(buffer);

        // Draw bonhomme sprite at its updated position
        stretch_blit(calque_collisions, buffer, 0, 0, calque_collisions->w, calque_collisions->h, 0, 0, buffer->w, buffer->h);
        //stretch_blit(map, buffer, 0, 0, map->w, map->h, 0, 0, buffer->w, buffer->h);
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



