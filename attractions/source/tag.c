
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
 * Contrainte : Utilisation d'animations                                                       
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "../header/tag.h"

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
    int score;
} Bonhomme;

//définir chaque fonction : 
void lib_memory(BITMAP * buffer, BITMAP * calque_collision, BITMAP * background, BITMAP * bonhomme1, BITMAP * bonhomme2, BITMAP * torche1 , BITMAP * torche2, BITMAP * cheminee1, BITMAP * cheminee2, SAMPLE * jump, SAMPLE * music);
void init_chat(Bonhomme *bonhomme1, Bonhomme *bonhomme2);
BITMAP* image_loader(const char* filepath);
SAMPLE* sound_loader(const char* filepath);
void arrow_manager(BITMAP * buffer, Bonhomme bonhomme1, Bonhomme bonhomme2, int compteur, int * fleche_liste, int init);
void mouvement(Bonhomme *bonhomme, BITMAP *calque_collision, int groundLevel, int HORIZONTAL_SPEED, int MAX_JUMP_HEIGHT, double GRAVITY, double MAX_FALL_SPEED, int UP, int RIGHT, int LEFT, SAMPLE * jump);
void loadNumberBitmaps(BITMAP *numberBitmaps[10]);
void displayNumber(BITMAP* destination, BITMAP* numberBitmaps[], int number, int x, int y);
void draw_background_elements_animation(BITMAP *buffer, BITMAP *torche1, BITMAP *torche2, BITMAP *cheminee1, BITMAP *cheminee2, int compteur);

int tag(){
    set_window_title("Chat");

    //! Initialisation des paramètres
    double GRAVITY = 0.4;
    double MAX_FALL_SPEED = 20;
    int HORIZONTAL_SPEED = 6;
    int MAX_JUMP_HEIGHT = 14;
    int groundLevel = SCREEN_HEIGHT - 39;
    int counter_duration = 60;
    //!##########################################

    // Création du buffer et des images principales
    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP * map = image_loader("attractions/assets/tag/map.bmp");
    BITMAP * calque_collisions = image_loader("attractions/assets/tag/map_collisions.bmp");
    
    // Création du bonhomme
    Bonhomme bonhomme1 = {image_loader("attractions/assets/tag/player_1.bmp"), SCREEN_WIDTH/2, SCREEN_HEIGHT - 150, 0, 0, FALSE};
    Bonhomme bonhomme2 = {image_loader("attractions/assets/tag/player_2.bmp"), SCREEN_WIDTH/3, SCREEN_HEIGHT - 150, 0, 0, FALSE};
    init_chat(&bonhomme1, &bonhomme2);


    //Variables pour la flèche, le score et le chrono
    clock_t start;
    int fleche_liste[20];
    for (int i = 0; i < 20; ++i) {
        fleche_liste[i] = i+1;
    }
    int compteur = 1;
    bool reverse = FALSE;

    //Variables pour le chronomètre
    BITMAP* numberBitmaps[10];
    loadNumberBitmaps(numberBitmaps);
    int chrono = 1;
    clock_t start_chrono = clock();

    //Initialisation des sons et des images externes
    SAMPLE *music = sound_loader("attractions/assets/tag/music.wav");
    SAMPLE *jump = sound_loader("attractions/assets/tag/jump.wav");
    play_sample(music, 255, 127, 1000, 1);
    BITMAP *torche1 = image_loader("attractions/assets/tag/torche1.bmp");
    BITMAP *torche2 = image_loader("attractions/assets/tag/torche2.bmp");
    BITMAP *cheminee1 = image_loader("attractions/assets/tag/cheminee1.bmp");
    BITMAP *cheminee2 = image_loader("attractions/assets/tag/cheminee2.bmp");

    // Boucle principale
    while (!key[KEY_ESC]) {
        // Update bonhomme's position
        mouvement(&bonhomme1, calque_collisions, groundLevel, HORIZONTAL_SPEED, MAX_JUMP_HEIGHT, GRAVITY, MAX_FALL_SPEED, KEY_UP, KEY_RIGHT, KEY_LEFT, jump);
        mouvement(&bonhomme2, calque_collisions, groundLevel, HORIZONTAL_SPEED, MAX_JUMP_HEIGHT, GRAVITY, MAX_FALL_SPEED, KEY_W, KEY_D, KEY_A, jump);

        
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

        //score++ of the player who is the chat
        if (bonhomme1.isChat) {
            bonhomme1.score++;
        }
        else {
            bonhomme2.score++;
        }
        // Effacer l'écran précédent
        clear(buffer);

        // Draw bonhomme sprite at its updated position
        stretch_blit(calque_collisions, buffer, 0, 0, calque_collisions->w, calque_collisions->h, 0, 0, buffer->w, buffer->h);
        stretch_blit(map, buffer, 0, 0, map->w, map->h, 0, 0, buffer->w, buffer->h);
        
        //display the number of the chrono 
        chrono = counter_duration - ((clock() - start_chrono) / CLOCKS_PER_SEC);
        displayNumber(buffer, numberBitmaps, chrono, 10, 10);
        draw_background_elements_animation(buffer, torche1, torche2, cheminee1, cheminee2, chrono);
        arrow_manager(buffer, bonhomme1, bonhomme2, compteur, fleche_liste, reverse);
        draw_sprite(buffer, bonhomme1.sprite, bonhomme1.x, bonhomme1.y);
        draw_sprite(buffer, bonhomme2.sprite, bonhomme2.x, bonhomme2.y);

        // Refresh screen
        vsync();
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // Update arrow counter
        if (compteur == 19) {
            reverse = TRUE;
        }else if(compteur == 0){
            reverse = FALSE;
        }
        (reverse)?compteur--:compteur++;

        //if the chrono is over, the game is over
        if (chrono == 0) {
            break;
        }
    }

    //Let's see who lost (who has the highest score)
    (bonhomme1.score > bonhomme2.score)? printf("Player 1 lost !\n"): printf("Player 2 lost !\n");

    // Fermeture d'Allegro
    lib_memory(buffer, calque_collisions, map, bonhomme1.sprite, bonhomme2.sprite, torche1, torche2, cheminee1, cheminee2, jump, music);
    
    //allegro_exit();
    return 0;
}

