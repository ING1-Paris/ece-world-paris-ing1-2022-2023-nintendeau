//! Alfred de Vulpian - Groupe 13 - ECE Paris - 2023

//#   ________________  __  _____________________  __   ____  ___   _____ __  __
//#  / ____/ ____/ __ \/  |/  / ____/_  __/ __ \ \/ /  / __ \/   | / ___// / / /
//# / / __/ __/ / / / / /|_/ / __/   / / / /_/ /\  /  / / / / /| | \__ \/ /_/ /
//#/ /_/ / /___/ /_/ / /  / / /___  / / / _, _/ / /  / /_/ / ___ |___/ / __  /
//#\____/_____/\____/_/  /_/_____/ /_/ /_/ |_| /_/  /_____/_/  |_/____/_/ /_/


#include <stdio.h>
#include <allegro.h>
#include <stdbool.h>
#include <time.h>
#include "../header/geometry_dash.h"
#include "../header/loader.h"

#define NB_BACKGROUNDS 2
#define BCG_SPEED 10
#define JUMP_SPEED 17


typedef struct Player {

    int x;
    int y;
    int jump_speed;
    int time;
    bool life;
} Player;


typedef struct {

    int x;
    int y;
} Background;


Player * creer_player();
void jump_and_collide(Player * player, BITMAP * buffer, BITMAP * sprite, BITMAP * level_collisions, int key_jump, SAMPLE * death_sound);
void move_player_to_default(Player * player, int frame_counter);
void show_background(BITMAP * buffer, BITMAP * level, Background bg[NB_BACKGROUNDS], int largeur);
void move_bcg(int compteur_frames, Background bg[NB_BACKGROUNDS], int largeur);
void show_game_over(BITMAP * buffer, BITMAP * game_over_text, int winner, double time_spent);
void show_start_menu_geometry_dash(BITMAP * level, BITMAP * buffer, BITMAP * title, int largeur);
void write_best_score(float * scores, char * game);


