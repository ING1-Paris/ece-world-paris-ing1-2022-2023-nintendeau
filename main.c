//! Code principal du projet d'algo du dexieme semestre

//? Objectif: Creer un jeu de parc d'attraction.
//?  - possibilité de se deplacer sur la carte du parc, qui servira aussi de menu.
//?  - systeme de tickets pour participer aux attractions.
//?  - systeme de sauvegarde du meilleur score de chaque attractions.
//?  - chaque membre de l'equipe doit programmer integrallement au moins une attraction.

//& 4 fichiers .h seront mis en place dans le dossier "attractions" pour accueilir les codes des 4 attractions (4 membres de l'equipe).
//& les fichiers .h seront inclus dans le main.c, dans lequel le code principal sera ecrit.

#include <stdio.h>
#include <Allegro.h>
#include "attractions/header/tag.h"
#include "attractions/header/geometry_dash.h"
#include "attractions/header/guitar_hero.h"
#include "attractions/header/guitar_hero.h"


// Structure Player qui contient les informations du joueur
typedef struct {
    int x, y;
    int previous_x, previous_y;
    int speed;
    int score;
    int tickets;
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


void launch_game(int active) {
    if (active) {
        textprintf_ex(screen, font, SCREEN_W/2 - 50, SCREEN_H - 50, makecol(255, 255, 255), -1, "LAUNCH GAME");
    }
}


// fonction qui gere les collisions de la map
void check_collision(Player * player, BITMAP * calque_collisions, BITMAP * player_sprite, SAMPLE * music_main) {

    int active = 0;

    int x = player->previous_x;
    int y = player->previous_y;

    int ground = makecol(0, 255, 0);
    int wall   = makecol(255, 0, 0);

    int palais_des_glaces_color = makecol(30, 124, 184);
    int paris_hippiques_color   = makecol(127, 0, 127);
    int geometry_dash_color     = makecol(0, 0, 127);
    int tape_taupe_color        = makecol(255, 255, 0);
    int guitar_hero_color       = makecol(127, 0, 0);
    int jackpot_color           = makecol(0, 127, 127);
    int tag_color               = makecol(127, 127, 127);
    int snake_color             = makecol(0, 127, 0);
    int flappy_bird_color       = makecol(0, 255, 255);

    int color_array[11] = {ground, wall, palais_des_glaces_color, paris_hippiques_color, geometry_dash_color, tape_taupe_color, guitar_hero_color, jackpot_color, tag_color, snake_color , flappy_bird_color};

    for (int i = 0; i < 11; i++) {
        // on regarde la couleur des pixels aux 4 coins de la hitbox du joueur
        if (getpixel(calque_collisions, (player->x)*calque_collisions->w/SCREEN_W, (player->y + player_sprite->h/1.3)*calque_collisions->h/SCREEN_H) == color_array[i] || getpixel(calque_collisions, (player->x + player_sprite->w)*calque_collisions->w/SCREEN_W, (player->y + player_sprite->h/1.3)*calque_collisions->h/SCREEN_H) == color_array[i] || getpixel(calque_collisions, (player->x)*calque_collisions->w/SCREEN_W, (player->y + player_sprite->h)*calque_collisions->h/SCREEN_H) == color_array[i] || getpixel(calque_collisions, (player->x + player_sprite->w)*calque_collisions->w/SCREEN_W, (player->y + player_sprite->h)*calque_collisions->h/SCREEN_H) == color_array[i]) {
            // si le joueur est sur une case mur, on le replace a sa position precedente
            active = 0;
            if (color_array[i] == wall) {
                player->x = x;
                player->y = y;
            }

            // si le joueur est sur un jeu, on lance l'attraction correspondante
            else if (color_array[i] != ground) {
                if (color_array[i] == palais_des_glaces_color) {
                    printf("palais_des_glaces\n");
                }
                else if (color_array[i] == paris_hippiques_color) {
                    printf("paris_hippiques\n");
                }
                else if (color_array[i] == geometry_dash_color) {
                    printf("geometry_dash\n");
                    geometry_dash();
                }
                else if (color_array[i] == tape_taupe_color) {
                    printf("tape_taupe\n");
                }
                else if (color_array[i] == guitar_hero_color) {
                    printf("guitar_hero\n");
                    stop_sample(music_main);
                    guitar_hero();
                }
                else if (color_array[i] == jackpot_color) {
                    printf("jackpot\n");
                }
                else if (color_array[i] == tag_color) {
                    printf("tag\n");
                    tag();

                }
                else if (color_array[i] == snake_color) {
                    printf("snake\n");
                }
                else if (color_array[i] == flappy_bird_color) {
                    printf("flappy_bird\n");
                }
                player->y = 300;
                player->x = 300;
            }
            player->previous_x = player->x;
            player->previous_y = player->y;
        }

        // collisions avec les bordures de la fenetre
        else if (player->x < 0)
            player->x = 0;
        else if (player->x > SCREEN_W - player_sprite->w)
            player->x = SCREEN_W - player_sprite->w;
        else if (player->y < 0)
            player->y = 0;
        else if (player->y > SCREEN_H - player_sprite->h)
            player->y = SCREEN_H - player_sprite->h;

        // actualisation de la position precedente
        else {
            player->previous_x = player->x;
            player->previous_y = player->y;
        }
    }
}


// afficher le score
void afficher_score(BITMAP * score_image, BITMAP * buffer, Player player) {
    stretch_blit(score_image, buffer, 0, 0, score_image->w, score_image->h, 0, 0, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer, font, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Score: %d", player.score);
}


// fonction d'affichage
void afficher_map(BITMAP * titre, BITMAP * buffer, BITMAP * map, BITMAP * player_sprite, Player player, int * can_move, BITMAP * score_image, BITMAP * calque_collisions) {

    clear_bitmap(buffer);
    stretch_blit(calque_collisions, buffer, 0, 0, calque_collisions->w, calque_collisions->h, 0, 0, buffer->w, buffer->h);
    stretch_blit(map, buffer, 0, 0, map->w, map->h, 0, 0, buffer->w, buffer->h);
    masked_blit(player_sprite, buffer, 0, 0, player.x, player.y, player_sprite->w, player_sprite->h);
    masked_stretch_blit(titre, buffer, 0, 0, titre->w, titre->h, SCREEN_W/2 - titre->w/1.35, SCREEN_H/2 - titre->h*1.5, titre->w*1.5, titre->h*1.5);

    // enlever le titre si la souris est clique
    if (key[KEY_SPACE] || mouse_b & 1) {
        clear_to_color(titre, makecol(255, 0, 255));
        *can_move = 1;
    }

    // afficher le score si le joueur est sur la case "score"
    if (940 < player.x && player.x < 1000 && 100 < player.y && player.y < 200) {
        afficher_score(score_image, buffer, player);
    }

    blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
}


void move_player(Player * player) {
    if (key[KEY_UP]) {
        player->y -= player->speed;
    }
    if (key[KEY_DOWN]) {
        player->y += player->speed;
    }
    if (key[KEY_LEFT]) {
        player->x -= player->speed;
    }
    if (key[KEY_RIGHT]) {
        player->x += player->speed;
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
    int frame_count = 0;
    int can_move = 0;

    //! CHARGEMENT DES BITMAPS
    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * titre = load_bitmap("attractions\\assets\\Titre.bmp", NULL);
    BITMAP * map = load_bitmap("attractions\\assets\\map_v3.bmp", NULL);
    BITMAP * calque_collisions = load_bitmap("attractions\\assets\\collision_v3.bmp", NULL);
    BITMAP * score_image = load_bitmap("attractions\\assets\\score.bmp", NULL);
    BITMAP * player_sprite = load_bitmap("attractions\\assets\\anim_player_bas\\frame_1.bmp", NULL);
    SAMPLE * music_main = load_wav("attractions\\assets\\music_main.wav");

    // si le chemin d'acces ne fonctionne pas, on essaye avec un autre chemin d'acces (pour Clion et vscode)
    if (!map || !player_sprite || !titre || !score_image || !calque_collisions || !music_main) {

        map = load_bitmap("../attractions/assets/map_v3.bmp", NULL);
        player_sprite = load_bitmap("../attractions/assets/anim_player_bas/frame_1.bmp", NULL);
        titre = load_bitmap("../attractions/assets/Titre.bmp", NULL);
        score_image = load_bitmap("../attractions/assets/score.bmp", NULL);
        calque_collisions = load_bitmap("../attractions/assets/collision_v3.bmp", NULL);
        music_main = load_wav("../attractions/assets/music_main.wav");

        if (!map || !player_sprite || !titre || !score_image || !calque_collisions || !music_main) {
            allegro_message("BITMAP ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    //& reste du code principal
    // fait apparaitre le joueur au centre de l'ecran
    Player player = {200, 200, 4, 0, 5}; //!{x, y, width, height, speed, score}

    play_sample(music_main, 255, 128, 1000, 1);

    //& boucle principale du menu (carte du parc)
    while (!key[KEY_M]) {

        check_collision(&player, calque_collisions, player_sprite, music_main);

        if (can_move) {
            move_player(&player);
        }

        // test pour le score
        if (mouse_x > player.x && mouse_x < player.x + player_sprite->w && mouse_y > player_sprite->h && mouse_y < player.y + player_sprite->h) {
            player.score++;
        }

        // ecrire le score dans le fichier
        //write_best_score(player.score);

        // passer a la frame suivante de l'animation du joueur (4 frames)
        frame_count = (frame_count + 1) % 4;

        afficher_map(titre, buffer, map, player_sprite, player, &can_move, score_image, calque_collisions);
    }

    readkey();
    allegro_exit();
    return 0;
}END_OF_MAIN();