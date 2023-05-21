//! Alfred de Vulpian - Groupe 13 - ECE Paris - 2023
//
//#     ____   _    _        _    ___ ____    ____  _____ ____     ____ _        _    ____ _____ ____
//#    |  _ \ / \  | |      / \  |_ _/ ___|  |  _ \| ____/ ___|   / ___| |      / \  / ___| ____/ ___|
//#   | |_) / _ \ | |     / _ \  | |\___ \  | | | |  _| \___ \  | |  _| |     / _ \| |   |  _| \___ \
//#  |  __/ ___ \| |___ / ___ \ | | ___) | | |_| | |___ ___) | | |_| | |___ / ___ \ |___| |___ ___) |
//# |_| /_/   \_\_____/_/   \_\___|____/  |____/|_____|____/   \____|_____/_/   \_\____|_____|____/


//? generation du labyrinthe (taille modulable) avec l'algorithme DFS (Depth First Search)
//? deplacement et collisions des joueurs

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <math.h>
#include "../header/palais_des_glaces.h"
#include "../header/loader.h"

#define SIZE 10
#define CELL_SIZE 800 / SIZE


typedef struct {
    int x;
    int y;
    int size;
    int previous_x;
    int previous_y;
    int speed;
    int direction;
    int id;
} Player;


typedef struct {
    int x;
    int y;
    int mur[4];
    int visite;
} Cell;


