//! Code principal du projet d'algo du dexieme semestre

//? Objectif: Creer un jeu de parc d'attraction.
//?  - possibilité de se deplacer sur la carte du parc, qui servira aussi de menu.
//?  - systeme de tickets pour participer aux attractions.
//?  - systeme de sauvegarde du meilleur score de chaque attractions.
//?  - chaque membre de l'equipe doit programmer integrallement au moins une attraction.

//& 4 fichiers .h seront mis en place dans le dossier "attractions" pour accueilir les codes des 4 attractions (4 membres de l'equipe).
//& les fichiers .h seront inclus dans le main.c, dans lequel le code principal sera ecrit.

#include <stdio.h>
#include <string.h>
#include <Allegro.h>

#include "attractions/header/tag.h"
#include "attractions/header/geometry_dash.h"
#include "attractions/header/guitar_hero.h"
#include "attractions/header/palais_des_glaces.h"
#include "attractions/header/snake.h"
#include "attractions/header/loader.h"
#include "attractions/header/paris_hippiques.h"

#define PLAYER2_FILTER makecol(127, 0, 0)   // Red filter for player 2


// Structure Player qui contient les informations du joueur
typedef struct {
    int x, y;
    int number;
    int previous_x, previous_y;
    int direction, speed;
    int score, tickets;
    int leader;
    BITMAP * sprite;
} Player;

