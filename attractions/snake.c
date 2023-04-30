
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

// Constantes pour la taille des blocs et de l'écran
#define BLOCK_SIZE 20
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Structure pour les blocs du serpent
typedef struct snake {
    int x, y;
    int direction;
    struct snake *next;
} snake;

// Structure pour la nourriture
typedef struct food {
    int x, y;
} food;

//Initialisation des serpents
void init_snake(snake *head, int x, int y) {
    head->x = x;
    head->y = y;
    head->direction = rand() % 4; //direction aléatoire
    head->next = NULL;
} 

//Affichage du serpent
void draw_snake(snake *head, int color) {
    snake *current_block = head;
    while (current_block != NULL) {
        rectfill(screen, current_block->x, current_block->y, current_block->x + BLOCK_SIZE, current_block->y + BLOCK_SIZE, color);
        current_block = current_block->next;
    }
}

int main(int argc, char *argv[]){
    //Initialisation de la seed pour les nombres aléatoires
    srand(time(NULL));
    //Initialisation d'Allegro
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_window_title("Snake");
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1200, 800, 0, 0) != 0) {
        allegro_message("GFX ERROR");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    //Initialisation des variables
    int game_over = 0;
    int score1 = 0;
    int color1 = makecol(255, 0, 0);

    //Initialisation du serpent 1 (ses caractéristiques sont dans la fonction init_snake : position, direction, prochain bloc)
    snake *head1;
    head1 = malloc(sizeof(snake));
    init_snake(head1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);  

    //Initialisation de la nourriture et de sa position (seule caractéristique)
    food *food1;
    food1 = malloc(sizeof(food));
    food1->x = rand() % (SCREEN_WIDTH / BLOCK_SIZE) * BLOCK_SIZE;
    food1->y = rand() % (SCREEN_HEIGHT / BLOCK_SIZE) * BLOCK_SIZE;

    //Boucle principale
    while(key != KEY_ESC && !game_over){
        //Effacement de l'écran (actualisation)
        clear_to_color(screen, makecol(0, 0, 0));

        //Affichage de la nourriture
        rectfill(screen, food1->x, food1->y, food1->x + BLOCK_SIZE, food1->y + BLOCK_SIZE, makecol(0, 255, 0));

        //Affichage du serpent 1
        draw_snake(head1, color1);

        //Affichage du score
        textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "Score : %d", score1);

        //Actualisation de l'écran
        vsync();

        //Déplacement du serpent 1
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
            game_over = 1;
        }

        //Gestion des collisions avec la nourriture
        if (head1->x == food1->x && head1->y == food1->y) {
            score1++;
            food1->x = rand() % (SCREEN_WIDTH / BLOCK_SIZE) * BLOCK_SIZE;
            food1->y = rand() % (SCREEN_HEIGHT / BLOCK_SIZE) * BLOCK_SIZE;
        }

        //Gestion des collisions avec le serpent 1
        snake *current_block = head1->next;
        while (current_block != NULL) {
            if (head1->x == current_block->x && head1->y == current_block->y) {
                game_over = 1;
            }
            current_block = current_block->next;
        }

        //C'est bon
        rest(100);
    }
    //Fermeture d'Allegro
    allegro_exit();
    return 0;
}END_OF_MAIN()


    