Cell *   creer_cellule(int x, int y);
Cell *** remplir_grille(Cell *** cell_grid);
Cell *   check_neighbours(Cell * cell, Cell *** cell_grid);
Player * initialiser_joueur();
void show_grid(Cell *** cell_grid, BITMAP * maze, BITMAP * buffer);
void free_grid(Cell *** cell_grid);
void check_collision(Player * player, BITMAP * maze);
void move_players(Player * player_1, Player * player_2);
void remove_wall(Cell * current_cell, Cell * chosen_neighbour);
void wait_to_quit();
int check_victory(Player * player_1, Player * player_2, time_t start_time, time_t end_time, BITMAP * buffer, SAMPLE * win_music, SAMPLE * music, int * temps);
void generer_labyrinthe(Cell *** cell_grid, Cell * current_cell, Cell ** stack, int stack_size, BITMAP * maze, BITMAP * buffer);
void show_start_menu_maze(BITMAP * buffer, BITMAP * titre);
void show_distance_to_finish(Player * player_1, Player * player_2, BITMAP * buffer);
int check_visited(Cell *** cell_grid);
void show_player(BITMAP * buffer, Player * player, BITMAP * anim_player_haut[4], BITMAP* anim_player_bas[4], BITMAP* anim_player_gauche[4], BITMAP* anim_player_droite[4],int frame_counter, int player_color);
int palais_des_glaces(int player_color1, int player_color2, BITMAP * anim_player_haut[4], BITMAP* anim_player_bas[4], BITMAP* anim_player_gauche[4], BITMAP* anim_player_droite[4]) {

    set_window_title("Palais des Glaces");

    srand(time(NULL));

    //* On initialise les joueurs
    Player * player_1 = initialiser_joueur();
    player_1->x = SCREEN_H - CELL_SIZE/2;
    player_1->y = SCREEN_H - CELL_SIZE/2 - player_1->size;
    player_1->id = 1;

    Player * player_2 = initialiser_joueur();
    player_2->x = SCREEN_H - CELL_SIZE/2 - player_1->size;
    player_2->y = SCREEN_H - CELL_SIZE/2;
    player_2->id = 2;

    //* On initialise les BITMAPS
    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * maze = create_bitmap(SCREEN_H, SCREEN_H);
    BITMAP * mask = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP * titre           = image_loader("attractions/assets/palais_des_glaces/maze_run.bmp");
    BITMAP * player_sprite_1 = image_loader("attractions/assets/palais_des_glaces/player_1.bmp");
    BITMAP * player_sprite_2 = image_loader("attractions/assets/palais_des_glaces/player_2.bmp");

    //* Charger la musique de fond
    SAMPLE * bcg_music = sound_loader("attractions/assets/palais_des_glaces/Bubble-Bobble.wav");
    SAMPLE * win_music = sound_loader("attractions/assets/palais_des_glaces/mario_victory.wav");

    // jouer la musique de fond
    play_sample(bcg_music, 255, 128, 1000, 1);

    // création du tableau de cellules (SIZE*SIZE)
    Cell *** cell_grid = malloc(sizeof(Cell**) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        cell_grid[i] = malloc(sizeof(Cell*) * SIZE);
    }
    cell_grid = remplir_grille(cell_grid);

    // initialisation de la premiere cellule
    Cell * current_cell = cell_grid[0][0];

    // création de la pile de cellules
    Cell ** stack = malloc(sizeof(Cell*) * SIZE * SIZE);
    int stack_size = 0;

    int frame_counter = 0;
    int winner = 0;


    time_t start_time, end_time;
    int temps;

    // génération du labyrinthe
    clear_to_color(screen, makecol(0, 0, 0));
    generer_labyrinthe(cell_grid, current_cell, stack, stack_size, maze, buffer);

    // on demarre le chrono
    time(&start_time);

    while (!key[KEY_ENTER]) {
        show_start_menu_maze(buffer, titre);
    }

    // main loop
    while (!key[KEY_ESC]) {
        clear(buffer);

        clear_to_color(mask, makecol(0, 0, 0));
        circlefill(mask, player_1->x + player_1->size/2, player_1->y + player_1->size/2, 65, makecol(255, 0, 255));
        circlefill(mask, player_2->x + player_2->size/2, player_2->y + player_2->size/2, 65, makecol(255, 0, 255));

        //* Départ en haut a gauche et arrivée en bas a droite
        rectfill(maze, 2, 2, CELL_SIZE - 2, CELL_SIZE - 2, makecol(100, 200, 100));
        rectfill(maze, SCREEN_H - CELL_SIZE + 2, SCREEN_H - CELL_SIZE + 2, SCREEN_H - 2, SCREEN_H - 2, makecol(100, 100, 200));

        frame_counter = (frame_counter + 1) % 4;
        (frame_counter == 0) ? frame_counter = 4 : frame_counter;

        //* Affichage du labyrinthe et des joueurs
        blit(maze, buffer, 0, 0, 0, 0, SCREEN_H, SCREEN_H);
        //masked_stretch_blit(player_sprite_1, buffer, 0, 0, player_sprite_1->w, player_sprite_1->h, player_1->x, player_1->y - 10, player_1->size, player_1->size + 10);
        //masked_stretch_blit(player_sprite_2, buffer, 0, 0, player_sprite_2->w, player_sprite_2->h, player_2->x, player_2->y - 10, player_2->size, player_2->size + 10);

        printf("on tente d'afficher le joueur 1\n");
        show_player(buffer, player_1, anim_player_haut, anim_player_bas, anim_player_gauche, anim_player_droite, frame_counter, player_color1);
        printf("on tente d'afficher le joueur 2\n");
        show_player(buffer, player_2, anim_player_haut, anim_player_bas, anim_player_gauche, anim_player_droite, frame_counter, player_color2);
        //* Collisions et mouvements
        check_collision(player_1, maze);
        check_collision(player_2, maze);
        move_players(player_1, player_2);


        //* Encore affichage
        masked_blit(mask, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rectfill(buffer, SCREEN_W * 2/3, 70, SCREEN_W, 70, makecol(255, 255, 255));
        rectfill(buffer, SCREEN_H, 0, SCREEN_H, SCREEN_H, makecol(255, 255, 255));
        winner = check_victory(player_1, player_2, start_time, end_time, buffer, win_music, bcg_music, &temps);
        masked_stretch_blit(titre, buffer, 0, 0, titre->w, titre->h, 810, 10, 380, 50);
        show_distance_to_finish(player_1, player_2, buffer);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    stop_sample(bcg_music);
    stop_sample(win_music);
    free_grid(cell_grid);
    destroy_sample(bcg_music);
    destroy_sample(win_music);
    return winner;
}

void show_grid(Cell *** cell_grid, BITMAP * maze, BITMAP * buffer) {

    // couleurs
    int wall_color = makecol(255, 255, 255);
    int cell_color = makecol(50, 50, 50);

    //* Afficher chaque cellule
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            //* Mur du haut
            if (cell_grid[i][j]->mur[0]) {
                rectfill(maze, i * CELL_SIZE - 1, j*CELL_SIZE - 1, i*CELL_SIZE+CELL_SIZE, j*CELL_SIZE + 1, wall_color);
            }
            else if (!cell_grid[i][j]->mur[0]) {
                rectfill(maze, i * CELL_SIZE + 2, j*CELL_SIZE - 1, i*CELL_SIZE+CELL_SIZE - 2, j*CELL_SIZE + 1, cell_color);
            }

            //* Mur de droite
            if (cell_grid[i][j]->mur[1]) {
                rectfill(maze, i*CELL_SIZE+CELL_SIZE - 1, j*CELL_SIZE - 1, i*CELL_SIZE+CELL_SIZE + 1, j*CELL_SIZE+CELL_SIZE, wall_color);
            }
            else if (!cell_grid[i][j]->mur[1]) {
                rectfill(maze, i*CELL_SIZE+CELL_SIZE - 1, j*CELL_SIZE + 2, i*CELL_SIZE+CELL_SIZE + 1, j*CELL_SIZE+CELL_SIZE, cell_color);
            }

            //* Mur du bas
            if (cell_grid[i][j]->mur[2]) {
                rectfill(maze, i*CELL_SIZE - 1, j*CELL_SIZE+CELL_SIZE - 1, i*CELL_SIZE+CELL_SIZE + 1, j*CELL_SIZE+CELL_SIZE + 1, wall_color);
            }
            else if (!cell_grid[i][j]->mur[2]) {
                rectfill(maze, i*CELL_SIZE  + 2, j*CELL_SIZE+CELL_SIZE - 1, i*CELL_SIZE+CELL_SIZE - 2, j*CELL_SIZE+CELL_SIZE + 1, cell_color);
            }

            //* Mur de gauche
            if (cell_grid[i][j]->mur[3]) {
                rectfill(maze, i*CELL_SIZE - 1, j*CELL_SIZE, i*CELL_SIZE + 1, j*CELL_SIZE+CELL_SIZE + 1, wall_color);
            }
            else if (!cell_grid[i][j]->mur[3]) {
                rectfill(maze, i*CELL_SIZE - 1, j*CELL_SIZE + 2, i*CELL_SIZE + 1, j*CELL_SIZE+CELL_SIZE - 2, cell_color);
            }
        }
    }
    blit(maze, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}


Cell * creer_cellule(int x, int y) {

    Cell * new_cell = malloc(sizeof(Cell));
    new_cell->x = x;
    new_cell->y = y;
    new_cell->mur[0] = 1;
    new_cell->mur[1] = 1;
    new_cell->mur[2] = 1;
    new_cell->mur[3] = 1;
    new_cell->visite = 0;

    return new_cell;
}


Player * initialiser_joueur() {

    Player * player = malloc(sizeof(Player));
    player->x = 5;
    player->y = 5;
    player->size = CELL_SIZE/3;
    player->previous_x = 0;
    player->previous_y = 0;
    player->speed = 3;
    player->direction = 1;

    return player;
}


Cell *** remplir_grille(Cell *** cell_grid) {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE ; j++) {
            Cell * new_cell = creer_cellule(j, i);
            cell_grid[i][j] = new_cell;
        }
    }
    return cell_grid;
}


