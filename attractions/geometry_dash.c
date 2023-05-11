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

#define NB_BACKGROUNDS 2


typedef struct Player {
    int x;
    int y;
    bool life;
    int jump_speed;
} Player;


typedef struct {
    int x;
    int y;
} Background;


//? creation du joueur
Player * creer_player() {
    Player * player = malloc(sizeof(Player));
    player->x = 200;
    player->y = SCREEN_H - 263;
    player->life = true;
    player->jump_speed = 0;
    return player;
}


//? gestion du saut
void jump(Player * player, BITMAP * buffer, BITMAP * sprite) {

    int ground_level = SCREEN_H - 263;

    // If user press space and player is on the ground
    if (key[KEY_SPACE] && player->y == ground_level) {
        // Increase y speed
        player->jump_speed -= 17;
    }

    player->y += player->jump_speed;

    // If player is under the ground
    if (player->y > ground_level) {
        player->y = ground_level;
    }

    // If player is not on the ground
    if (player->y < ground_level) {
        // Increase y speed
        player->jump_speed += 1;
    }

    else {
        player->jump_speed = 0;
    }
}


void show_background(BITMAP * buffer, BITMAP * level, Background bg[NB_BACKGROUNDS], int largeur) {

    for (int i = 0; i < NB_BACKGROUNDS; ++i) {
        stretch_blit(level, buffer, 0, 0, level->w, level->h, bg[i].x, bg[i].y, largeur, SCREEN_H);
    }
}


void move_bcg(int compteur_frames, Background bg[NB_BACKGROUNDS], int largeur) {
    if (compteur_frames % 2 == 0) {
        for (int i = 0; i < NB_BACKGROUNDS; ++i) {
            if (bg[i].x <= - largeur) {
                bg[i].x = bg[(i+1)%NB_BACKGROUNDS].x + largeur;
            }
            bg[i].x -= 10;
        }
    }
}


//? initialisation d'allegro
void init_allegro() {

    allegro_init();
    install_mouse();
    install_keyboard();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    install_timer();
    set_window_title("GEOMETRY DASH");

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1200, 800, 0, 0) != 0) {
        allegro_message("GFX ERROR");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}


int main () {

    init_allegro();

    //* charger les bitmaps
    BITMAP * player_sprite = load_bitmap("../assets/geometry_dash/square2.bmp", NULL);
    BITMAP * level = load_bitmap("../assets/geometry_dash/geometry_map.bmp", NULL);
    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(buffer);
    SAMPLE * music = load_sample("../sounds/stereo_madness.wav");

    // If loading failed
    if (!player_sprite || !level || !music) {
        player_sprite = load_bitmap("assets\\geometry_dash\\square.bmp", NULL);
        level = load_bitmap("assets\\geometry_dash\\geometry_map.bmp", NULL);
        music = load_sample("sounds\\stereo_madness.wav");
        if (!player_sprite || !level || !music) {
            allegro_message("LOADING ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    //* initialisation du joueur
    Player * player = creer_player();

    Background bg[NB_BACKGROUNDS];
    bg[0].x = 0;
    bg[0].y = 0;
    bg[1].x = SCREEN_W;
    bg[1].y = 0;


    int largeur = level->w * SCREEN_H / level->h;
    int compteur_frames = 0;

    bool game_over = false;

    //* musique
    show_mouse(screen);
    play_sample(music, 255, 128, 1000, 1);


    //* boucle principale
    while (!key[KEY_ESC] || game_over) {
        clear_bitmap(buffer);

        show_background(buffer, level, bg, largeur);
        move_bcg(compteur_frames, bg, largeur);

        jump(player, buffer, player_sprite);

        //* affichage
        blit(player_sprite, buffer, 0, 0, player->x, player->y, 50, 50);
        blit(buffer, screen, 0, 0, 0, 0,SCREEN_W,SCREEN_H);
        compteur_frames++;
    }

    return 0;
}END_OF_MAIN();