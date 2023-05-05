//! Alfred de Vulpian - Groupe 13 - ECE Paris - 2023

//* Programme du jeu de course dans un labyrinthe (palais des glaces) avec 2 joueurs

//? generation du labyrinthe (taille modulable) avec l'algorithme DFS (Depth First Search)
//? deplacement et collisions des joueurs

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>

#define SIZE 10
#define CELL_SIZE 800 / SIZE


typedef struct {
    int x;
    int y;
    int size;
    int previous_x;
    int previous_y;
    int speed;
    int temps;
} Player;


typedef struct {
    int x;
    int y;
    int mur[4];
    int visite;
} Cell;


// fonction pour afficher la grille
void show_grid(Cell *** cell_grid, BITMAP * maze, BITMAP * buffer) {

    // couleurs
    int wall_color = makecol(255, 255, 255);
    int cell_color = makecol(0, 0, 0);

    // afficher les murs et les cases
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            // mur du haut
            if (cell_grid[i][j]->mur[0]) {
                rectfill(maze, i * CELL_SIZE - 1, j*CELL_SIZE - 1, i*CELL_SIZE+CELL_SIZE, j*CELL_SIZE + 1, wall_color);
            }
            else if (!cell_grid[i][j]->mur[0]) {
                rectfill(maze, i * CELL_SIZE + 2, j*CELL_SIZE - 1, i*CELL_SIZE+CELL_SIZE - 2, j*CELL_SIZE + 1, cell_color);
            }

            // mur de droite
            if (cell_grid[i][j]->mur[1]) {
                rectfill(maze, i*CELL_SIZE+CELL_SIZE - 1, j*CELL_SIZE - 1, i*CELL_SIZE+CELL_SIZE + 1, j*CELL_SIZE+CELL_SIZE, wall_color);
            }
            else if (!cell_grid[i][j]->mur[1]) {
                rectfill(maze, i*CELL_SIZE+CELL_SIZE - 1, j*CELL_SIZE + 2, i*CELL_SIZE+CELL_SIZE + 1, j*CELL_SIZE+CELL_SIZE, cell_color);
            }

            // mur du bas
            if (cell_grid[i][j]->mur[2]) {
                rectfill(maze, i*CELL_SIZE - 1, j*CELL_SIZE+CELL_SIZE - 1, i*CELL_SIZE+CELL_SIZE + 1, j*CELL_SIZE+CELL_SIZE + 1, wall_color);
            }
            else if (!cell_grid[i][j]->mur[2]) {
                rectfill(maze, i*CELL_SIZE  + 2, j*CELL_SIZE+CELL_SIZE - 1, i*CELL_SIZE+CELL_SIZE - 2, j*CELL_SIZE+CELL_SIZE + 1, cell_color);
            }

            // mur de gauche
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


// fonction pour creer une cellule
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


// fonction pour remplir la grille de cellules
Cell *** remplir_grille(Cell *** cell_grid) {

    // pour chaque cellule de la grille, on en crée une
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE ; j++) {
            Cell * new_cell = creer_cellule(j, i);
            cell_grid[i][j] = new_cell;
        }
    }
    return cell_grid;
}


// fonction pour liberer la grille de cellules et les cellules
void free_grid(Cell *** cell_grid) {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE ; j++) {
            free(cell_grid[i][j]);
        }
        free(cell_grid[i]);
    }
    free(cell_grid);
}


// fonction pour regarder  les voisins d'une cellule et retourner un voisin aléatoire
Cell * check_neighbours(Cell * cell, Cell *** cell_grid) {

    // liste des voisins potentiels non visités
    Cell * neighbours[4];
    int nb_neighbours = 0;

    // on récupère les coordonnées de la cellule
    int x = cell->x;
    int y = cell->y;

    // on récupère les voisins
    Cell * top    = (y > 0) ?      cell_grid[y - 1][x] : NULL;
    Cell * right  = (x < SIZE-1) ? cell_grid[y][x + 1] : NULL;
    Cell * bottom = (y < SIZE-1) ? cell_grid[y + 1][x] : NULL;
    Cell * left   = (x > 0) ?      cell_grid[y][x - 1] : NULL;

    // on vérifie si les voisins existent et non visités pour les ajouter a la liste
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

    // si il y a des voisins non visités
    if (nb_neighbours > 0) {

        // on choisit un voisin au hasard
        int random = rand() % nb_neighbours;
        Cell * chosen_neighbour = neighbours[random];

        // on retourne le voisin
        return chosen_neighbour;
    }

    // sinon on retourne NULL
    return NULL;
}


