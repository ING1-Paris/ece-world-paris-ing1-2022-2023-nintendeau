#include <allegro.h>
#include <time.h>
#include <stdbool.h>

#include "../header/flappy_bird.h"
#include "../header/loader.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 60

#define LARGEUROBSTACLE 80
#define DISTANCE 200 //correspond à la taille de l'obstacle
#define TAILLEOISEAU 30 //correspond à la taille de l'oiseau
#define GRAVITE 2.5
#define SAUT 15

int flappy_bird(char * nom1, char * nom2) {
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    srand(time(NULL));

    //importation des images et création du double buffer


    //importation des images et création du double buffer
    BITMAP *decor = image_loader("attractions/assets/flappy_bird/images/decor.bmp"); // charger le bitmap du décor
    BITMAP *oiseau1 = image_loader("attractions/assets/flappy_bird/images/joueur1.bmp"); // charger le bitmap du bird 1
    BITMAP *oiseau2 = image_loader("attractions/assets/flappy_bird/images/joueur2.bmp"); // charger le bitmap du bird 2
    BITMAP *obstaclehaut = image_loader("attractions/assets/flappy_bird/images/obstacle_haut.bmp"); // charger le bitmap de l'obstacle supérieur
    BITMAP *obstaclebas = image_loader("attractions/assets/flappy_bird/images/obstacle_bas.bmp"); // charger le bitmap de l'obstacle inférieur
    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT); // crée un double buffer
    BITMAP *cloud = image_loader("attractions/assets/flappy_bird/images/cloud.bmp"); // charger le bitmap du nuage
    SAMPLE *saut = sound_loader("attractions/assets/flappy_bird/son/saut.wav"); // charger le son du saut
    SAMPLE *collision = sound_loader("attractions/assets/flappy_bird/son/collision.wav"); // charger le son de la collision
    SAMPLE *scoreincremente = sound_loader("attractions/assets/flappy_bird/son/scoreincremente.wav"); // charger le son de l'incrémentation du score

    int oiseau1_x = SCREEN_WIDTH / 4 - TAILLEOISEAU / 2;
    int oiseau1_y = SCREEN_HEIGHT / 2 - TAILLEOISEAU / 2;
    int vitesse1 = 0;

    int oiseau2_x = SCREEN_WIDTH * 3 / 4 - TAILLEOISEAU / 2;
    int oiseau2_y = SCREEN_HEIGHT / 2 - TAILLEOISEAU / 2;
    int vitesse2 = 0;

    int tuyau = SCREEN_WIDTH;
    int obstacle_haut = SCREEN_HEIGHT / 2 - DISTANCE / 2;
    int obstacle_bas = obstacle_haut + DISTANCE;

    int score1 = 0;
    int score2 = 0;

    bool game_started = false;
    bool game_over1 = false;
    bool game_over2 = false;
    bool gameovergeneral = false; //variable qui permet de quitter le jeu sans se prendre 10000 allegro_message()

    while (!key[KEY_ESC] && gameovergeneral == false) {
        if (!game_started && key[KEY_P]) { //si on appuie sur P, le jeu commence
        game_started = true;
        }

        if (game_started) {
            if (!game_over1 && oiseau1_y > 0 && key[KEY_SPACE]) {
                vitesse1 = -SAUT;
                play_sample(saut, 255, 128, 1000, 0);
                rotate_sprite(buffer, oiseau1, oiseau1_x, oiseau1_y, itofix(-64));
            }
            if (!game_over2 && oiseau2_y > 0 && key[KEY_ENTER]) {
                vitesse2 = -SAUT;
                play_sample(saut, 255, 100, 1000, 0);
            }

            //bouger l'obstacle vers la gauche et le faire réapparaitre à droite
            tuyau -= 5;
            if (tuyau < -LARGEUROBSTACLE) {
                tuyau = SCREEN_WIDTH;
                obstacle_haut = rand() % (SCREEN_HEIGHT - DISTANCE);
                obstacle_bas = obstacle_haut + DISTANCE;
            }

            //bouger l'oiseau 1

            vitesse1 += GRAVITE;
            oiseau1_y += vitesse1;


            //bouger l'oiseau 2

            vitesse2 += GRAVITE;
            oiseau2_y += vitesse2;


            //verifier les collisions avec les tuyaux

            if (!game_over1 && ((oiseau1_x + TAILLEOISEAU >= tuyau && oiseau1_x <= tuyau + LARGEUROBSTACLE) &&
                                (oiseau1_y <= obstacle_haut || oiseau1_y + TAILLEOISEAU >= obstacle_bas))) {
                game_over1 = true;
                play_sample(collision, 255, 128, 1000, 0);

            }
            if (!game_over2 && ((oiseau2_x + TAILLEOISEAU >= tuyau && oiseau2_x <= tuyau + LARGEUROBSTACLE) &&
                                (oiseau2_y <= obstacle_haut || oiseau2_y + TAILLEOISEAU >= obstacle_bas))) {
                game_over2 = true;
                play_sample(collision, 255, 100, 1000, 0);
            }

            //verifier les collisions avec le sol
            if (!game_over1 && oiseau1_y + TAILLEOISEAU >= SCREEN_HEIGHT) {
                game_over1 = true;
                play_sample(collision, 255, 128, 1000, 0);
            }
            if (!game_over2 && oiseau2_y + TAILLEOISEAU >= SCREEN_HEIGHT) {
                game_over2 = true;
                play_sample(collision, 255, 100, 1000, 0);
            }

            //mettre à jour les scores si les oiseaux ont passé les obstacles
            if (tuyau + LARGEUROBSTACLE == oiseau1_x && !game_over1) {
                score1++;
                play_sample(scoreincremente, 255, 128, 1000, 0);
            }
            if (tuyau + LARGEUROBSTACLE == oiseau2_x && !game_over2) {
                score2++;
                play_sample(scoreincremente, 255, 100, 1000, 0);
            }
        }

        //dessiner le fond sur le buffer

        clear_to_color(buffer, makecol(0, 0, 0));

        //dessiner les images sur le buffer

        draw_sprite(buffer, decor, 0, 0);

        //dessiner les obstacles sur le buffer

        draw_sprite(buffer, obstaclehaut, tuyau, obstacle_haut - DISTANCE);
        draw_sprite(buffer, obstaclebas, tuyau, obstacle_bas);

        //dessiner les oiseaux sur le buffer

        draw_sprite(buffer, oiseau1, oiseau1_x, oiseau1_y);

        //dessiner les oiseaux sur le buffer

        draw_sprite(buffer, oiseau2, oiseau2_x, oiseau2_y);

        //dessiner le nuage sur le buffer
        draw_sprite(buffer, cloud, 0, 0);

        //dessiner les scores sur le buffer

        textprintf_right(buffer, font, SCREEN_WIDTH - 10, 10, makecol(255, 255, 255), "Player 1: %d", score1);
        textprintf_right(buffer, font, SCREEN_WIDTH - 10, 30, makecol(255, 255, 0), "Player 2: %d", score2);

        //dessiner le message de début de jeu sur le buffer

        if (!game_started) {
            BITMAP *menufloppybird = image_loader("attractions/assets/flappy_bird/images/menufloppybird.bmp");
            draw_sprite(buffer, menufloppybird, 0, 0);
            rest(1000 / FPS);
            clear(menufloppybird);
        }
        if (game_over1 && game_over2) {
            if(score1 > score2){
                rest(2000);
                allegro_message(" %s a gagné !", nom1);
                return 1;

            } else if(score1 < score2){
                rest(2000);
                allegro_message("%s a gagné !", nom2);
                return 2;
            } else {
                rest(2000);
                allegro_message("Egalité !");
                return 0;
            }
            gameovergeneral = true;
        }


        //copier le buffer sur l'écran

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        rest(1000 / FPS);
    }

    destroy_bitmap(decor);
    destroy_bitmap(oiseau1);
    destroy_bitmap(oiseau2);
    destroy_bitmap(obstaclehaut);
    destroy_bitmap(obstaclebas);
    destroy_bitmap(buffer);

    return 0;
}
