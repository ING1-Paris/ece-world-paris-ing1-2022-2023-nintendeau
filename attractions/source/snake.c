/*
 ! By Léon DALLE - ECE ING1 - TD13
 *
 *
 *
 *
 *    ███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗
 *    ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝
 *    ███████╗██╔██╗ ██║███████║█████╔╝ █████╗
 *    ╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝
 *    ███████║██║ ╚████║██║  ██║██║  ██╗███████╗
 *    ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝
 *
 *
 *
 * Jeu : Reproduction d'un Snake à deux joueurs sur Allegro 4
 * Objectif : Fluidité du jeu, gestion des collisions, gestion des scores sans fichier externe
 * Contrainte : Utilisation de listes chainées pour la gestion du serpent
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#include <stdbool.h>
#include "../header/snake.h"

//* Constantes pour la taille des blocs et de l'écran
#define BLOCK_SIZE 20
#define SPEED 1
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

//* Structures pour les blocs du serpent et la nourriture
typedef struct snake {
    int x, y;
    int direction;
    int previous_pos_x, previous_pos_y;
    struct snake *next;
    bool is_head;
} snake;
typedef struct food {
    int x;
    int y;
} food;

//définition des fonctions :
void init_snake(snake *head, int x, int y);
void init_food(food *food);
BITMAP* image_loader(const char* filepath);
SAMPLE* sound_loader(const char* filepath);
void lib_memoire(snake *head, food *Food, snake *head2, food *Food2, BITMAP *game, BITMAP *buffer, SAMPLE* music);
void draw_snake(snake *head, int color, BITMAP *game);
void add_block(snake *head);
void move_snake(snake *head);
int collision_mort(snake *head1, snake *head2);
int collision_food(snake *head, food *food);
void gestion_mouvements(snake *head1, snake *head2);

int snake(){
    set_window_title("Snake");
    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT); //buffer est la fenêtre où on affiche tous les texte et autres
    BITMAP *game = create_bitmap(SCREEN_HEIGHT, SCREEN_HEIGHT); //game is a square

    BITMAP * logo_img = image_loader("assets/snake/logo.bmp");
    BITMAP * game_over_img = image_loader("assets/snake/game_over.bmp");

    //?Initialisation des variables
    int game_over = 0;
    int score1 = 0;
    int score2 = 0;
    int color1 = makecol(255, 0, 0);
    int color2 = makecol(0, 0, 255);
    int buffer_color = makecol(0x47, 0xE1, 0x0C);
    int game_color = makecol(0, 0, 0);
    int food_colour = makecol(71, 225, 12);

    //?Initialisation du serpent 1 (ses caractéristiques sont dans la fonction init_snake : position, direction, prochain bloc et si c'est la tête) et la nourriture et de sa position (seule caractéristique)
    snake *head1 = malloc(sizeof(snake));
    snake *head2 = malloc(sizeof(snake));
    init_snake(head1, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);
    init_snake(head2, SCREEN_HEIGHT / 3, SCREEN_HEIGHT /3);
    food *food1 = malloc(sizeof(food));
    food *food2 = malloc(sizeof(food));
    init_food(food1);
    init_food(food2);

    SAMPLE *music = sound_loader("attractions/assets/tag/music.wav");
    play_sample(music, 255, 127, 1000, 1);


    //Boucle principale
    while(!key[KEY_ESC] && !game_over){
        //Effacement de l'écran (actualisation) et de affichage de la nourriture et du score
        clear_to_color(game, game_color);
        clear_to_color(buffer, buffer_color);
        //print logo on buffer on the far-right, a bit reduced with masked_stretch_blit
        masked_stretch_blit(logo_img, buffer, 0, 0, logo_img->w, logo_img->h, SCREEN_HEIGHT + 20, 20, logo_img->w / 2, logo_img->h / 2);

        //print scores
        textprintf_ex(buffer, font, SCREEN_HEIGHT + 10, 100, makecol(0,0,0), -1, "Score Joueur 1 : %d", score1);
        textprintf_ex(buffer, font, SCREEN_HEIGHT + 10, 120, makecol(0,0,0), -1, "Score Joueur 2 : %d", score2);

        //print food and snake
        rectfill(game, food1->x, food1->y, food1->x + BLOCK_SIZE, food1->y + BLOCK_SIZE, food_colour);
        rectfill(game, food2->x, food2->y, food2->x + BLOCK_SIZE, food2->y + BLOCK_SIZE, food_colour);
        draw_snake(head1, color1, game);
        draw_snake(head2, color2, game);

        //Déplacement du serpent 1
        gestion_mouvements(head1, head2);
        move_snake(head1);
        move_snake(head2);


        //Gestion des collisions : si le serpent sort de l'écran, si le serpent se touche lui-même ou si la tête du serpent touche le corps du serpent
        int looser = collision_mort(head1, head2);
        if (looser != 0) {
            if (looser == 1) {
                printf("Game Over ! first player loosed !\n");
            }else{
                printf("Game Over ! second player loosed !\n");
            }
            game_over = 1;
        }

        //Gestion des collisions avec la nourriture
        if (collision_food(head1, food1) || collision_food(head1, food2)){
            score1++;
            add_block(head1);
        }
        if (collision_food(head2, food1) || collision_food(head2, food2)){
            score2++;
            add_block(head2);
        }

        //Actualisation de l'écran
        rest(120);
        blit(game, buffer, 0, 0, 0, 0, SCREEN_HEIGHT, SCREEN_HEIGHT);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }


    //¤Fin du programme
    lib_memoire(head1, food1, head2, food2, buffer, game, music);
    allegro_exit();
    return 0;
}


//*Fonctions d'initialisation
void init_snake(snake *head, int x, int y) { //¤Initialisation de la nourriture (position aléatoire)
    head->x = x;
    head->y = y;
    head->direction = rand() % 4; //direction aléatoire
    head->previous_pos_x = -30;
    head->previous_pos_y = -30;
    head->is_head = true;
    head->next = NULL;
}

void init_food(food *food) { //¤Affichage du serpent à partir de la tête
    food->x = rand() % (SCREEN_HEIGHT - BLOCK_SIZE);
    food->y = rand() % (SCREEN_HEIGHT - BLOCK_SIZE);
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

void lib_memoire(snake *head, food *Food, snake *head2, food *Food2, BITMAP *game, BITMAP *buffer, SAMPLE *music) { //¤Fonction pour libérer la mémoire
    snake *current_block = head;
    snake *next_block = head->next;
    while (current_block != NULL) {
        next_block = current_block->next;
        free(current_block);
        current_block = next_block;
    }
    current_block = head2;
    next_block = head2->next;
    while (current_block != NULL) {
        next_block = current_block->next;
        free(current_block);
        current_block = next_block;
    }
    free(Food);
    free(Food2);
    stop_sample(music);
    destroy_sample(music);
    destroy_bitmap(game);
    destroy_bitmap(buffer);
}
//*############################################################################################################################################

//!Fonctions relatives au serpent et appelées souvent
void draw_snake(snake *head, int color, BITMAP *game) { //¤Fonction pour libérer la mémoire
    snake *current_block = head;
    while (current_block != NULL) {
        rectfill(game, current_block->x, current_block->y, current_block->x + BLOCK_SIZE, current_block->y + BLOCK_SIZE, color);
        current_block = current_block->next;
    }
}

void add_block(snake *head) { //¤ Fonction pour ajouter un bloc au serpent
    snake *current_block = head;
    while (current_block->next != NULL) {
        current_block = current_block->next;
    }
    snake *new_block = malloc(sizeof(snake));
    new_block->x = current_block->previous_pos_x;
    new_block->y = current_block->previous_pos_y;
    new_block->direction = current_block->direction;
    new_block->is_head = false;
    new_block->next = NULL;
    current_block->next = new_block;
}

void move_snake(snake *head){ //¤ On bouge chaque bloc du serpent en fonction de la direction du bloc qui le précède
    int previous_pos_x = head->x;
    int previous_pos_y = head->y;
    //Déplacement du serpent 1
    if (head->direction == 0) {
        head->y -= BLOCK_SIZE;
    }
    if (head->direction == 1) {
        head->x += BLOCK_SIZE;
    }
    if (head->direction == 2) {
        head->y += BLOCK_SIZE;
    }
    if (head->direction == 3) {
        head->x -= BLOCK_SIZE;
    }

    //on transmet les coordonnées du bloc précédent au bloc suivant
    snake *current_block = head->next;
    while (current_block != NULL) {
        int temp_x = current_block->x;
        int temp_y = current_block->y;
        current_block->x = previous_pos_x;
        current_block->y = previous_pos_y;
        previous_pos_x = temp_x;
        previous_pos_y = temp_y;
        current_block = current_block->next;
    }
}

int collision_mort(snake *head1, snake *head2){ //¤ On vérifie si le serpent sort de l'écran ou se mord la queue ou mord l'autre serpent
    int looser = 0;
    //vérifier si le serpent sort de l'écran
    if (head1->x < 0 || head1->x >= SCREEN_HEIGHT || head1->y < 0 || head1->y >= SCREEN_HEIGHT) {
        printf("Game Over ! Le serpent 1 a perdu !\n");
        looser = 1;
    }
    if (head2->x < 0 || head2->x >= SCREEN_HEIGHT || head2->y < 0 || head2->y >= SCREEN_HEIGHT) {
        printf("Game Over ! Le serpent 2 a perdu !\n");
        looser = 1;
    }

    //vérifier si le serpent se mord la queue
    //Gestion des collisions avec le serpent
    snake *current_block = head1->next;
    while (current_block != NULL) {
        if (head1->x == current_block->x && head1->y == current_block->y) {
            printf("Game Over ! first player ate himself !\n");
            looser = 1;
        }
        current_block = current_block->next;
    }

    current_block = head2->next;
    while (current_block != NULL) {
        if (head2->x == current_block->x && head2->y == current_block->y) {
            printf("Game Over ! second player ate himself !\n");
            looser = 1;
        }
        current_block = current_block->next;
    }

    //collisions entre les deux serpents : si la tête du serpent 1 touche le corps du serpent 2 ou inversement
    current_block = head2;
    while (current_block != NULL) {
        if (head1->x <= current_block->x + BLOCK_SIZE && current_block->x <= head1->x + BLOCK_SIZE && head1->y <= current_block->y + BLOCK_SIZE && current_block->y <= head1->y + BLOCK_SIZE) {
            printf("Game Over ! first player ate second player !\n");
            looser = 1;
        }
        current_block = current_block->next;
    }

    current_block = head1;
    while (current_block != NULL) {
        if (head2->x <= current_block->x + BLOCK_SIZE && current_block->x <= head2->x + BLOCK_SIZE && head2->y <= current_block->y + BLOCK_SIZE && current_block->y <= head2->y + BLOCK_SIZE) {
            printf("Game Over ! second player ate first player !\n");
            looser = 1;
        }
        current_block = current_block->next;
    }

    return looser;
}

int collision_food(snake *head, food *food) { //¤ On vérifie si le serpent mange la nourriture
    if (head->x <= food->x + BLOCK_SIZE && food->x <= head->x + BLOCK_SIZE && head->y <= food->y + BLOCK_SIZE && food->y <= head->y + BLOCK_SIZE) {
        init_food(food);
        return 1;
    }else{
        return 0;
    }
}

void gestion_mouvements(snake *head1, snake *head2){
    //Déplacement du serpent 1 en fonction de la direction (0 = haut, 1 = droite, 2 = bas, d3 = gauche, pas de demi-tour possible)
    //move snake 1 with arrows
    if (key[KEY_UP] && head1->direction != 2) {
        head1->direction = 0;
    }else if (key[KEY_LEFT] && head1->direction != 1) {
        head1->direction = 3;
    }else if (key[KEY_DOWN] && head1->direction != 0) {
        head1->direction = 2;
    }else if (key[KEY_RIGHT] && head1->direction != 3) {
        head1->direction = 1;
    }

    //move snake 2 with ZQSD (azerty keyboard)
    if (key[KEY_W] && head2->direction != 2) {
        head2->direction = 0;
    }else if (key[KEY_A] && head2->direction != 1) {
        head2->direction = 3;
    }else if (key[KEY_S] && head2->direction != 0) {
        head2->direction = 2;
    }else if (key[KEY_D] && head2->direction != 3) {
        head2->direction = 1;
    }
}
//!############################################################################################################################################