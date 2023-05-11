
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

// Constantes pour la gravité
#define GRAVITY 0.2
#define MAX_FALL_SPEED 8

// Structure pour le bonhomme
typedef struct {
    BITMAP *sprite;     // Sprite du bonhomme
    int x, y;           // Coordonnées du bonhomme
    int xspeed, yspeed; // Vitesse horizontale et verticale du bonhomme
} Bonhomme;

int main()
{
    //Initialisation de la seed pour les nombres aléatoires
    srand(time(NULL));
    //Initialisation d'Allegro
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_window_title("Snake");
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0) {
        allegro_message("GFX ERROR");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Création du bonhomme
    Bonhomme bonhomme = {NULL, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0, 0};
    BITMAP *player_sprite_1 = load_bitmap("../assets/palais_des_glaces/player_1.bmp", NULL);
    // on vérifie que les BITMAPS ont bien été initialisés
    if (!player_sprite_1) {
        player_sprite_1 = load_bitmap("assets/palais_des_glaces/player_1.bmp", NULL);
        if (!player_sprite_1) {
            allegro_message("BITMAP ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
    bonhomme.sprite = player_sprite_1;

    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Boucle principale
    while (!key[KEY_ESC]) {
        // Effacer l'écran précédent
        clear(buffer);

        // Déplacer le bonhomme en fonction des touches pressées
        if (key[KEY_LEFT]) {
            bonhomme.xspeed = -5;
        }
        else if (key[KEY_RIGHT]) {
            bonhomme.xspeed = 5;
        }
        else {
            bonhomme.xspeed = 0;
        }

        if (key[KEY_UP] && bonhomme.yspeed == 0) {
            bonhomme.yspeed = -10;
        }

        // Ajouter la gravité à la vitesse verticale du bonhomme
        bonhomme.yspeed += GRAVITY;
        if (bonhomme.yspeed > MAX_FALL_SPEED) {
            bonhomme.yspeed = MAX_FALL_SPEED;
        }

        // Mettre à jour les coordonnées du bonhomme en fonction de sa vitesse
        bonhomme.x += bonhomme.xspeed;
        bonhomme.y += bonhomme.yspeed;

        // Dessiner le bonhomme à sa nouvelle position
        draw_sprite(buffer, bonhomme.sprite, bonhomme.x, bonhomme.y);

        // Rafraîchir l'écran
        vsync();
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    destroy_bitmap(player_sprite_1);
    // Fermeture d'Allegro
    allegro_exit();
    return 0;
}END_OF_MAIN();