void free_grid(Cell *** cell_grid) {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE ; j++) {
            free(cell_grid[i][j]);
        }
        free(cell_grid[i]);
    }
    free(cell_grid);
}


Cell * check_neighbours(Cell * cell, Cell *** cell_grid) {

    Cell * neighbours[4];
    int nb_neighbours = 0;

    int x = cell->x;
    int y = cell->y;

    //*  On récupère les voisins
    Cell * top    = (y > 0) ?      cell_grid[y - 1][x] : NULL;
    Cell * right  = (x < SIZE-1) ? cell_grid[y][x + 1] : NULL;
    Cell * bottom = (y < SIZE-1) ? cell_grid[y + 1][x] : NULL;
    Cell * left   = (x > 0) ?      cell_grid[y][x - 1] : NULL;

    //* On vérifie s'il y a des voisins non visités et on les ajoute à la liste
    if (top && !top->visite) {
        neighbours[nb_neighbours] = top;
        nb_neighbours++;
    }
    if (right && !right->visite) {
        neighbours[nb_neighbours] = right;
        nb_neighbours++;
    }
    if (bottom && !bottom->visite) {
        neighbours[nb_neighbours] = bottom;
        nb_neighbours++;
    }
    if (left && !left->visite) {
        neighbours[nb_neighbours] = left;
        nb_neighbours++;
    }

    //* S'il y a des voisins non visités
    if (nb_neighbours > 0) {

        //* On choisit un voisin au hasard
        int random = rand() % nb_neighbours;
        Cell * chosen_neighbour = neighbours[random];

        return chosen_neighbour;
    }

    return NULL;
}