void lib_memory(BITMAP * buffer, BITMAP * calque_collision, BITMAP * background, BITMAP * bonhomme1, BITMAP * bonhomme2, BITMAP * torche1 , BITMAP * torche2, BITMAP * cheminee1, BITMAP * cheminee2, SAMPLE * jump, SAMPLE * music){
    //Free memory
    stop_sample(music);
    destroy_bitmap(buffer);
    destroy_bitmap(calque_collision);
    destroy_bitmap(background);
    destroy_bitmap(bonhomme1);
    destroy_bitmap(bonhomme2);
    destroy_bitmap(torche1);
    destroy_bitmap(torche2);
    destroy_bitmap(cheminee1);
    destroy_bitmap(cheminee2);
    destroy_sample(jump);
    destroy_sample(music);
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
    BITMAP * img = load_bitmap(filepath, NULL);
    if (!img) {
        char clion_filepath[100];
        strcpy(clion_filepath, "../");
        strcat(clion_filepath, filepath);
        img = load_bitmap(clion_filepath, NULL);
        
        if (!img) {
            allegro_message("Erreur d'importation d'image : %s", filepath);
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
    return img;
}

SAMPLE* sound_loader(const char* filepath){
    // on vérifie que les BITMAPS ont bien été initialisés
    SAMPLE * sound = load_bitmap(filepath, NULL);
    if (!sound) {
        char clion_filepath[100];
        strcpy(clion_filepath, "../");
        strcat(clion_filepath, filepath);
        sound = load_bitmap(clion_filepath, NULL);
        
        if (!sound) {
            allegro_message("Erreur d'importation d'image : %s", filepath);
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
    return sound;
}

void arrow_manager(BITMAP * buffer, Bonhomme bonhomme1, Bonhomme bonhomme2, int compteur, int * fleche_liste, int init){
    BITMAP * arrow = image_loader("attractions/assets/tag/arrow.bmp");
    //draw the arrow on top of the chat player and make like it is boucning up and down
    int currentindex = fleche_liste[compteur];
    if (bonhomme1.isChat) {
        draw_sprite(buffer, arrow, bonhomme1.x + bonhomme1.sprite->w/2 - arrow->w/2, bonhomme1.y - arrow->h - currentindex);
    }else{
        draw_sprite(buffer, arrow, bonhomme2.x + bonhomme2.sprite->w/2 - arrow->w/2, bonhomme2.y - arrow->h - currentindex);
    }

    free(arrow);
}

void mouvement(Bonhomme *bonhomme, BITMAP *calque_collision, int groundLevel, int HORIZONTAL_SPEED, int MAX_JUMP_HEIGHT, double GRAVITY, double MAX_FALL_SPEED, int UP, int RIGHT, int LEFT, SAMPLE * jump) {
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
        play_sample(jump, 255, 128, 1000, FALSE);
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

void loadNumberBitmaps(BITMAP *numberBitmaps[10]) {
    // Load the bitmaps for numbers 0 to 9
    numberBitmaps[0] = image_loader("attractions/assets/tag/0.bmp");
    numberBitmaps[1] = image_loader("attractions/assets/tag/1.bmp");
    numberBitmaps[2] = image_loader("attractions/assets/tag/2.bmp");
    numberBitmaps[3] = image_loader("attractions/assets/tag/3.bmp");
    numberBitmaps[4] = image_loader("attractions/assets/tag/4.bmp");
    numberBitmaps[5] = image_loader("attractions/assets/tag/5.bmp");
    numberBitmaps[6] = image_loader("attractions/assets/tag/6.bmp");
    numberBitmaps[7] = image_loader("attractions/assets/tag/7.bmp");
    numberBitmaps[8] = image_loader("attractions/assets/tag/8.bmp");
    numberBitmaps[9] = image_loader("attractions/assets/tag/9.bmp");

    // Check if any bitmap loading failed
    for (int i = 0; i < 10; i++) {
        if (!numberBitmaps[i]) {
            // Handle the error (e.g., print an error message and exit the program)
            allegro_message("Failed to load number bitmap %d", i);
            exit(1);
        }
    }
}

void displayNumber(BITMAP* destination, BITMAP* numberBitmaps[], int number, int x, int y) {
    // Display the nnumber of the digits following the first number of number 
    // (e.g., if number is 98, first display a 9, then an 8)
    //first digit of number
    if (number < 0) {
        number = 0;
    }
    int firstDigit = number / 10;
    //second digit of number
    int secondDigit = number % 10;

    // Display in big, centered
    masked_stretch_blit(numberBitmaps[firstDigit], destination, 0, 0, numberBitmaps[firstDigit]->w, numberBitmaps[firstDigit]->h, x, y, 50, 50);
    masked_stretch_blit(numberBitmaps[secondDigit], destination, 0, 0, numberBitmaps[secondDigit]->w, numberBitmaps[secondDigit]->h, x + 50, y, 50, 50);
}

void draw_background_elements_animation(BITMAP *buffer, BITMAP *torche1, BITMAP *torche2, BITMAP *cheminee1, BITMAP *cheminee2, int compteur){
    // Draw the background elements following random patterns to size
    if (compteur %2 == 0){
        stretch_blit(cheminee1, buffer, 0, 0, cheminee1->w, cheminee1->h, 360, 120, 40, 40);
        stretch_blit(torche1, buffer, 0, 0, torche1->w, torche1->h, 280, 120, 40, 40);
        stretch_blit(torche2, buffer, 0, 0, torche2->w, torche2->h, 800, 400, 40, 40);
        stretch_blit(torche1, buffer, 0, 0, torche1->w, torche1->h, 560, 520, 40, 40);
        stretch_blit(torche2, buffer, 0, 0, torche2->w, torche2->h, 320, 720, 40, 40);
        stretch_blit(torche1, buffer, 0, 0, torche1->w, torche1->h, 520, 720, 40, 40);
    } else {
        stretch_blit(cheminee2, buffer, 0, 0, cheminee2->w, cheminee2->h, 360, 120, 40, 40);
        stretch_blit(torche2, buffer, 0, 0, torche2->w, torche2->h, 280, 120, 40, 40);
        stretch_blit(torche1, buffer, 0, 0, torche1->w, torche1->h, 800, 400, 40, 40);
        stretch_blit(torche2, buffer, 0, 0, torche2->w, torche2->h, 560, 520, 40, 40);
        stretch_blit(torche1, buffer, 0, 0, torche1->w, torche1->h, 320, 720, 40, 40);
        stretch_blit(torche2, buffer, 0, 0, torche2->w, torche2->h, 520, 720, 40, 40);
    }
}


