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

#define SIZE 10
#define CELL_SIZE 800 / SIZE


typedef struct {
    int x;
    int y;
    int size;
    int previous_x;
    int previous_y;
    int speed;
} Player;


typedef struct {
    int x;
    int y;
    int mur[4];
    int visite;
} Cell;


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

    //* Joueur 2
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


void init() {

    allegro_init();
    install_mouse();
    install_keyboard();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    install_timer();
    set_window_title("MAZE RUN");

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1200, 800, 0, 0) != 0) {
        allegro_message("GFX ERROR");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}


void wait_to_quit() {

    //* On affiche un message pour quitter le jeu
    textprintf_ex(screen, font, 500, 430, makecol(255, 255, 255), -1, "PRESS ESC TO QUIT");
    while (!key[KEY_ESC]) {
        rest(1);
    }
    allegro_exit();
    exit(EXIT_SUCCESS);
}


void check_victory(Player * player_1, Player * player_2, time_t start_time, time_t end_time, BITMAP * buffer, SAMPLE * win_music, SAMPLE * music, int * temps) {

    //* Si un des joueurs arrive à la fin du labyrinthe, on affiche le temps qu'il a mis pour le finir
    if (player_1->x <= CELL_SIZE && player_1->y <= CELL_SIZE || player_2->x <= CELL_SIZE && player_2->y <= CELL_SIZE) {
        stop_sample(music);
        play_sample(win_music, 255, 128, 1000, 0);
        time(&end_time);
        clear_to_color(screen, makecol(0, 0, 0));

        if (player_1->x <= CELL_SIZE && player_1->y <= CELL_SIZE) {
            textprintf_ex(screen, font, 500, 400, makecol(255, 255, 255), -1, "PLAYER 1 WINS : %d s", *temps);
        }
        else {
            textprintf_ex(screen, font, 500, 400, makecol(255, 255, 255), -1, "PLAYER 2 WINS : %d s", *temps);
        }

        wait_to_quit();
        allegro_exit();
        exit(EXIT_SUCCESS);
    }

    //* Sinon on affiche le temps des deux joueurs
    else {
        time(&end_time);
        (*temps) = (int)difftime(end_time, start_time);
        textprintf_ex(buffer, font, 900, 200, makecol(255, 255, 255), -1, "TEMPS : %d s", *temps);
    }
}


void generer_labirynthe(Cell *** cell_grid, Cell * current_cell, Cell ** stack, int stack_size, BITMAP * maze, BITMAP * buffer) {

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


void show_start_menu(BITMAP * buffer, BITMAP * titre) {

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


int main() {

    init();

    srand(time(NULL));

    //* On initialise les joueurs
    Player * player_1 = initialiser_joueur();
    player_1->x = SCREEN_H - CELL_SIZE/2;
    player_1->y = SCREEN_H - CELL_SIZE/2 - player_1->size;

    Player * player_2 = initialiser_joueur();
    player_2->x = SCREEN_H - CELL_SIZE/2 - player_1->size;
    player_2->y = SCREEN_H - CELL_SIZE/2;

    //* On initialise les BITMAPS
    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * maze = create_bitmap(SCREEN_H, SCREEN_H);
    BITMAP * mask = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * titre = load_bitmap("../assets/palais_des_glaces/maze_run.bmp", NULL);

    BITMAP * player_sprite_1 = load_bitmap("../assets/palais_des_glaces/player_1.bmp", NULL);
    BITMAP * player_sprite_2 = load_bitmap("../assets/palais_des_glaces/player_2.bmp", NULL);

    //* On vérifie que les bitmaps ont bien été initialisés
    if (!titre || !player_sprite_1 || !player_sprite_2) {

        titre = load_bitmap("assets\\palais_des_glaces\\maze_run.bmp", NULL);
        player_sprite_1 = load_bitmap("assets\\palais_des_glaces\\player_1.bmp", NULL);
        player_sprite_2 = load_bitmap("assets\\palais_des_glaces\\player_2.bmp", NULL);

        if (!titre || !player_sprite_1 || !player_sprite_2) {

            allegro_message("BITMAP ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    //* Charger la musique de fond
    SAMPLE * bcg_music = load_sample("../sounds/Bubble-Bobble.wav");
    SAMPLE * win_music = load_sample("../sounds/mario_victory.wav");

    // *Vérifier que la musique a bien été chargée
    if (!bcg_music || !win_music) {
        bcg_music = load_sample("sounds\\Bubble-Bobble.wav");
        win_music = load_sample("sounds\\mario_victory.wav");
        if (!bcg_music) {
            allegro_message("SAMPLE ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

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


    time_t start_time, end_time;
    int temps;

    // génération du labyrinthe
    generer_labirynthe(cell_grid, current_cell, stack, stack_size, maze, buffer);

    // on demarre le chrono
    time(&start_time);

    while (!key[KEY_ENTER]) {
        show_start_menu(buffer, titre);
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

        //* Affichage du labyrinthe et des joueurs
        blit(maze, buffer, 0, 0, 0, 0, SCREEN_H, SCREEN_H);
        masked_stretch_blit(player_sprite_1, buffer, 0, 0, player_sprite_1->w, player_sprite_1->h, player_1->x, player_1->y - 10, player_1->size, player_1->size + 10);
        masked_stretch_blit(player_sprite_2, buffer, 0, 0, player_sprite_2->w, player_sprite_2->h, player_2->x, player_2->y - 10, player_2->size, player_2->size + 10);

        //* Collisions et mouvements
        check_collision(player_1, maze);
        check_collision(player_2, maze);
        move_players(player_1, player_2);


        //* Encore affichage
        masked_blit(mask, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rectfill(buffer, SCREEN_W * 2/3, 70, SCREEN_W, 70, makecol(255, 255, 255));
        rectfill(buffer, SCREEN_H, 0, SCREEN_H, SCREEN_H, makecol(255, 255, 255));
        check_victory(player_1, player_2, start_time, end_time, buffer, win_music, bcg_music, &temps);
        masked_stretch_blit(titre, buffer, 0, 0, titre->w, titre->h, 810, 10, 380, 50);
        show_distance_to_finish(player_1, player_2, buffer);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    free_grid(cell_grid);
    return 0;
}END_OF_MAIN();