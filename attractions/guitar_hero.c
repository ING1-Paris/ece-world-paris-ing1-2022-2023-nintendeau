#include <stdio.h>
#include <stdlib.h>
#include <Allegro.h>
#include <time.h>

#define MAX_INTERVALLE 40
#define NB_CORDES 4


typedef struct {
    int temps;
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


// afficher le temps de jeu et le nombre de vies restantes
void affichage_temps(Player * player, BITMAP * buffer, int duration) {
    textprintf_ex(buffer, font, 10, 30, makecol(255, 255, 255), -1, "life : %d", player->life);
    textprintf_ex(buffer, font, 10, 50, makecol(255, 255, 255), -1, "duration : %d s", duration);
}


// afficher les boutons en bas du stage
void afficher_boutons(BITMAP * stage, int positions[5], int couleurs[5]) {
    for (int i = 0; i < NB_CORDES; i++) {
        // cercle pour chaque position de la liste posisions en bas du stage
        int hauteur = SCREEN_H - 100;
        circlefill(stage, positions[i], hauteur, 20, makecol(255, 255, 255));
        circlefill(stage, positions[i], hauteur, 18, couleurs[i]);
        circle(stage, positions[i], hauteur, 8, makecol(0, 0, 0));
    }

    // deux lignes horizontales pour delimiter la zone de pression
    rectfill(stage, 0, SCREEN_H - 78, stage->w, SCREEN_H - 78, makecol(255, 255, 255));
    rectfill(stage, 0, SCREEN_H - 122, stage->w, SCREEN_H - 122, makecol(255, 255, 255));
}


// afficher l'écran de fin de partie
void final_screen(int duration, BITMAP * buffer, BITMAP * game_over) {
    clear(buffer);
    textprintf_ex(buffer, font, SCREEN_W/2 - 50, SCREEN_H/2  + 50, makecol(255, 255, 255), -1, "time : %d s", duration);
    textprintf_ex(buffer, font, SCREEN_W/2 - 140, SCREEN_H/2  + 65, makecol(255, 255, 255), -1, "Appuyer sur ENTER pour continuer");
    masked_stretch_blit(game_over, buffer, 0, 0, game_over->w, game_over->h, SCREEN_W/2 - game_over->w, SCREEN_H/2 - game_over->h, game_over->w*2, game_over->h*2);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}


int victory (int temps_1, int temps_2) {
    if (temps_1 > temps_2) {
        return 1;
    } else if (temps_1 < temps_2) {
        return 2;
    } else {
        return 0;
    }
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

    Player * player_1 = malloc(sizeof(Player));
    player_1->temps = 0;
    player_1->tickets = 5;
    player_1->life = 10;

    Player * player_2 = malloc(sizeof(Player));
    player_2->temps = 0;
    player_2->tickets = 5;
    player_2->life = 10;

    Player * player = player_1;


    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * stage = create_bitmap(SCREEN_W/3, SCREEN_H);
    BITMAP * background = load_bitmap("../assets/background.bmp", NULL);
    BITMAP * logo = load_bitmap("../assets/logo.bmp", NULL);
    BITMAP * game_over = load_bitmap("../assets/game_over.bmp", NULL);

    int frame_counter = 0;
    int intervalle = MAX_INTERVALLE;
    int liste_boutons[4] = {0};

    int positions[NB_CORDES] = {stage->w/5, stage->w*2/5, stage->w*3/5, stage->w*4/5, };
    int couleurs[NB_CORDES] = {makecol(103, 147, 52), makecol(195, 64, 60), makecol(228, 207, 76), makecol(90, 157, 188)};

    if (!logo || !background || !game_over) {
        game_over = load_bitmap("assets\\game_over.bmp", NULL);
        logo = load_bitmap("assets\\logo.bmp", NULL);
        background = load_bitmap("assets\\background.bmp", NULL);
        if (!logo || !background || !game_over) {
            allegro_message("IMAGE ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    time_t start_time, end_time;
    int duration = 0;

    Note * ancre = NULL;

    time(&start_time);

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

            // création d'une nouvelle note
            int random_number = rand() % NB_CORDES;
            nouvelle_note->x = positions[random_number];
            nouvelle_note->y = 0;
            nouvelle_note->y_speed = 7;
            nouvelle_note->color = couleurs[random_number];
            nouvelle_note->alive = 1;
            nouvelle_note->next = NULL;

            // ajout de la note à la liste chainée
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

        // si la note est vivante
        while (current->next != NULL) {
            if (current->alive == 1) {
                // on l'affiche
                circlefill(stage, current->x, current->y, 20, current->color);
                // si la note est dans la zone de pression
                if (current->y <= SCREEN_H - 78 && current->y >= SCREEN_H - 122) {
                    // si la touche correspondante est pressée
                    if (key[KEY_D] && current->x == positions[0] || key[KEY_F] && current->x == positions[1] || key[KEY_J] && current->x == positions[2] || key[KEY_K] && current->x == positions[3]) {
                        // si la touche n'a pas déjà été pressée a la frame précédente, onn supprime la note
                        if (key[KEY_D] != liste_boutons[0] || key[KEY_F] != liste_boutons[1] || key[KEY_J] != liste_boutons[2] || key[KEY_K] != liste_boutons[3]) {
                            current->alive = 0;
                        }
                    }
                }
                // sinon si la touche dépasse la zone, on la supprime et on enlève une vie
                else if (current->y > SCREEN_H - 10){
                    current->alive = 0;
                    player->life -= 1;
                }
            }
            current = current->next;
        }

        current = notes;

        // on fait descendre les notes vivantes
        while (current->next != NULL) {
            if (current->alive == 1) {
                current->y += current->y_speed;
            }
            current = current->next;
        }

        // on incrémente le compteur de frames
        frame_counter++;

        // on affiche ce qu'il y a a afficher (boutons, stage, le rested de l'UI)
        afficher_boutons(stage, positions, couleurs);
        blit(stage, buffer, 0, 0, SCREEN_W/3, 0, SCREEN_W, SCREEN_H);
        rectfill(buffer, 0, 0, SCREEN_W/3 - 1, 200, makecol(255, 0, 0));
        rectfill(buffer, SCREEN_W*2/3, 0, SCREEN_W*2/3 + 2, SCREEN_H, makecol(0, 0, 0));
        rectfill(buffer, SCREEN_W/3, 0, SCREEN_W/3 - 2, SCREEN_H, makecol(0, 0, 0));
        time(&end_time);

        // on calcule le temps écoulé depuis le début de la partie
        duration = difftime(end_time, start_time);
        affichage_temps(player, buffer, duration);

        // si le joueur n'a plus de vie, on affiche l'écran de fin
        if (player->life == 0) {
            player->temps = duration;
            final_screen(duration, buffer, game_over);

            // on attend que le joueur appuie sur entrée pour continuer
            while (!key[KEY_ENTER]) {
                rest(1);
            }

            // on passe au joueur suivant, on réinitialise le temps et on vide la liste chainée
            if (player == player_1) {
                player_1 = player;
                player = player_2;
                time(&start_time);
                ancre->next = NULL;
            }

            // si le joueur 2 a joué, on affiche l'écran de fin
            else {
                player_2 = player;
                int gagnant = victory(player_1->temps, player_2->temps);
                textprintf_ex(buffer, font, SCREEN_W/2 - 70, SCREEN_H/2 + 80, makecol(255, 255, 255), -1, "Joueur %d gagne !", gagnant);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(2000);
                allegro_message("GAME OVER");
                allegro_exit();
                exit(EXIT_SUCCESS);
            }
        }

        // on met à jour la liste des boutons pressés
        liste_boutons[0] = key[KEY_D];
        liste_boutons[1] = key[KEY_F];
        liste_boutons[2] = key[KEY_J];
        liste_boutons[3] = key[KEY_K];

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }

    // on libère la memoire allouee
    destroy_bitmap(buffer);
    destroy_bitmap(stage);
    destroy_bitmap(logo);
    free(player);

    // on libère la memoire allouée pour les notes
    Note * current = ancre;
    Note * next = NULL;
    while (current->next != NULL) {
        free(current);
        current = current->next;
    }

    return 0;
}END_OF_MAIN();
