//! Alfred de Vulpian - Groupe 13 - ECE Paris - 2023

//#   ________________  __  _____________________  __   ____  ___   _____ __  __
//#  / ____/ ____/ __ \/  |/  / ____/_  __/ __ \ \/ /  / __ \/   | / ___// / / /
//# / / __/ __/ / / / / /|_/ / __/   / / / /_/ /\  /  / / / / /| | \__ \/ /_/ /
//#/ /_/ / /___/ /_/ / /  / / /___  / / / _, _/ / /  / /_/ / ___ |___/ / __  /
//#\____/_____/\____/_/  /_/_____/ /_/ /_/ |_| /_/  /_____/_/  |_/____/_/ /_/


#include <stdio.h>
#include <allegro.h>
#include <stdbool.h>


typedef struct Player {
    int x;
    int y;
    bool life;
    int y_speed;
} Player;


//? creation du joueur
Player * creer_player() {
    Player * player = malloc(sizeof(Player));
    player->x = 200;
    player->y = SCREEN_H - 50;
    player->life = true;
    player->y_speed = 0;
    return player;
}


//? gestion du saut
void jump(Player * player, BITMAP * level, BITMAP * player_sprite) {
    int x = player->x;
    if (player->y > SCREEN_H - 50) {
        player->y_speed = 0;
        player->y = SCREEN_H - 50;
    }
    else if (getpixel(level, x, player->y + 50) == makecol(255, 255, 255)) {
        player->y_speed = 0;
        player->y = player->y;
    }
    else {
        player->y_speed += 1;
        player->y += player->y_speed;
    }

    if (key[KEY_SPACE]) {
        player->y_speed = -10;
        player->y += player->y_speed;
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
    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * player_sprite = load_bitmap("../assets/geometry_dash/square.bmp", NULL);
    BITMAP * player_bmp = create_bitmap(player_sprite->w, player_sprite->h);

    BITMAP * level = load_bitmap("../assets/geometry_dash/geometry_map.bmp", NULL);
    SAMPLE * music = load_sample("../sounds/Stereo-Madness.wav");

    if (!player_sprite || !level || !music) {
        player_sprite = load_bitmap("assets\\geometry_dash\\square.bmp", NULL);
        level = load_bitmap("assets\\geometry_dash\\geometry_map.bmp", NULL);
        music = load_sample("sounds\\Stereo-Madness.wav");
        if (!player_sprite || !level || !music) {
            allegro_message("LOADING ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    //* initialisation du joueur
    Player * player = creer_player();

    show_mouse(screen);

    int largeur = level->w * SCREEN_H / level->h;

    bool game_over = false;

    //* musique
    play_sample(music, 255, 128, 1000, 1);


    //* boucle principale
    while (!key[KEY_ESC] || game_over) {

        jump(player, level, player_sprite);

        //* affichage
        stretch_blit(level, buffer, 0, 0, level->w, level->h, 0, 0, largeur, SCREEN_H);
        stretch_blit(player_sprite, buffer, 0, 0, player_sprite->w, player_sprite->h, player->x, player->y, 50, 50);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    readkey();
    return 0;
}END_OF_MAIN();