#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>
#include <time.h>
#include "../header/guitar_hero.h"
#include "../header/loader.h"

#define BPM 30
#define MAX_INTERVALLE 2 * BPM // (1 bpm = 2 temps)
#define NB_CORDES 4


typedef struct {
    double temps;
    int life;
    int id;
    char name[100];
} Player;


typedef struct note {
    int x;
    int y;
    int y_speed;
    int color;
    int alive;
    struct note * next;
} Note;


Player * creer_joueur(int id);
Note * allouer_note(Note * note, int x, int color);
int victory (int temps_1, int temps_2);
void afficher_stats(Player * player, BITMAP * buffer, int duration);
void afficher_boutons(BITMAP * stage, int positions[5], int couleurs[5]);
void afficher_final_screen(int duration, BITMAP * buffer, BITMAP * game_over);
void fin_partie(BITMAP * buffer, int gagnant, char * nom1, char * nom2);
void afficher(BITMAP * buffer, BITMAP * stage, int positions[4], int couleurs[4]);
void afficher_cordes(BITMAP * stage, int positions[4], int couleurs[4]);
void afficher_note(BITMAP * stage, Note * note);
void free_memory(BITMAP * buffer, BITMAP * stage, BITMAP * logo, BITMAP * background, BITMAP * game_over, Player * player_1, Player * player_2, Player * player, Note * ancre);
void play_guitar(Note * note, int positions[4], SAMPLE * music);
void show_start_menu_guitar_hero(BITMAP * buffer, BITMAP * title);

