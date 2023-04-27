#include <stdio.h>
#include <stdlib.h>
#include <Allegro.h>
#include <time.h>

#define MAX_INTERVALLE 70
#define MIN_INTERVALLE 30
#define NB_CORDES 4


typedef struct {
    int score;
    int tickets;
    int life;
} Player;


typedef struct {
    int x;
    int y;
    int y_speed;
    int color;
    int alive;
    struct Note * next;
} Note;


void affichage_score(Player * player, BITMAP * buffer) {
    textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "Score : %d", player->score);
    textprintf_ex(buffer, font, 10, 30, makecol(255, 255, 255), -1, "life : %d", player->life);
}


void afficher_boutons(BITMAP * stage, int positions[5], int couleurs[5]) {
    for (int i = 0; i < NB_CORDES; i++) {
        // cercle pour chaque position de la liste posisions en bas du stage
        int hauteur = SCREEN_H - 100;
        circlefill(stage, positions[i], hauteur, 20, makecol(255, 255, 255));
        circlefill(stage, positions[i], hauteur, 18, couleurs[i]);
        circle(stage, positions[i], hauteur, 8, makecol(0, 0, 0));
    }
}


int main() {

    allegro_init();
    install_mouse();
    install_keyboard();
    set_window_title("GUITAR HERO");

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1200, 800, 0, 0) != 0) {
        allegro_message("GFX ERROR");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    int frame_counter = 0;
    int intervalle = MAX_INTERVALLE;

    Player * player = malloc(sizeof(Player));
    player->score = 0;
    player->tickets = 5;
    player->life = 20;

    Player * player_2 = malloc(sizeof(Player));
    player_2->score = 0;
    player_2->tickets = 5;
    player_2->life = 20;


    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * stage = create_bitmap(SCREEN_W/3, SCREEN_H);
    BITMAP * final_screen = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * logo = load_bitmap("../assets/guitar_hero/logo.bmp", NULL);

    int positions[NB_CORDES] = {stage->w/5, stage->w*2/5, stage->w*3/5, stage->w*4/5, };
    int couleurs[NB_CORDES] = {makecol(103, 147, 52), makecol(195, 64, 60), makecol(228, 207, 76), makecol(90, 157, 188)};

    if (!logo) {
        logo = load_bitmap("assets\\guitar_hero\\logo.bmp", NULL);
        if (!logo) {
            allegro_message("IMAGE ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    while (!key[KEY_ESC]) {

        clear_bitmap(buffer);
        clear_to_color(stage, makecol(41, 33, 30));
        stretch_blit(logo, buffer, 0, 0, logo->w, logo->h, SCREEN_W*2/3, 0, SCREEN_W/3, SCREEN_H);

        for (int i = 0; i < NB_CORDES; i++) {
            // ligne verticale pour chaque position de la liste positions
            rectfill(stage, positions[i], 0, positions[i] + 1, SCREEN_H, couleurs[i]);
        }


        afficher_boutons(stage, positions, couleurs);
        blit(stage, buffer, 0, 0, SCREEN_W/3, 0, SCREEN_W, SCREEN_H);
        rectfill(buffer, 0, 0, SCREEN_W/3 - 1, 200, makecol(255, 0, 0));
        affichage_score(player, buffer);

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }

    return 0;
}END_OF_MAIN();
