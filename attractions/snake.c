
/*
 ! By Léon DALLE - ECE ING1 - TD13                                                                                                                      
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

//*Fonctions d'initialisation appeléesa
void init_allegro(){ //¤Initialisation des serpents (direction aléatoire)
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
    
void init_snake(snake *head, int x, int y) { //¤Initialisation de la nourriture (position aléatoire)
    head->x = x;
    head->y = y;
    head->direction = rand() % 4; //direction aléatoire
    head->previous_pos_x = x;
    head->previous_pos_y = y;
    head->is_head = true;
    head->next = NULL;
} 
    
void init_food(food *food) { //¤Affichage du serpent à partir de la tête
    food->x = rand() % (SCREEN_WIDTH - BLOCK_SIZE);
    food->y = rand() % (SCREEN_HEIGHT - BLOCK_SIZE);
}
    
void draw_snake(snake *head, int color) { //¤Fonction pour libérer la mémoire
    snake *current_block = head;
    while (current_block != NULL) {
        rectfill(screen, current_block->x, current_block->y, current_block->x + BLOCK_SIZE, current_block->y + BLOCK_SIZE, color);
        current_block = current_block->next;
    }
}
    
void lib_memoire(snake *head, food *food) { //¤Fonction pour libérer la mémoire
    snake *current_block = head;
    snake *next_block = head->next;
    while (current_block != NULL) {
        next_block = current_block->next;
        free(current_block);
        current_block = next_block;
    }
    free(food);
}

//!Fonctions relatives au serpent et appelées souvent
void add_block(snake *head) { //¤ On ajoute un bloc au serpent
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

void move_snake(snake *head){ //¤ On bouge tout le serpent
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
    int game_over = 0;
    //vérifier si le serpent sort de l'écran
    if (head1->x < 0 || head1->x >= SCREEN_WIDTH || head1->y < 0 || head1->y >= SCREEN_HEIGHT) {
        printf("Game Over ! Le serpent 1 a perdu !\n");
        game_over = 1;
    }
    if (head2->x < 0 || head2->x >= SCREEN_WIDTH || head2->y < 0 || head2->y >= SCREEN_HEIGHT) {
        printf("Game Over ! Le serpent 2 a perdu !\n");
        game_over = 1;
    }

    //vérifier si le serpent se mord la queue
    //Gestion des collisions avec le serpent
    snake *current_block = head1->next;
    while (current_block != NULL) {
        if (head1->x == current_block->x && head1->y == current_block->y) {
            printf("Game Over ! first player ate himself !\n");
            game_over = 1;
        }
        current_block = current_block->next;
    }

    current_block = head2->next;
    while (current_block != NULL) {
        if (head2->x == current_block->x && head2->y == current_block->y) {
            printf("Game Over ! second player ate himself !\n");
            game_over = 1;
        }
        current_block = current_block->next;
    }

    //collisions entre les deux serpents : si la tête du serpent 1 touche le corps du serpent 2 ou inversement
    current_block = head2;
    while (current_block != NULL) {
        if (head1->x == current_block->x && head1->y == current_block->y) {
            printf("Game Over ! first player ate second player !\n");
            game_over = 1;
        }
        current_block = current_block->next;
    }

    current_block = head1;
    while (current_block != NULL) {
        if (head2->x == current_block->x && head2->y == current_block->y) {
            printf("Game Over ! second player ate first player !\n");
            game_over = 1;
        }
        current_block = current_block->next;
    }

    return game_over;
}

int collision_food(snake *head, food *food) { //¤ On vérifie si le serpent mange la nourriture
    if (head->x <= food->x + BLOCK_SIZE && food->x <= head->x + BLOCK_SIZE && head->y <= food->y + BLOCK_SIZE && food->y <= head->y + BLOCK_SIZE) {
        init_food(food);
        return true;
    }
}



int main(int argc, char *argv[]){
    init_allegro();
    //?Initialisation des variables 
    int game_over = 0;
    int score1 = 0;
    int score2 = 0;
    //serpent1 en rouge et serpent2 en bleu
    int color1 = makecol(255, 0, 0);
    int color2 = makecol(0, 0, 255);

    //?Initialisation du serpent 1 (ses caractéristiques sont dans la fonction init_snake : position, direction, prochain bloc et si c'est la tête) et la nourriture et de sa position (seule caractéristique)
    snake *head1 = malloc(sizeof(snake));
    snake *head2 = malloc(sizeof(snake));
    init_snake(head1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    init_snake(head2, SCREEN_WIDTH / 3, SCREEN_HEIGHT /3);
    food *food1 = malloc(sizeof(food));
    food *food2 = malloc(sizeof(food));
    init_food(food1);
    init_food(food2);


    //Boucle principale
    while(!key[KEY_ESC] && !game_over){
        //Effacement de l'écran (actualisation) et de affichage de la nourriture et du score
        clear_to_color(screen, makecol(0, 0, 0));
        textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "Score : %d", score1);
        rectfill(screen, food1->x, food1->y, food1->x + BLOCK_SIZE, food1->y + BLOCK_SIZE, makecol(0, 255, 0));
        draw_snake(head1, color1);
        draw_snake(head2, color2);

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

        if (key[KEY_W] && head2->direction != 2) {
            head2->direction = 0;
        }
        if (key[KEY_D] && head2->direction != 3) {
            head2->direction = 1;
        }
        if (key[KEY_S] && head2->direction != 0) {
            head2->direction = 2;
        }
        if (key[KEY_A] && head2->direction != 1) {
            head2->direction = 3;
        }

        //Déplacement du serpent 1
        move_snake(head1);
        move_snake(head2);

        //Gestion des collisions : si le serpent sort de l'écran, si le serpent se touche lui-même ou si la tête du serpent touche le corps du serpent
        if (collision_mort(head1, head2)) {
            game_over = 1;
        }

        //Gestion des collisions avec la nourriture
        if (!collision_food(head1, food1) || !collision_food(head1, food2)){
            score1++;
            add_block(head1);
        }
        if (!collision_food(head2, food1) || !collision_food(head2, food2)){
            score2++;
            add_block(head2);
        }

        //Actualisation de l'écran
        rest(100);
    }


    //¤Fin du programme
    lib_memoire(head1, food1);
    allegro_exit();
    return 0;
}END_OF_MAIN()


    













