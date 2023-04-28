#include <stdio.h>
#include <stdlib.h>
#include <Allegro.h>
#include <time.h>

#define MAX_INTERVALLE 40
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


void affichage_score(Player * player, BITMAP * buffer, int duration) {
    textprintf_ex(buffer, font, 10, 30, makecol(255, 255, 255), -1, "life : %d", player->life);
    textprintf_ex(buffer, font, 10, 50, makecol(255, 255, 255), -1, "duration : %d s", duration);
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


void final_screen(int duration, BITMAP * buffer) {
    clear(buffer);
    textprintf_ex(buffer, font, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), -1, "GAME OVER");
    textprintf_ex(buffer, font, SCREEN_W/2, SCREEN_H/2 + 20, makecol(255, 255, 255), -1, "time : %d s", duration);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}


int main() {

    allegro_init();
    install_mouse();
    install_keyboard();
    install_timer();
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

    Player * player_1 = malloc(sizeof(Player));
    player_1->score = 0;
    player_1->tickets = 5;
    player_1->life = 20;

    Player * player_2 = malloc(sizeof(Player));
    player_2->score = 0;
    player_2->tickets = 5;
    player_2->life = 20;


    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * stage = create_bitmap(SCREEN_W/3, SCREEN_H);
    BITMAP * background = load_bitmap("../assets/background.bmp", NULL);
    BITMAP * logo = load_bitmap("../assets/logo.bmp", NULL);

    int positions[NB_CORDES] = {stage->w/5, stage->w*2/5, stage->w*3/5, stage->w*4/5, };
    int couleurs[NB_CORDES] = {makecol(103, 147, 52), makecol(195, 64, 60), makecol(228, 207, 76), makecol(90, 157, 188)};

    if (!logo || !background) {
        logo = load_bitmap("assets\\logo/bmp", NULL);
        background = load_bitmap("assets\\background.bmp", NULL);
        if (!logo) {
            allegro_message("IMAGE ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    time_t start_time, end_time;
    int duration = 0;


    Note * ancre = NULL;

    time(&start_time);

    Player * player = player_1;

    while (!key[KEY_ESC]) {

        clear_bitmap(buffer);
        clear_to_color(stage, makecol(41, 33, 30));
        masked_stretch_blit(background, buffer, 0, 0, background->w, background->h, 0, 200, SCREEN_W/3 - 1, SCREEN_H - 200);
        stretch_blit(logo, buffer, 0, 0, logo->w, logo->h, SCREEN_W*2/3, 0, SCREEN_W/3, SCREEN_H);

        for (int i = 0; i < NB_CORDES; i++) {
            // ligne verticale pour chaque position de la liste positions
            rectfill(stage, positions[i], 0, positions[i] + 1, SCREEN_H, couleurs[i]);
        }

        show_mouse(screen);

        Note * nouvelle_note = malloc(sizeof(Note));

        if (frame_counter % intervalle == 0) {

            int random_number = rand() % NB_CORDES;
            nouvelle_note->x = positions[random_number];
            nouvelle_note->y = 0;
            nouvelle_note->y_speed = 7;
            nouvelle_note->color = couleurs[random_number];
            nouvelle_note->alive = 1;
            nouvelle_note->next = NULL;

            if (*&ancre == NULL) {
                *&ancre = nouvelle_note;
            }
            else {
                nouvelle_note->next = *&ancre;
                *&ancre =nouvelle_note;
            }
        }


        Note * notes = ancre;
        Note * current = notes;

        while (current->next != NULL) {
            if (current->alive == 1) {
                printf("x : %d, y : %d\n", current->x, current->y);
                circlefill(stage, current->x, current->y, 20, current->color);
                if (current->y <= SCREEN_H - 75 && current->y >= SCREEN_H - 100) {
                    if (key[KEY_D] && current->x == positions[0] || key[KEY_F] && current->x == positions[1] || key[KEY_J] && current->x == positions[2] || key[KEY_K] && current->x == positions[3]) {
                        current->alive = 0;
                        player->score += 10;
                    }
                }
                else if (current->y > SCREEN_H - 10){
                    current->alive = 0;
                    player->life -= 1;
                }
            }
            current = current->next;
        }

        current = notes;

        while (current->next != NULL) {
            if (current->alive == 1) {
                current->y += current->y_speed;
            }
            current = current->next;
        }


        frame_counter++;

        afficher_boutons(stage, positions, couleurs);
        blit(stage, buffer, 0, 0, SCREEN_W/3, 0, SCREEN_W, SCREEN_H);
        rectfill(buffer, 0, 0, SCREEN_W/3 - 1, 200, makecol(255, 0, 0));
        rectfill(buffer, SCREEN_W*2/3, 0, SCREEN_W*2/3 + 2, SCREEN_H, makecol(0, 0, 0));
        rectfill(buffer, SCREEN_W/3, 0, SCREEN_W/3 - 2, SCREEN_H, makecol(0, 0, 0));
        time(&end_time);
        duration = difftime(end_time, start_time);
        affichage_score(player, buffer, duration);

        if (player->life == 0) {
            final_screen(duration, buffer);
            while (!keypressed()) {
                rest(1);
            }
            // passe au joueur suivant
            if (player == player_1) {
                player = player_2;
                time(&start_time);
                ancre->next = NULL;
            }
            else {
                rest(1000);
                allegro_message("GAME OVER");
                allegro_exit();
                exit(EXIT_SUCCESS);
            }
        }

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }

    // liberer la memoire allouee
    destroy_bitmap(buffer);
    destroy_bitmap(stage);
    destroy_bitmap(logo);
    free(player);

    //liberer la memoire allouee pour les notes
    Note * current = ancre;
    Note * next = NULL;
    while (current->next != NULL) {
        free(current);
        current = current->next;
    }

    return 0;
}END_OF_MAIN();