int check_visited(Cell *** cell_grid) {

    //* On parcourt la grille, des qu'on trouve une cellule non visitée on retourne 0
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE ; j++) {
            if (cell_grid[i][j]->visite == 0) {
                return 0;
            }
        }
    }
    return 1;
}


void check_collision(Player * player, BITMAP * maze) {

    //* On récupère les coordonnées précédentes du joueur
    int x = player->previous_x;
    int y = player->previous_y;

    int wall = makecol(255, 255, 255);

    //* Collisions avec les murs
    for (int i = 0; i < player->size; i++) {
        if (getpixel(maze, player->x + i, player->y) == wall || getpixel(maze, player->x + i, player->y + player->size) == wall) {
            player->x = x;
            player->y = y;
        }
        else if (getpixel(maze, player->x, player->y + i) == wall || getpixel(maze, player->x + player->size, player->y + i) == wall) {
            player->x = x;
            player->y = y;
        }
        else {
            player->previous_x = player->x;
            player->previous_y = player->y;
        }
    }


    //* Collisions avec les bords de la map
    if (player->x < 0) {
        player->x = 0;
    }
    if (player->y < 0) {
        player->y = 0;
    }
    if (player->x > maze->w - player->size) {
        player->x = maze->w - player->size;
    }
    if (player->y > maze->h - player->size) {
        player->y = maze->h - player->size;
    }
}


void move_players(Player * player_1, Player * player_2) {

    //* Joueur 1
    if (key[KEY_UP]) {
        player_1->y -= player_1->speed;
        player_1->direction = 1;
    }
    if (key[KEY_DOWN]) {
        player_1->y += player_1->speed;
        player_1->direction = 2;
    }
    if (key[KEY_LEFT]) {
        player_1->x -= player_1->speed;
        player_1->direction = 3;
    }
    if (key[KEY_RIGHT]) {
        player_1->x += player_1->speed;
        player_1->direction = 4;
    }

    //* Joueur 2
    if (key[KEY_W]) {
        player_2->y -= player_2->speed;
        player_2->direction = 1;
    }
    if (key[KEY_S]) {
        player_2->y += player_2->speed;
        player_2->direction = 2;
    }
    if (key[KEY_A]) {
        player_2->x -= player_2->speed;
        player_2->direction = 3;
    }
    if (key[KEY_D]) {
        player_2->x += player_2->speed;
        player_2->direction = 4;
    }

}


