
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
#include <unistd.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

// Structure pour le bonhomme
typedef struct {
    BITMAP *sprite;     // Sprite du bonhomme
    int x, y;           // Coordonnées du bonhomme
    double xspeed, yspeed; // Vitesse horizontale et verticale du bonhomme
    int previous_x;   // Position X précédente du bonhomme
    int previous_y;   // Position Y précédente du bonhomme
    bool isChat;
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

void init_chat(Bonhomme *bonhomme1, Bonhomme *bonhomme2){
    //set a random chat between the 2 players
    int chat = rand() % 2;
    if (chat == 0) {
        bonhomme1->isChat = !bonhomme1->isChat;
    }else{
        bonhomme2->isChat = !bonhomme2->isChat;
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

void arrow_manager(BITMAP * buffer, Bonhomme bonhomme1, Bonhomme bonhomme2, int * fleche_liste, int compteur, bool reverse){
    BITMAP * arrow = image_loader("assets/tag/arrow.bmp");
    //draw the arrow on top of the chat player and make like it is boucning up and down
    int currentindex = fleche_liste[compteur];
    if (bonhomme1.isChat) {
        draw_sprite(buffer, arrow, bonhomme1.x + bonhomme1.sprite->w/2 - arrow->w/2, bonhomme1.y - arrow->h - currentindex);
    }else{
        draw_sprite(buffer, arrow, bonhomme2.x + bonhomme2.sprite->w/2 - arrow->w/2, bonhomme2.y - arrow->h - currentindex);
    }
    //go to the next index of the list
    if (reverse) {
        compteur--;
    }else{
        compteur++;
    }
    if (compteur == 19 || compteur == 0) {
        reverse = !reverse;
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
    int wall = makecol(255, 0, 0);
    int wall_down_left = (getpixel(calque_collision, bonhomme->x, bonhomme->y + bonhomme->sprite->h) == wall) ? TRUE : FALSE;
    int wall_down_right = (getpixel(calque_collision, bonhomme->x + bonhomme->sprite->w, bonhomme->y + bonhomme->sprite->h) == wall) ? TRUE : FALSE;
    int wall_up_left = (getpixel(calque_collision, bonhomme->x, bonhomme->y) == wall) ? TRUE : FALSE;
    int wall_up_right = (getpixel(calque_collision, bonhomme->x + bonhomme->sprite->w, bonhomme->y) == wall) ? TRUE : FALSE;
    int wall_middle_left = (getpixel(calque_collision, bonhomme->x, bonhomme->y + bonhomme->sprite->h/2) == wall) ? TRUE : FALSE;
    int wall_middle_right = (getpixel(calque_collision, bonhomme->x + bonhomme->sprite->w, bonhomme->y + bonhomme->sprite->h/2) == wall) ? TRUE : FALSE;
    int wall_middle_down = (getpixel(calque_collision, bonhomme->x + bonhomme->sprite->w/2, bonhomme->y + bonhomme->sprite->h) == wall) ? TRUE : FALSE;
    //side is when all the three pixels on the side are red
    int isOnGround = (wall_down_left || wall_down_right) ? TRUE : FALSE;
    if ((isOnGround && wall_up_left && wall_middle_left) || (isOnGround && wall_up_right && wall_middle_right)) {
        bonhomme->y = bonhomme->previous_y;
        bonhomme->yspeed = 0;
    }
    int isHeadOnCeiling = (wall_up_left || wall_up_right) ? TRUE : FALSE;

    // Handle keyboard input
    if (key[RIGHT]) {
        bonhomme->xspeed = HORIZONTAL_SPEED;
    } else if (key[LEFT]) {
        bonhomme->xspeed = -HORIZONTAL_SPEED;
    } else {
        // Stop horizontal movement
        bonhomme->xspeed = 0;
    }

    // Apply gravity
    bonhomme->yspeed += GRAVITY;

    // Limit the falling speed
    if (bonhomme->yspeed >= MAX_FALL_SPEED) {
        bonhomme->yspeed = MAX_FALL_SPEED;
    }

    //Prevent falling when the bonhomme is on a platform (if down right or down left is red)
    if (isOnGround && !wall_up_left && !wall_up_right && !wall_middle_left && !wall_middle_right) {
        bonhomme->y = bonhomme->previous_y;
        bonhomme->yspeed = 0;
    }

    //Prevent  bumping head on ceiling
    if (isHeadOnCeiling && !isOnGround && !wall_middle_left && !wall_middle_right) {
        bonhomme->y = bonhomme->previous_y;
        bonhomme->yspeed = 0;
    }

    //If one of the pixels are red, go back to the previous position
    if ((wall_down_left || wall_down_right || wall_up_left || wall_up_right || wall_middle_left || wall_middle_right) && !wall_middle_down) {
        bonhomme->x = bonhomme->previous_x;
        bonhomme->y = bonhomme->previous_y;
        
        
    }

    // Jump only if the bonhomme is on the ground or on a platform
    if (key[UP] && isOnGround) {
        bonhomme->yspeed = -MAX_JUMP_HEIGHT; // Set the initial vertical speed for the jump
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

int main()
{
    // Initialisation d'Allegro
    init_allegro();

    //! Initialisation des variables du mouvement
    double GRAVITY = 0.4;
    double MAX_FALL_SPEED = 20;
    int HORIZONTAL_SPEED = 6;
    int MAX_JUMP_HEIGHT = 14;
    int groundLevel = SCREEN_HEIGHT - 39;
    //!##########################################

    // Création du buffer
    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP * map = image_loader("assets/tag/map.bmp");
    BITMAP * calque_collisions = image_loader("assets/tag/map_collisions.bmp");
    
    // Création du bonhomme
    Bonhomme bonhomme1 = {image_loader("assets/tag/player_1.bmp"), SCREEN_WIDTH/2, SCREEN_HEIGHT - 150, 0, 0, FALSE};
    Bonhomme bonhomme2 = {image_loader("assets/tag/player_2.bmp"), SCREEN_WIDTH/3, SCREEN_HEIGHT - 150, 0, 0, FALSE};
    init_chat(&bonhomme1, &bonhomme2);

    //Variables pour la flèche
    clock_t start, end;
    int fleche_liste[20];
    for (int i = 0; i < 20; ++i) {
        fleche_liste[i] = i+1;
    }
    int compteur = 1;
    bool reverse = FALSE;

    // Boucle principale
    while (!key[KEY_ESC]) {
        // Update bonhomme's position
        mouvement(&bonhomme1, calque_collisions, groundLevel, HORIZONTAL_SPEED, MAX_JUMP_HEIGHT, GRAVITY, MAX_FALL_SPEED, KEY_UP, KEY_RIGHT, KEY_LEFT);
        mouvement(&bonhomme2, calque_collisions, groundLevel, HORIZONTAL_SPEED, MAX_JUMP_HEIGHT, GRAVITY, MAX_FALL_SPEED, KEY_W, KEY_D, KEY_A);

        
        //when players touch themselves, reverse the chat role but only once every second, to avoid the chat to change every frame
        //example of collision : (head1->x <= current_block->x + BLOCK_SIZE && current_block->x <= head1->x + BLOCK_SIZE && head1->y <= current_block->y + BLOCK_SIZE && current_block->y <= head1->y + BLOCK_SIZE)
        if (bonhomme1.x <= bonhomme2.x + bonhomme2.sprite->w && bonhomme2.x <= bonhomme1.x + bonhomme1.sprite->w && bonhomme1.y <= bonhomme2.y + bonhomme2.sprite->h && bonhomme2.y <= bonhomme1.y + bonhomme1.sprite->h) {
            //if the chat role has not been changed in the last second
            if (clock() - start > 1000) {
                //reverse the chat role
                bonhomme1.isChat = !bonhomme1.isChat;
                bonhomme2.isChat = !bonhomme2.isChat;
                //reset the timer
                start = clock();
            }
        }

        // Effacer l'écran précédent
        clear(buffer);

        // Draw bonhomme sprite at its updated position
        stretch_blit(calque_collisions, buffer, 0, 0, calque_collisions->w, calque_collisions->h, 0, 0, buffer->w, buffer->h);
        stretch_blit(map, buffer, 0, 0, map->w, map->h, 0, 0, buffer->w, buffer->h);

        arrow_manager(buffer, bonhomme1, bonhomme2, fleche_liste, compteur, reverse);
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