int geometry_dash(float scores[2]) {

    set_window_title("Geometry Dash");

    //* charger les fichiers nécessaires
    BITMAP * player_sprite    = image_loader("attractions/assets/geometry_dash/square_1.bmp");
    BITMAP * player_sprite_2  = image_loader("attractions/assets/geometry_dash/square_2.bmp");
    BITMAP * level            = image_loader("attractions/assets/geometry_dash/geometry_map.bmp");
    BITMAP * level_collisions = image_loader("attractions/assets/geometry_dash/geometry_map_collisions.bmp");
    BITMAP * game_over_text   = image_loader("attractions/assets/geometry_dash/game_over.bmp");
    BITMAP * title            = image_loader("attractions/assets/geometry_dash/title.bmp");

    SAMPLE * music            = sound_loader("attractions/assets/geometry_dash/stereo_madness.wav");
    SAMPLE * death_sound      = sound_loader("attractions/assets/geometry_dash/gd_death.wav");

    BITMAP * buffer           = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * buffer_2         = create_bitmap(SCREEN_W, SCREEN_H);


    //* Initialisation du joueur et du background
    Player * player_1 = creer_player();
    Player * player_2 = creer_player();

    Background bg[NB_BACKGROUNDS];
    bg[0].x = 0;
    bg[0].y = 0;
    bg[1].x = SCREEN_W;
    bg[1].y = 0;

    //* Variables
    int largeur = level->w * SCREEN_H / level->h;
    int compteur_frames = 0;
    int SPACE = KEY_SPACE;
    int UP = KEY_UP;
    int winner;

    clock_t start, end;
    double time_spent;

    bool game_over = false;

    //* Musique
    play_sample(music, 100, 128, 1000, 1);

    //* Afficher l'écran de démarrage
    while (!key[KEY_ENTER]) {
        show_start_menu_geometry_dash(level, buffer, title, largeur);
    }

    start = clock();

    //* Boucle principale
    while (!key[KEY_ESC] || !game_over) {

        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        clear_bitmap(buffer);

        //* Gérer le background
        show_background(buffer, level_collisions, bg, largeur);
        show_background(buffer_2, level, bg, largeur);
        move_bcg(compteur_frames, bg, largeur);

        //* Gérer les joueurs (s'ils sont en vie)
        if (player_1->life) {
            jump_and_collide(player_1, buffer, player_sprite, level_collisions, UP, death_sound);
            move_player_to_default(player_1, compteur_frames);
            blit(player_sprite, buffer_2, 0, 0, player_1->x, player_1->y, 50, 50);
        }
        if (player_2->life) {
            jump_and_collide(player_2, buffer, player_sprite, level_collisions, SPACE, death_sound);
            move_player_to_default(player_2, compteur_frames);
            blit(player_sprite_2, buffer_2, 0, 0, player_2->x, player_2->y, 50, 50);
        }


        //* Si l'un des deux joueurs meurt
        if (player_1->life == false && player_2->life == false) {


            // définir le gagnant
            if (!player_1->life) {
                winner = 2;
                scores[1] = time_spent;
                scores[0] = 0;
            } else {
                winner = 1;
                scores[0] = time_spent;
                scores[1] = 0;
            }

            //write_best_score(scores, "tag");

            game_over = true;

            show_game_over(buffer, game_over_text, winner, time_spent);

            while(!key[KEY_ESC]) {
                rest(1);
            }
        }

        //* Affichage
        textprintf_ex(buffer_2, font, 10, 10, makecol(255, 255, 255), -1, "TIME SPENT : %.2f s", time_spent);
        blit(buffer_2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        compteur_frames++;
    }

    stop_sample(music);
    if (winner == 1) {
        return 1;
    } else if(winner == 2){
        return 2;
    }else{
        return 0;
    }
}


Player * creer_player() {

    Player * player = malloc(sizeof(Player));
    player->x = 400;
    player->y = SCREEN_H - 263;
    player->life = true;
    player->jump_speed = 0;
    return player;
}


// fonction pour ecrire le meilleur score dans le fichier "meilleurs_scores.txt"
void write_best_score(float * scores, char * game) {

    // Ouvrir les fichiers best_scores.txt et temp.txt
    FILE * scores_file = fopen("../attractions/assets/best_scores.txt", "r");
    FILE * temp_file   = fopen("../attractions/assets/temp.txt", "w");

    if (scores_file == NULL || temp_file == NULL) {
        scores_file = fopen("attractions\\assets\\best_scores.txt", "r");
        temp_file   = fopen("attractions\\assets\\temp.txt", "w");
    }

    // Déterminer le score max dans le tableau scores
    float score_max = scores[0];
    if (scores[1] > score_max) {
        score_max = scores[1];
    }

    // Déterminer la ligne du fichier best_scores.txt à modifier en fonction du jeu
    int game_line = -1;
    if (strcmp(game, "geometry_dash") == 0) {
        game_line = 1;
    } else if (strcmp(game, "snake") == 0) {
        game_line = 2;
    } else if (strcmp(game, "tape_taupe") == 0) {
        game_line = 3;
    } else if (strcmp(game, "flappy_bird") == 0) {
        game_line = 4;
    } else if (strcmp(game, "jackpot") == 0) {
        game_line = 5;
    } else if (strcmp(game, "guitar_hero") == 0) {
        game_line = 6;
    } else if (strcmp(game, "paris_hippiques") == 0) {
        game_line = 7;
    } else if (strcmp(game, "palais_des_glaces") == 0) {
        game_line = 8;
    } else if (strcmp(game, "tag") == 0) {
        game_line = 9;
    }


    // Parcourir les lignes du fichier best_scores.txt
    char contenu_ligne[100];
    int num_ligne = 1;
    while (fgets(contenu_ligne, sizeof(contenu_ligne), scores_file) != NULL) {
        // Si la ligne n'est pas celle du jeu en question, la copier dans temp.txt
        if (num_ligne != game_line) {
            fputs(contenu_ligne, temp_file);
        } else {
            // Si le score max des joueurs est supérieur au contenu de la ligne, la modifier
            float current_score;
            sscanf(contenu_ligne, "%f", &current_score);
            if (score_max > current_score) {
                fprintf(temp_file, "%.2f\n", score_max);
            } else {
                fputs(contenu_ligne, temp_file);
            }
        }
        num_ligne++;
    }

    // Fermer les fichiers
    fclose(scores_file);
    fclose(temp_file);

    // Supprimer best_scores.txt et renommer temp.txt en "best_scores.txt"
    remove("../attractions/assets/best_scores.txt");
    rename("../attractions/assets/temp.txt", "../attractions/assets/best_scores.txt");
}


void jump_and_collide(Player * player, BITMAP * buffer, BITMAP * sprite, BITMAP * level_collisions, int key_jump, SAMPLE * death_sound) {

    int spike  = makecol(255, 0, 0);
    int air    = makecol(0, 255, 0);
    int ground = makecol(0, 0, 255);

    bool on_ground;
    bool can_jump ;

    //* Détection du sol et des piques
    if (getpixel(buffer, player->x - 1, player->y + sprite->h + 1) == ground || getpixel(buffer, player->x + sprite->w + 1, player->y + sprite->h + 1) == ground) {

        //* Sur le sol
        if (getpixel(buffer, player->x - 1, player->y + sprite->h - 1) == air || getpixel(buffer, player->x + sprite->w + 1, player->y + sprite->h - 1) == air) {
            on_ground = true;
            can_jump = true;
            player->jump_speed = 0;
        }

        //* Dans le sol
        else if (getpixel(buffer, player->x - 1, player->y + sprite->h - 1) == ground || getpixel(buffer, player->x + sprite->w + 1, player->y + sprite->h - 1) == ground) {
            can_jump = false;
            player->y -= player->jump_speed;
            player->jump_speed = 0;
        }
    }

    //* En l'air
    else if (getpixel(buffer, player->x - 1, player->y + sprite->h + 1) == air || getpixel(buffer, player->x + sprite->w + 1, player->y + sprite->h + 1) == air) {
        can_jump = false;
        on_ground = false;
        player->jump_speed++;
    }

    //* Sur/dans un pique
    if (getpixel(buffer, player->x + sprite->w/2, player->y + sprite->h/2) == spike || player->x < - sprite->w) {
        can_jump = false;
        player->life = false;
        play_sample(death_sound, 255, 128, 1000, 0);
    }

    //* Collisions avec les murs
    if (getpixel(buffer, player->x + sprite->w + 1, player->y + sprite->h/2) == ground) {
        player->x -= BCG_SPEED;
    }

    //* Gestion du saut
    if (key[key_jump] && can_jump) {
        player->jump_speed -= JUMP_SPEED;
    }

    //* Appliquer la vitesse de saut
    player->y += player->jump_speed;
}


void move_player_to_default(Player * player, int frame_counter) {

    if (frame_counter % 2 == 0 && player->x < 400) {
        player->x += 2;
    }
}


void show_background(BITMAP * buffer, BITMAP * level, Background bg[NB_BACKGROUNDS], int largeur) {

    for (int i = 0; i < NB_BACKGROUNDS; ++i) {
        stretch_blit(level, buffer, 0, 0, level->w, level->h, bg[i].x, bg[i].y, largeur, SCREEN_H);
    }
}


void move_bcg(int compteur_frames, Background bg[NB_BACKGROUNDS], int largeur) {

    //* deplacement du background toute les 2 frames
    if (compteur_frames % 2 == 0) {
        for (int i = 0; i < NB_BACKGROUNDS; ++i) {
            if (bg[i].x <= - largeur) {
                bg[i].x = bg[(i + 1) % NB_BACKGROUNDS].x + largeur;
            }
            bg[i].x -= BCG_SPEED;
        }
    }
}


void show_game_over(BITMAP * buffer, BITMAP * game_over_text, int winner, double time_spent) {

    BITMAP * game_over_screen = create_bitmap(SCREEN_W, SCREEN_H);

    clear_bitmap(buffer);
    clear_to_color(game_over_screen, makecol(0, 0, 0));

    masked_blit(game_over_text, game_over_screen, 0, 0, SCREEN_W/2 - game_over_text->w/2, SCREEN_H/2 - game_over_text->h/2, game_over_text->w, game_over_text->h);
    textprintf_ex(game_over_screen, font, SCREEN_W/2 - 70, SCREEN_H/2 + 100, makecol(255, 255, 255), -1, "PLAYER %d WINS", winner);
    textprintf_ex(game_over_screen, font, SCREEN_W/2 - 85, SCREEN_H/2 + 150, makecol(255, 255, 255), -1, "TIME SPENT : %.2f s", time_spent);
    textprintf_ex(game_over_screen, font, SCREEN_W/2 - 90, SCREEN_H/2 + 200, makecol(255, 255, 255), -1, "PRESS ESCAPE TO QUIT");

    blit(game_over_screen, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}


void show_start_menu_geometry_dash(BITMAP * level, BITMAP * buffer, BITMAP * title, int largeur) {
    clear_bitmap(buffer);
    stretch_blit(level, buffer, 0, 0, level->w, level->h, 0, 0, largeur, SCREEN_H);
    masked_blit(title, buffer, 0, 0, SCREEN_W/2 - title->w/2, SCREEN_H/2 - title->h/2, title->w, title->h);
    textprintf_ex(buffer, font, SCREEN_W/2 - 100, SCREEN_H/2 + 50, makecol(255, 255, 255), -1, "PRESS ENTER TO START");
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}