void remove_wall(Cell * current_cell, Cell * chosen_neighbour) {

    //* On récupère la différence entre les coordonnées des deux cellules
    int x_diff = current_cell->x - chosen_neighbour->x;
    int y_diff = current_cell->y - chosen_neighbour->y;

    //* On supprime le mur entre les deux cellules en fonction de la différence
    if (x_diff == 1) {
        current_cell->mur[0] = 0;
        chosen_neighbour->mur[2] = 0;
    }

    else if (x_diff == -1) {
        current_cell->mur[2] = 0;
        chosen_neighbour->mur[0] = 0;
    }

    else if (y_diff == 1) {
        current_cell->mur[3] = 0;
        chosen_neighbour->mur[1] = 0;
    }

    else if (y_diff == -1) {
        current_cell->mur[1] = 0;
        chosen_neighbour->mur[3] = 0;
    }
}


void wait_to_quit() {

    //* On affiche un message pour quitter le jeu
    textprintf_ex(screen, font, 500, 430, makecol(255, 255, 255), -1, "PRESS ESC TO QUIT");
    while (!key[KEY_ESC]) {
        rest(1);
    }
}


int check_victory(Player * player_1, Player * player_2, time_t start_time, time_t end_time, BITMAP * buffer, SAMPLE * win_music, SAMPLE * music, int * temps) {

    //* Si un des joueurs arrive à la fin du labyrinthe, on affiche le temps qu'il a mis pour le finir
    if (player_1->x <= CELL_SIZE && player_1->y <= CELL_SIZE || player_2->x <= CELL_SIZE && player_2->y <= CELL_SIZE) {
        stop_sample(music);
        play_sample(win_music, 255, 128, 1000, 0);
        time(&end_time);
        clear_to_color(screen, makecol(0, 0, 0));

        if (player_1->x <= CELL_SIZE && player_1->y <= CELL_SIZE) {
            textprintf_ex(screen, font, 500, 400, makecol(255, 255, 255), -1, "PLAYER 1 WINS : %d s", *temps);
            return 1;
        }
        else {
            textprintf_ex(screen, font, 500, 400, makecol(255, 255, 255), -1, "PLAYER 2 WINS : %d s", *temps);
            return 2;
        }

        wait_to_quit();
    }

    //* Sinon on affiche le temps des deux joueurs
    else {
        time(&end_time);
        (*temps) = (int)difftime(end_time, start_time);
        textprintf_ex(buffer, font, 900, 200, makecol(255, 255, 255), -1, "TEMPS : %d s", *temps);
    }
    return 0;
}


void generer_labyrinthe(Cell *** cell_grid, Cell * current_cell, Cell ** stack, int stack_size, BITMAP * maze, BITMAP * buffer) {

    //* Génération du labyrinthe
    while (!check_visited(cell_grid)) {

        current_cell->visite = 1;
        Cell * next_cell = check_neighbours(current_cell, cell_grid);

        //* S'il ya un voisin pas visité
        if (next_cell) {

            next_cell->visite = 1;
            stack[stack_size] = current_cell;
            stack_size++;
            rectfill(maze, current_cell->y * CELL_SIZE + 2, current_cell->x * CELL_SIZE + 2, current_cell->y * CELL_SIZE + CELL_SIZE - 2, current_cell->x * CELL_SIZE + CELL_SIZE - 2, makecol(50, 50, 50));
            remove_wall(current_cell, next_cell);
            current_cell = next_cell;
            rectfill(maze, next_cell->y * CELL_SIZE + 2, next_cell->x * CELL_SIZE + 2, next_cell->y * CELL_SIZE + CELL_SIZE - 2, next_cell->x * CELL_SIZE + CELL_SIZE - 2, makecol(255, 0, 0));

        }

        //* sinon, on remonte dans la pile
        else if (stack_size > 0) {
            stack_size--;
            rectfill(maze, current_cell->y * CELL_SIZE + 2, current_cell->x * CELL_SIZE + 2, current_cell->y * CELL_SIZE + CELL_SIZE - 2, current_cell->x * CELL_SIZE + CELL_SIZE - 2, makecol(50, 50, 50));
            current_cell = stack[stack_size];
            rectfill(maze, current_cell->y * CELL_SIZE + 2, current_cell->x * CELL_SIZE + 2, current_cell->y * CELL_SIZE + CELL_SIZE - 2, current_cell->x * CELL_SIZE + CELL_SIZE - 2, makecol(255, 0, 0));
        }

        //* On affiche le labyrinthe
        show_grid(cell_grid, maze, buffer);
        rectfill(maze, current_cell->y * CELL_SIZE + 2, current_cell->x * CELL_SIZE + 2, current_cell->y * CELL_SIZE + CELL_SIZE - 2, current_cell->x * CELL_SIZE + CELL_SIZE - 2, makecol(50, 50, 50));
        rest(10);
    }
}