// fonction pour ecrire le meilleur score dans le fichier "meilleurs_scores.txt"
void write_best_score(int score) {

    // on ouvre le fichier "meilleurs_scores.txt" en mode ecriture
    FILE * file = fopen("saves\\meilleurs_scores.txt", "w");

    // si le fichier n'existe pas, on essaie avec un autre chemin (vscode et Clion)
    if (!file) {
        file = fopen("../saves/meilleurs_scores.txt", "w");

        if (!file) {
            allegro_message("FILE ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    int best_score;
    fscanf(file, "%d", &best_score);
    if (score > best_score) {
        fprintf(file, "%d\n", score);
    }
    else {
        fprintf(file, "%d\n", best_score);
    }
    fclose(file);
}


void afficher_regles(BITMAP* regles, BITMAP* buffer, const char* file_name) {
    masked_stretch_blit(regles, buffer, 0, 0, regles->w, regles->h, 0, 0, SCREEN_W, SCREEN_H);
    // Fetch rules from file and display them (location: attractions/assets/(game_name)/rules.txt)
    char filepath[200];
    snprintf(filepath, sizeof(filepath), "attractions/assets/%s/rules.txt", file_name);

    FILE* file = file_loader(filepath, "r");

    char line[100];
    int y = 250; // y position of the first line
    while (fgets(line, sizeof(line), file) != NULL) {
        //remove the ^ at the end of the line
        line[strlen(line) - 1] = '\0';
        textout_ex(buffer, font, line, 200, y, makecol(0, 0, 0), -1);
        y += 20;
    }

    fclose(file);
}


void show_ending_screen(BITMAP * buffer, BITMAP * ending_screen) {
    masked_stretch_blit(ending_screen, buffer, 0, 0, ending_screen->w, ending_screen->h, 0, 0, SCREEN_W, SCREEN_H);
    textout_ex(buffer, font, "Appuyez sur ECHAP pour quitter", 550, 600, makecol(0, 0, 0), -1);
    //blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    if (key[KEY_ESC]) {
        allegro_exit();
        exit(EXIT_SUCCESS);
    }
}


void check_collision_main(Player * player, Player * player_2, BITMAP * calque_collisions, BITMAP * player_sprite_1, SAMPLE * music_main, BITMAP * regles, BITMAP * buffer, BITMAP * ending_screen, BITMAP * anim_player_haut[4], BITMAP* anim_player_bas[4], BITMAP* anim_player_gauche[4], BITMAP* anim_player_droite[4]) {

    int active = 0;

    int x = player->previous_x;
    int y = player->previous_y;

    int ground = makecol(0, 255, 0);
    int wall   = makecol(255, 0, 0);

    int palais_des_glaces_color = makecol(30, 124, 184);// value in int : 0x1E7CB8
    int paris_hippiques_color   = makecol(127, 0, 127);
    int geometry_dash_color     = makecol(0, 0, 127);
    int guitar_hero_color       = makecol(127, 0, 0);
    int flappy_bird_color       = makecol(0, 255, 255);
    int tape_taupe_color        = makecol(255, 255, 0);
    int jackpot_color           = makecol(0, 127, 127);
    int sortie_color            = makecol(0, 0, 255);
    int snake_color             = makecol(0, 127, 0);
    int tag_color               = makecol(127, 127, 127);

    int color_array[12] = {ground, wall, palais_des_glaces_color, paris_hippiques_color, geometry_dash_color, tape_taupe_color, guitar_hero_color, jackpot_color, tag_color, snake_color , flappy_bird_color, sortie_color};

    for (int i = 0; i < 12; i++) {
        // on regarde la couleur des pixels aux 4 coins de la hitbox du joueur
        if (getpixel(calque_collisions, (player->x)*calque_collisions->w/SCREEN_W, (player->y + player_sprite_1->h/1.3)*calque_collisions->h/SCREEN_H) == color_array[i] || getpixel(calque_collisions, (player->x + player_sprite_1->w)*calque_collisions->w/SCREEN_W, (player->y + player_sprite_1->h/1.3)*calque_collisions->h/SCREEN_H) == color_array[i] || getpixel(calque_collisions, (player->x)*calque_collisions->w/SCREEN_W, (player->y + player_sprite_1->h)*calque_collisions->h/SCREEN_H) == color_array[i] || getpixel(calque_collisions, (player->x + player_sprite_1->w)*calque_collisions->w/SCREEN_W, (player->y + player_sprite_1->h)*calque_collisions->h/SCREEN_H) == color_array[i]) {

            //check the color
            const char* game;
            if (color_array[i] == palais_des_glaces_color) {
                game = "palais_des_glaces";
            }
            else if (color_array[i] == paris_hippiques_color) {
                game = "paris_hippiques";
            }
            else if (color_array[i] == geometry_dash_color) {
                game = "geometry_dash";
            }
            else if (color_array[i] == tape_taupe_color) {
                game = "tape_taupe";
            }
            else if (color_array[i] == guitar_hero_color) {
                game = "guitar_hero";
            }
            else if (color_array[i] == jackpot_color) {
                game = "jackpot";
            }
            else if (color_array[i] == tag_color) {
                game = "tag";
            }
            else if (color_array[i] == snake_color) {
                game = "snake";
            }
            else if (color_array[i] == flappy_bird_color) {
                game = "flappy_bird";
            }
            else if (color_array[i] == sortie_color) {
                show_ending_screen(buffer, ending_screen);
            }
            else {
                game = "none";
            }
            // si le joueur est sur une case mur, on le replace a sa position precedente
            active = 0;
            if (color_array[i] == wall) {
                player->x = x;
                player->y = y;
            }// si le joueur est sur un jeu, on lance l'attraction correspondante
            else if (color_array[i] != ground && color_array[i] != sortie_color && player->leader) {
                afficher_regles(regles, buffer, game);
                if (key[KEY_SPACE]) {
                    stop_sample(music_main);
                    if (strcmp(game, "palais_des_glaces") == 0) {
                        printf("palais_des_glaces\n");
                        palais_des_glaces(PLAYER2_FILTER, anim_player_haut, anim_player_bas, anim_player_gauche, anim_player_droite);
                    }
                    else if (strcmp(game, "paris_hippiques") == 0) {
                        printf("paris_hippiques\n");
                        paris_hippiques();
                    }
                    else if (strcmp(game, "geometry_dash") == 0) {
                        printf("geometry_dash\n");
                        geometry_dash();
                    }
                    else if (strcmp(game, "tape_taupe") == 0) {
                        printf("tape_taupe\n");
                    }
                    else if (strcmp(game, "guitar_hero") == 0) {
                        printf("guitar_hero\n");
                        guitar_hero();
                    }
                    else if (strcmp(game, "jackpot") == 0) {
                        printf("jackpot\n");
                    }
                    else if (strcmp(game, "tag") == 0) {
                        printf("tag\n");
                        tag(PLAYER2_FILTER, anim_player_haut, anim_player_bas, anim_player_gauche, anim_player_droite);
                    }
                    else if (strcmp(game, "snake") == 0) {
                        printf("snake\n");
                        snake();
                    }
                    else if (strcmp(game, "flappy_bird") == 0) {
                        printf("flappy_bird\n");
                    }

                    if (player->leader) {
                        player->leader = 0;
                        player_2->leader = 1;
                    }
                    else if (!player->leader) {
                        player->leader = 1;
                        player_2->leader = 0;
                    }

                    //replacer le joueur au milieu de la map et redéfinir la fenetre
                    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1200, 800, 0, 0);
                    play_sample(music_main, 255, 128, 1000, 1);
                    player->y = 300;
                    player->x = 300;
                }
            }
            player->previous_x = player->x;
            player->previous_y = player->y;
        }

        // collisions avec les bordures de la fenetre
        else if (player->x < 0)
            player->x = 0;
        else if (player->x > SCREEN_W - player_sprite_1->w)
            player->x = SCREEN_W - player_sprite_1->w;
        else if (player->y < 0)
            player->y = 0;
        else if (player->y > SCREEN_H - player_sprite_1->h)
            player->y = SCREEN_H - player_sprite_1->h;

        // actualisation de la position precedente
        else {
            player->previous_x = player->x;
            player->previous_y = player->y;
        }
    }
}


void afficher_score(BITMAP * score_image, BITMAP * buffer, Player player) {
    masked_stretch_blit(score_image, buffer, 0, 0, score_image->w, score_image->h, 0, 0, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer, font, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Score: %d", player.score);
}


void display_player(Player player, BITMAP* buffer, int frame_counter, BITMAP* anim_player_haut[4], BITMAP* anim_player_bas[4], BITMAP* anim_player_gauche[4], BITMAP* anim_player_droite[4]) {
    // Select the appropriate animation array based on the direction
    BITMAP ** animation_array;
    if (player.direction == 1) {
        animation_array = anim_player_haut;
    }
    else if (player.direction == 2) {
        animation_array = anim_player_bas;
    }
    else if (player.direction == 3) {
        animation_array = anim_player_gauche;
    }
    else if (player.direction == 4) {
        animation_array = anim_player_droite;
    }
    else {
        // Invalid direction, do nothing
        return;
    }

    // Retrieve the current frame bitmap from the animation array
    BITMAP * current_frame;
    if (player.x != player.previous_x || player.y != player.previous_y) {
        current_frame = animation_array[frame_counter];
    }
    else {
        if (player.direction == 1 || player.direction == 2){
            current_frame = animation_array[1];
        }else{
            current_frame = animation_array[2];
        }
    }

    // Create a temporary bitmap for the masked sprite
    BITMAP * masked_sprite = create_bitmap(current_frame->w, current_frame->h);

    // Apply the mask to the sprite
    clear(masked_sprite);
    blit(current_frame, masked_sprite, 0, 0, 0, 0, current_frame->w, current_frame->h);

    if (player.number == 2) {
        // Apply the color filter only for player 2
        int filter = PLAYER2_FILTER;
        set_trans_blender(0, 0, 0, 255);
        draw_lit_sprite(masked_sprite, masked_sprite, 0, 0, filter);
    }

    // Draw the masked sprite
    masked_blit(masked_sprite, buffer, 0, 0, player.x, player.y, masked_sprite->w, masked_sprite->h);

    // Destroy the temporary bitmap
    destroy_bitmap(masked_sprite);
}


void afficher_map(BITMAP * titre, BITMAP * buffer, BITMAP * map, BITMAP * player_sprite_1, BITMAP * player_sprite_2, Player player_1, Player player_2, int * can_move, BITMAP * score_image, BITMAP * calque_collisions, BITMAP * buffer_texte, int frame_counter, BITMAP * anim_player_haut[4], BITMAP * anim_player_bas[4], BITMAP * anim_player_gauche[4], BITMAP * anim_player_droite[4]) {

    clear_bitmap(buffer);
    clear_to_color(buffer_texte, makecol(255, 0, 255));
    stretch_blit(calque_collisions, buffer, 0, 0, calque_collisions->w, calque_collisions->h, 0, 0, buffer->w, buffer->h);
    stretch_blit(map, buffer, 0, 0, map->w, map->h, 0, 0, buffer->w, buffer->h);

    //Animation du joueur :
    display_player(player_1, buffer, frame_counter, anim_player_haut, anim_player_bas, anim_player_gauche, anim_player_droite);
    display_player(player_2, buffer, frame_counter, anim_player_haut, anim_player_bas, anim_player_gauche, anim_player_droite);

    masked_stretch_blit(titre, buffer, 0, 0, titre->w, titre->h, SCREEN_W/2 - titre->w/1.35, SCREEN_H/2 - titre->h*1.5, titre->w*1.5, titre->h*1.5);
    masked_blit(buffer_texte, buffer, 0, 0, 0, 0, buffer_texte->w, buffer_texte->h);

    // enlever le titre si la souris est clique
    if (key[KEY_SPACE] || mouse_b & 1) {
        clear_to_color(titre, makecol(255, 0, 255));
        *can_move = 1;
    }

    // afficher le score si le joueur est sur la case "score"
    if (940 < player_1.x && player_1.x < 1000 && 100 < player_1.y && player_1.y < 200 || 940 < player_2.x && player_2.x < 1000 && 100 < player_2.y && player_2.y < 200) {
        afficher_score(score_image, buffer_texte, player_1);
        afficher_score(score_image, buffer_texte, player_2);
    }
}


void move_player(Player * player, int UP, int DOWN, int LEFT, int RIGHT) {
    if (key[UP]) {
        player->y -= player->speed;
        player->direction = 1;
    }
    else if (key[DOWN]) {
        player->y += player->speed;
        player->direction = 2;
    }
    else if (key[LEFT]) {
        player->x -= player->speed;
        player->direction = 3;
    }
    else if (key[RIGHT]) {
        player->x += player->speed;
        player->direction = 4;
    }
}


//! fonction principale
int main() {

    //& initialisation de la fenetre, de la souris et du clavier
    allegro_init();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

    //Initialisation de la seed pour les nombres aléatoires
    srand(time(NULL));

    set_window_title("Projet Algo S2");
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1200, 800, 0, 0) != 0) {
        allegro_message("GFX ERROR");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    show_mouse(screen);

    //! VARIABLES
    int frame_counter = 0;
    int can_move      = 0;

    //! CHARGEMENT DES BITMAPS
    BITMAP * buffer_texte      = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * buffer            = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * calque_collisions = image_loader("attractions/assets/collision_v3.bmp");
    BITMAP * player_sprite_1   = image_loader("attractions/assets/palais_des_glaces/player_1.bmp");
    BITMAP * player_sprite_2   = image_loader("attractions/assets/palais_des_glaces/player_2.bmp");
    BITMAP * ending_screen     = image_loader("attractions/assets/ending_screen.bmp");
    BITMAP * score_image       = image_loader("attractions/assets/score.bmp");
    BITMAP * regles            = image_loader("attractions/assets/lancer_jeu.bmp");
    BITMAP * titre             = image_loader("attractions/assets/Titre.bmp");
    BITMAP * map               = image_loader("attractions/assets/map_v3.bmp");
    SAMPLE * music_main        = sound_loader("attractions/assets/music_main.wav");

    //! Chargement des animations
    // Load the bitmaps in separate arrays
    BITMAP * anim_player_gauche[4];
    BITMAP * anim_player_droite[4];
    BITMAP * anim_player_haut[4];
    BITMAP * anim_player_bas[4];

    // Load the bitmaps in the arrays
    for (int i = 1; i < 5; i++) {
        // Construct the file paths using sprintf
        char file_path[100];
        sprintf(file_path, "attractions/assets/anim_player_haut/frame_%d.bmp", i);
        anim_player_haut[i] = image_loader(file_path);

        sprintf(file_path, "attractions/assets/anim_player_bas/frame_%d.bmp", i);
        anim_player_bas[i] = image_loader(file_path);

        sprintf(file_path, "attractions/assets/anim_player_gauche/frame_%d.bmp", i);
        anim_player_gauche[i] = image_loader(file_path);

        sprintf(file_path, "attractions/assets/anim_player_droite/frame_%d.bmp", i);
        anim_player_droite[i] = image_loader(file_path);
    }


    //& reste du code principal

    Player player_1;
    player_1.sprite = player_sprite_1;
    player_1.number = 1;
    player_1.x = 520;
    player_1.y = 150;
    player_1.previous_x = player_1.x;
    player_1.previous_y = player_1.y;
    player_1.speed = 5;
    player_1.leader = 1;
    player_1.direction = 2; //player facing down first

    Player player_2;
    player_2.sprite = player_sprite_2;
    player_2.number = 2;
    player_2.x = 590;
    player_2.y = 150;
    player_2.previous_x = player_2.x;
    player_2.previous_y = player_2.y;
    player_2.speed = 5;
    player_2.leader = 0;
    player_2.direction = 2; //player facing down first

    //Musique du menu
    play_sample(music_main, 255, 128, 1000, 1);

    //& boucle principale du menu (carte du parc)
    while (!key[KEY_M]) {

        afficher_map(titre, buffer, map, player_sprite_1, player_sprite_2, player_1, player_2, &can_move, score_image, calque_collisions, buffer, frame_counter, anim_player_haut, anim_player_bas, anim_player_gauche, anim_player_droite);
        check_collision_main(&player_2, &player_1, calque_collisions, player_sprite_2, music_main, regles, buffer, ending_screen, anim_player_haut, anim_player_bas, anim_player_gauche, anim_player_droite);
        check_collision_main(&player_1, &player_2, calque_collisions, player_sprite_1, music_main, regles, buffer, ending_screen, anim_player_haut, anim_player_bas, anim_player_gauche, anim_player_droite);

        // afficher le leader
        if (player_1.leader)
            textprintf_ex(buffer, font, 10, 10, makecol(0, 0, 0), -1, "Joueur 1 leader");
        if (player_2.leader)
            textprintf_ex(buffer, font, 10, 10, makecol(0, 0, 0), -1, "Joueur 2 leader");


        if (can_move) {
            move_player(&player_1, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT);
            move_player(&player_2, KEY_W, KEY_S, KEY_A, KEY_D);
        }


        // passer a la frame suivante de l'animation du joueur (4 frames)
        frame_counter = (frame_counter + 1) % 4;
        (frame_counter == 0) ? frame_counter += 4 : frame_counter;

        vsync();
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    }

    readkey();
    allegro_exit();
    return 0;
}END_OF_MAIN();