int guitar_hero(char * nom1, char * nom2, float scores[2]) {

    set_window_title("Guitar Hero");

    srand(time(NULL));

    // initialisation des joueurs
    Player * player_1 = creer_joueur(1);
    strcpy(player_1->name, nom1);
    Player * player_2 = creer_joueur(2);
    strcpy(player_2->name, nom2);
    Player * player   = player_1;

    // initialisation et chargement des bitmaps

    BITMAP * background = image_loader("attractions/assets/guitar_hero/background.bmp");
    BITMAP * logo       = image_loader("attractions/assets/guitar_hero/logo.bmp");
    BITMAP * game_over  = image_loader("attractions/assets/guitar_hero/game_over.bmp");
    BITMAP * title      = image_loader("attractions/assets/guitar_hero/title.bmp");

    SAMPLE * music      = sound_loader("attractions/assets/guitar_hero/guitar.wav");

    BITMAP * buffer     = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * stage      = create_bitmap(SCREEN_W/3, SCREEN_H);

    // variables
    int frame_counter    = 0;
    int intervalle       = MAX_INTERVALLE;
    int liste_boutons[4] = {0};
    double duration       = 0;
    time_t start_time, end_time;

    int positions[NB_CORDES] = {stage->w/5, stage->w*2/5, stage->w*3/5, stage->w*4/5, };
    int couleurs[NB_CORDES]  = {makecol(103, 147, 52), makecol(195, 64, 60), makecol(228, 207, 76), makecol(90, 157, 188)};

    Note * ancre = NULL;

    //* Afficher l'écran de démarrage
    while (!key[KEY_ENTER]) {
        show_start_menu_guitar_hero(buffer, title);
    }

    // on démarre le timer
    time(&start_time);
    int gagnant = 0;

    // boucle principale
    while (!key[KEY_ESC] || gagnant != 0) {

        //réinitialiser le buffer et le stage
        clear_bitmap(buffer);
        clear_to_color(stage, makecol(41, 33, 30));
        masked_stretch_blit(background, buffer, 0, 0, background->w, background->h, 0, 200, SCREEN_W/3 - 1, SCREEN_H - 200);
        stretch_blit(logo, buffer, 0, 0, logo->w, logo->h, SCREEN_W*2/3, 0, SCREEN_W/3, SCREEN_H);
        afficher_cordes(stage, positions, couleurs);

        // on initialise la nouvelle note
        Note * nouvelle_note = malloc(sizeof(Note));

        if (frame_counter % intervalle == 0) {

            // création d'une nouvelle note
            int random_number = rand() % NB_CORDES;
            nouvelle_note = allouer_note(nouvelle_note, positions[random_number], couleurs[random_number]);

            // ajout de la note à la liste chainée
            if (*&ancre == NULL) {
                *&ancre = nouvelle_note;
            }
            else {
                nouvelle_note->next = *&ancre;
                *&ancre = nouvelle_note;
            }
        }

        // on parcourt la liste chainée
        Note * notes = ancre;
        Note * current = notes;

        // si la note est vivante
        while (current->next != NULL) {
            if (current->alive == 1) {
                // on l'affiche
                afficher_note(stage, current);
                // si la note est dans la zone de pression
                if (current->y <= SCREEN_H - 70 && current->y >= SCREEN_H - 130) {
                    // si la touche correspondante est pressée
                    if (key[KEY_D] && current->x == positions[0] || key[KEY_F] && current->x == positions[1] || key[KEY_J] && current->x == positions[2] || key[KEY_K] && current->x == positions[3]) {
                        // si la touche n'a pas déjà été pressée a la frame précédente, onn supprime la note
                        if (key[KEY_D] != liste_boutons[0] || key[KEY_F] != liste_boutons[1] || key[KEY_J] != liste_boutons[2] || key[KEY_K] != liste_boutons[3]) {
                            current->alive = 0;
                        }

                        play_guitar(current, positions, music);
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
        afficher(buffer, stage, positions, couleurs);

        // on calcule le temps écoulé depuis le début de la partie
        time(&end_time);
        duration = difftime(end_time, start_time);
        afficher_stats(player, buffer, duration);

        // si le joueur n'a plus de vie, on affiche l'écran de fin
        if (player->life <= 0) {
            player->temps = duration;
            afficher_final_screen(duration, buffer, game_over);

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
                player_2->id = 2;
                gagnant = victory(player_1->temps, player_2->temps);
                fin_partie(buffer, gagnant, nom1, nom2);
                destroy_sample(music);
                scores[0] = player_1->temps;
                scores[1] = player_2->temps;
                return gagnant;
            }
        }

        // on met à jour la liste des boutons pressés
        liste_boutons[0] = key[KEY_D];
        liste_boutons[1] = key[KEY_F];
        liste_boutons[2] = key[KEY_J];
        liste_boutons[3] = key[KEY_K];

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }

    // on libère la memoire allouée
    //free_memory(buffer, stage, logo, background, game_over, player_1, player_2, player, ancre);
    //destroy_sample(music);
    return 0;
}


void afficher_stats(Player * player, BITMAP * buffer, int duration) {
    textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "%s", player->name);
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

    // deux lignes horizontales pour delimiter la zone de pression
    rectfill(stage, 0, SCREEN_H - 78, stage->w, SCREEN_H - 78, makecol(255, 255, 255));
    rectfill(stage, 0, SCREEN_H - 122, stage->w, SCREEN_H - 122, makecol(255, 255, 255));
}


void afficher_final_screen(int duration, BITMAP * buffer, BITMAP * game_over) {
    clear(buffer);
    textprintf_ex(buffer, font, SCREEN_W/2 - 50, SCREEN_H/2  + 50, makecol(255, 255, 255), -1, "time : %d s", duration);
    textprintf_ex(buffer, font, SCREEN_W/2 - 140, SCREEN_H/2  + 65, makecol(255, 255, 255), -1, "Appuyer sur ENTER pour continuer");
    masked_stretch_blit(game_over, buffer, 0, 0, game_over->w, game_over->h, SCREEN_W/2 - game_over->w, SCREEN_H/2 - game_over->h, game_over->w*2, game_over->h*2);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}


Player * creer_joueur(int id) {
    Player * player = malloc(sizeof(Player));
    player->id = id;
    player->life = 10;
    player->temps = 0;
    return player;
}


int victory (int temps_1, int temps_2) {
    return (temps_1 > temps_2) ? 1 : (temps_2 > temps_1) ? 2 : 0;
}


void fin_partie(BITMAP * buffer, int gagnant, char * nom1, char * nom2) {

    if (gagnant != 0) {
        if (gagnant == 1){
            textprintf_ex(buffer, font, SCREEN_W / 2 - 70, SCREEN_H / 2 + 80, makecol(255, 255, 255), -1,"%s gagne !",nom1);
        }else{
            textprintf_ex(buffer, font, SCREEN_W / 2 - 70, SCREEN_H / 2 + 80, makecol(255, 255, 255), -1,"%s gagne !",nom2);
        }

    }
    else {
        textprintf_ex(buffer, font, SCREEN_W / 2 - 47, SCREEN_H / 2 + 80, makecol(255, 255, 255), -1, "Egalite !");
    }

    textprintf_ex(buffer, font, SCREEN_W / 2 - 90, SCREEN_H / 2 + 100, makecol(255, 255, 255), -1, "MERCI D'AVOIR JOUE !");
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    rest(2000);
}


void afficher(BITMAP * buffer, BITMAP * stage, int positions[4], int couleurs[4]) {
    afficher_boutons(stage, positions, couleurs);
    blit(stage, buffer, 0, 0, SCREEN_W/3, 0, SCREEN_W, SCREEN_H);
    rectfill(buffer, SCREEN_W*2/3, 0, SCREEN_W*2/3 + 2, SCREEN_H, makecol(0, 0, 0));
    rectfill(buffer, SCREEN_W/3, 0, SCREEN_W/3 - 2, SCREEN_H, makecol(0, 0, 0));
    rectfill(buffer, 0, 70, SCREEN_W/3, 71, makecol(255, 255, 255));
}


void afficher_cordes(BITMAP * stage, int positions[4], int couleurs[4]) {
    for (int i = 0; i < NB_CORDES; i++) {
        rectfill(stage, positions[i], 0, positions[i] + 1, SCREEN_H, couleurs[i]);
    }
}


void afficher_note(BITMAP * stage, Note * note) {
    circlefill(stage, note->x, note->y, 20, note->color);
}


void free_memory(BITMAP * buffer, BITMAP * stage, BITMAP * logo, BITMAP * background, BITMAP * game_over, Player * player_1, Player * player_2, Player * player, Note * ancre) {

    destroy_bitmap(buffer);
    destroy_bitmap(stage);
    destroy_bitmap(logo);
    destroy_bitmap(background);
    free(player_1);
    free(player_2);
    free(player);

    Note * current = ancre;
    while (current->next != NULL) {
        Note * tmp = current;
        free(tmp);
        current = current->next;
    }
}


Note * allouer_note(Note * note, int x, int color) {
    note->x = x;
    note->y = 0;
    note->y_speed = 4;
    note->color = color;
    note->alive = 1;
    note->next = NULL;
    return note;
}


void play_guitar(Note * note, int positions[4], SAMPLE * music) {
    if (key[KEY_D] && note->x == positions[0])
        play_sample(music,255, 128, positions[0] * 5, 1);

    if (key[KEY_F] && note->x == positions[1])
        play_sample(music,255, 128, positions[1] * 5, 1);

    if (key[KEY_J] && note->x == positions[2])
        play_sample(music,255, 128, positions[2] * 5, 1);

    if (key[KEY_K] && note->x == positions[3])
        play_sample(music,255, 128, positions[3] * 5, 1);
}


void show_start_menu_guitar_hero(BITMAP * buffer, BITMAP * title) {
    clear_bitmap(buffer);
    masked_stretch_blit(title, buffer, 0, 0, title->w, title->h, SCREEN_W/2 - title->w, SCREEN_H/2 - title->h, title->w*2, title->h*2);
    textprintf_ex(buffer, font, SCREEN_W/2 - 100, SCREEN_H/2 + 50, makecol(255, 255, 255), -1, "PRESS ENTER TO START");
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}