void show_start_menu_maze(BITMAP * buffer, BITMAP * titre) {

    clear_bitmap(buffer);
    masked_stretch_blit(titre, buffer, 0, 0, titre->w, titre->h, 300, SCREEN_H/2 - titre->h/2, 600, 100);
    textprintf_ex(buffer, font, SCREEN_W/2 - 100, SCREEN_H/2 + 50, makecol(255, 255, 255), -1, "PRESS ENTER TO START");
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}


void show_distance_to_finish(Player * player_1, Player * player_2, BITMAP * buffer) {

    int distance_1 = (int)sqrt(pow(player_1->x - CELL_SIZE, 2) + pow(player_1->y - CELL_SIZE, 2));
    int distance_2 = (int)sqrt(pow(player_2->x - CELL_SIZE, 2) + pow(player_2->y - CELL_SIZE, 2));

    textprintf_ex(buffer, font, 900, 100, makecol(255, 255, 255), -1, "Joueur 1 a %dm de la fin", distance_1);
    textprintf_ex(buffer, font, 900, 150, makecol(255, 255, 255), -1, "Joueur 2 a %dm de la fin", distance_2);
}


void show_player(BITMAP * buffer, Player * player, BITMAP * anim_player_haut[4], BITMAP* anim_player_bas[4], BITMAP* anim_player_gauche[4], BITMAP* anim_player_droite[4],int frame_counter, int player_color){
    // Select the appropriate animation array based on the direction
    BITMAP ** animation_array;

    if (player->direction == 1) {
        animation_array = anim_player_haut;
    }
    else if (player->direction == 2) {
        animation_array = anim_player_bas;
    }
    else if (player->direction == 3) {
        animation_array = anim_player_gauche;
    }
    else if (player->direction == 4) {
        animation_array = anim_player_droite;
    }
    else {
        // Invalid direction, do nothing
        return;
    }

    // Retrieve the current frame bitmap from the animation array
    BITMAP * current_frame;
    if (player->x != player->previous_x || player->y != player->previous_y) {
        current_frame = animation_array[frame_counter];
    }
    else {
        if (player->direction == 1 || player->direction == 2){
            current_frame = animation_array[1];
        }else{
            current_frame = animation_array[2];
        }
    }

    // Create a temporary bitmap for the masked sprite
    BITMAP* masked_sprite = create_bitmap(player->size, player->size + 10);

    // Apply the mask to the sprite
    clear(masked_sprite);
    stretch_blit(current_frame, masked_sprite, 0, 0, current_frame->w, current_frame->h, 0, 0, masked_sprite->w, masked_sprite->h);

    // Apply the color filter
    int filter = player_color;
    set_trans_blender(0, 0, 0, 255);
    draw_lit_sprite(masked_sprite, masked_sprite, 0, 0, filter);


    // Draw the masked sprite
    masked_blit(masked_sprite, buffer, 0, 0, player->x, player->y - 10, masked_sprite->w, masked_sprite->h);

    // Destroy the temporary bitmap
    destroy_bitmap(masked_sprite);
}