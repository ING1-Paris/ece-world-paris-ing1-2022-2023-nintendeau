
/*
 ! Léon DALLE - ECE ING1 - TD13                                                                                                                      
 *
 *          ___           ___           ___           ___           ___     
 *         /  /\         /__/\         /  /\         /__/|         /  /\    
 *        /  /:/_        \  \:\       /  /::\       |  |:|        /  /:/_   
 *       /  /:/ /\        \  \:\     /  /:/\:\      |  |:|       /  /:/ /\  
 *      /  /:/ /::\   _____\__\:\   /  /:/~/::\   __|  |:|      /  /:/ /:/_ 
 *     /__/:/ /:/\:\ /__/::::::::\ /__/:/ /:/\:\ /__/\_|:|____ /__/:/ /:/ /\
 *     \  \:\/:/~/:/ \  \:\~~\~~\/ \  \:\/:/__\/ \  \:\/:::::/ \  \:\/:/ /:/
 *      \  \::/ /:/   \  \:\  ~~~   \  \::/       \  \::/~~~~   \  \::/ /:/ 
 *       \__\/ /:/     \  \:\        \  \:\        \  \:\        \  \:\/:/  
 *         /__/:/       \  \:\        \  \:\        \  \:\        \  \::/   
 *         \__\/         \__\/         \__\/         \__\/         \__\/    
 * 
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

//* Constantes pour la taille des blocs et de l'écran
#define BLOCK_SIZE 10
#define SPEED 1
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

//*Fonctions d'initialisation
void init_allegro(){
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
}
    //¤Initialisation des serpents (direction aléatoire)
void init_snake(snake *head, int x, int y) {
    head->x = x;
    head->y = y;
    head->direction = rand() % 4; //direction aléatoire
    head->previous_pos_x = x;
    head->previous_pos_y = y;
    head->is_head = true;
    head->next = NULL;
} 
    //¤Initialisation de la nourriture (position aléatoire)
void init_food(food *food) {
    food->x = rand() % (SCREEN_WIDTH - BLOCK_SIZE);
    food->y = rand() % (SCREEN_HEIGHT - BLOCK_SIZE);
}
    //¤Affichage du serpent à partir de la tête
void draw_snake(snake *head, int color) {
    snake *current_block = head;
    while (current_block != NULL) {
        rectfill(screen, current_block->x, current_block->y, current_block->x + BLOCK_SIZE, current_block->y + BLOCK_SIZE, color);
        current_block = current_block->next;
    }
}
    //¤Fonction pour libérer la mémoire
void lib_memoire(snake *head, food *food) {
    snake *current_block = head;
    snake *next_block = head->next;
    while (current_block != NULL) {
        next_block = current_block->next;
        free(current_block);
        current_block = next_block;
    }
    free(food);
}

//!Fonctions relatives au serpent






int main(int argc, char *argv[]){
    init_allegro();
    //?Initialisation des variables 
    int game_over = 0;
    int score1 = 0;
    int score2 = 0;
    int color1 = makecol(255, 0, 0);

    //?Initialisation du serpent 1 (ses caractéristiques sont dans la fonction init_snake : position, direction, prochain bloc et si c'est la tête) et la nourriture et de sa position (seule caractéristique)
    snake *head1 = malloc(sizeof(snake));
    init_snake(head1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    food *food1 = malloc(sizeof(food));
    init_food(food1);

    //Boucle principale
    while(!key[KEY_ESC] && !game_over){
        //Effacement de l'écran (actualisation) et de affichage de la nourriture et du score
        clear_to_color(screen, makecol(0, 0, 0));
        textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "Score : %d", score1);
        rectfill(screen, food1->x, food1->y, food1->x + BLOCK_SIZE, food1->y + BLOCK_SIZE, makecol(0, 255, 0));
        draw_snake(head1, color1);

        

        //Déplacement du serpent 1 en fonction de la direction (0 = haut, 1 = droite, 2 = bas, 3 = gauche, pas de demi-tour possible)
        if (key[KEY_UP] && head1->direction != 2) {
            head1->direction = 0;
        }
        if (key[KEY_RIGHT] && head1->direction != 3) {
            head1->direction = 1;
        }
        if (key[KEY_DOWN] && head1->direction != 0) {
            head1->direction = 2;
        }
        if (key[KEY_LEFT] && head1->direction != 1) {
            head1->direction = 3;
        }

        //Déplacement du serpent 1
        if (head1->direction == 0) {
            head1->y -= BLOCK_SIZE;
        }
        if (head1->direction == 1) {
            head1->x += BLOCK_SIZE;
        }
        if (head1->direction == 2) {
            head1->y += BLOCK_SIZE;
        }
        if (head1->direction == 3) {
            head1->x -= BLOCK_SIZE;
        }


        //Gestion des collisions avec les bords de l'écran
        if (head1->x < 0 || head1->x >= SCREEN_WIDTH || head1->y < 0 || head1->y >= SCREEN_HEIGHT) {
            printf("Game Over ! Out of bounds !\n");
            game_over = 1;
        }
        
        //Gestion des collisions avec la nourriture en fonction de la taille d'un bloc
        /// (2 pts) Si la tête du serpent 1 est dans la zone de la nourriture, le score augmente de 1, un nouveau bloc est créé et la nourriture change de position
        if (head1->x <= food1->x + BLOCK_SIZE && food1->x <= head1->x + BLOCK_SIZE && head1->y <= food1->y + BLOCK_SIZE && food1->y <= head1->y + BLOCK_SIZE) {
            score1++;
            init_food(food1);
        }

        //Actualisation de l'écran
        rest(100);
    }


    //¤Fin du programme
    lib_memoire(head1, food1);
    allegro_exit();
    return 0;
}END_OF_MAIN()


    