// fonction pour vérifier si toutes les cellules ont été visitées
int check_visited(Cell *** cell_grid) {

    // on parcourt la grille, des qu'on trouve une cellule non visitée on retourne 0
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE ; j++) {
            if (cell_grid[i][j]->visite == 0) {
                return 0;
            }
        }
    }
    // sinon on retourne 1
    return 1;
}


// fonction pour créer un joueur
Player * initialiser_joueur() {

    Player * player = malloc(sizeof(Player));
    player->x = 5;
    player->y = 5;
    player->size = CELL_SIZE/3;
    player->previous_x = 0;
    player->previous_y = 0;
    player->speed = 3;

    return player;
}


// fonction qui gere les collisions de la map
void check_collision(Player * player, BITMAP * maze) {

    // on récupère les coordonnées précédentes du joueur
    int x = player->previous_x;
    int y = player->previous_y;

    // couleur des murs
    int wall = makecol(255, 255, 255);

    // collisions avec les murs
    if (getpixel(maze, player->x, player->y) == wall || getpixel(maze, player->x + player->size, player->y) == wall || getpixel(maze, player->x, player->y + player->size) == wall || getpixel(maze, player->x + player->size, player->y + player->size) == wall) {
        player->x = x;
        player->y = y;
    }
    else {
        player->previous_x = player->x;
        player->previous_y = player->y;
    }

    // collisions avec les bords de la map
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


// fonction pour déplacer les joueurs
void move_players(Player * player_1, Player * player_2) {

    if (key[KEY_UP]) {
        player_1->y -= player_1->speed;
    }
    if (key[KEY_DOWN]) {
        player_1->y += player_1->speed;
    }
    if (key[KEY_LEFT]) {
        player_1->x -= player_1->speed;
    }
    if (key[KEY_RIGHT]) {
        player_1->x += player_1->speed;
    }

    if (key[KEY_W]) {
        player_2->y -= player_2->speed;
    }
    if (key[KEY_S]) {
        player_2->y += player_2->speed;
    }
    if (key[KEY_A]) {
        player_2->x -= player_2->speed;
    }
    if (key[KEY_D]) {
        player_2->x += player_2->speed;
    }

}


// fonction pour supprimer le mur entre deux cellules
void remove_wall(Cell * current_cell, Cell * chosen_neighbour) {

    // on récupère la différence entre les coordonnées des deux cellules
    int x_diff = current_cell->x - chosen_neighbour->x;
    int y_diff = current_cell->y - chosen_neighbour->y;

    // on supprime le mur entre les deux cellules
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


int main() {

    allegro_init();
    install_mouse();
    install_keyboard();
    install_timer();
    set_window_title("MAZE RUN");

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1200, 800, 0, 0) != 0) {
        allegro_message("GFX ERROR");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    // on initialise les joueurs
    Player * player_1 = initialiser_joueur();
    player_1->x = CELL_SIZE/2;
    player_1->y = CELL_SIZE/2 - player_1->size;

    Player * player_2 = initialiser_joueur();
    player_2->x = CELL_SIZE/2 - player_1->size;
    player_2->y = CELL_SIZE/2;

    // on initialise les BITMAPS
    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * maze = create_bitmap(SCREEN_H, SCREEN_H);
    BITMAP * titre = load_bitmap("../assets/palais_des_glaces/maze_run.bmp", NULL);
    BITMAP * player_sprite_1 = create_bitmap(player_1->size, player_1->size);
    BITMAP * player_sprite_2 = create_bitmap(player_2->size, player_2->size);
    rectfill(player_sprite_1, 0, 0, player_1->size, player_1->size, makecol(255, 0, 0));
    rectfill(player_sprite_2, 0, 0, player_2->size, player_2->size, makecol(0, 0, 255));

    // on vérifie que les BITMAPS ont bien été initialisés
    if (!titre) {
        titre = load_bitmap("assets\\palais_des_glaces\\maze_run.bmp", NULL);
        if (!titre) {
            allegro_message("BITMAP ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

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

    // main loop
    while (!check_visited(cell_grid)) {

        current_cell->visite = 1;
        Cell * next_cell = check_neighbours(current_cell, cell_grid);
        if (next_cell) {
            next_cell->visite = 1;
            // afficher la cellule courante en rouge en inversant x et y
            stack[stack_size] = current_cell;
            stack_size++;
            rectfill(maze, current_cell->y * CELL_SIZE + 2, current_cell->x * CELL_SIZE + 2, current_cell->y * CELL_SIZE + CELL_SIZE - 2, current_cell->x * CELL_SIZE + CELL_SIZE - 2, makecol(0, 0, 0));
            remove_wall(current_cell, next_cell);
            current_cell = next_cell;
            rectfill(maze, next_cell->y * CELL_SIZE + 2, next_cell->x * CELL_SIZE + 2, next_cell->y * CELL_SIZE + CELL_SIZE - 2, next_cell->x * CELL_SIZE + CELL_SIZE - 2, makecol(255, 0, 0));

        }
        else if (stack_size > 0) {
            stack_size--;
            rectfill(maze, current_cell->y * CELL_SIZE + 2, current_cell->x * CELL_SIZE + 2, current_cell->y * CELL_SIZE + CELL_SIZE - 2, current_cell->x * CELL_SIZE + CELL_SIZE - 2, makecol(0, 0, 0));
            current_cell = stack[stack_size];
            rectfill(maze, current_cell->y * CELL_SIZE + 2, current_cell->x * CELL_SIZE + 2, current_cell->y * CELL_SIZE + CELL_SIZE - 2, current_cell->x * CELL_SIZE + CELL_SIZE - 2, makecol(255, 0, 0));
        }
        show_grid(cell_grid, maze, buffer);
        rectfill(maze, current_cell->y * CELL_SIZE + 2, current_cell->x * CELL_SIZE + 2, current_cell->y * CELL_SIZE + CELL_SIZE - 2, current_cell->x * CELL_SIZE + CELL_SIZE - 2, makecol(0, 0, 0));
        rest(10);
    }

    while (!key[KEY_ESC]) {
        clear(buffer);

        // départ en haut a gauche et arrivée en bas a droite
        rectfill(maze, 2, 2, CELL_SIZE - 2, CELL_SIZE - 2, makecol(100, 200, 100));
        rectfill(maze, SCREEN_H - CELL_SIZE + 2, SCREEN_H - CELL_SIZE + 2, SCREEN_H - 2, SCREEN_H - 2, makecol(100, 100, 200));

        blit(maze, buffer, 0, 0, 0, 0, SCREEN_H, SCREEN_H);
        blit(player_sprite_1, buffer, 0, 0, player_1->x, player_1->y, player_1->size, player_1->size);
        blit(player_sprite_2, buffer, 0, 0, player_2->x, player_2->y, player_2->size, player_2->size);

        // collisions et mouvements
        check_collision(player_1, maze);
        check_collision(player_2, maze);
        move_players(player_1, player_2);

        // encore affichage
        masked_stretch_blit(titre, buffer, 0, 0, titre->w, titre->h, 810, 10, 380, 50);
        rectfill(buffer, SCREEN_W*2/3, 70, SCREEN_W, 70, makecol(255, 255, 255));
        rectfill(buffer, SCREEN_H, 0, SCREEN_H, SCREEN_H, makecol(255, 255, 255));
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    free_grid(cell_grid);
    return 0;
}END_OF_MAIN();