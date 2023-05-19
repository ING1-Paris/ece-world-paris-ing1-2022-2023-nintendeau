#include <allegro.h>
#include <time.h>
#include <stdbool.h>

#define SCREEN_W 640
#define SCREEN_H 480
#define FPS 60

#define LARGEUROBSTACLE 80
#define DISTANCE 200 //correspond à la taille de l'obstacle
#define TAILLEOISEAU 30 //correspond à la taille de l'oiseau
#define GRAVITE 2.5
#define SAUT 15

int main() {
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0);
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

    srand(time(NULL));

    //importation des images et création du double buffer


    BITMAP *decor = load_bitmap("../images/decor.bmp", NULL); // charger le bitmap du décor
    BITMAP *oiseau1 = load_bitmap("../images/joueur1.bmp", NULL); // charger le bitmap du bird 1
    BITMAP *oiseau2 = load_bitmap("../images/joueur2.bmp", NULL); // charger le bitmap du bird 2
    BITMAP *obstaclehaut = load_bitmap("../images/obstacle_haut.bmp", NULL); // charger le bitmap de l'obstacle supérieur
    BITMAP *obstaclebas = load_bitmap("../images/obstacle_bas.bmp", NULL); // charger le bitmap de l'obstacle inférieur
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H); // crée un double buffer
    BITMAP *cloud = load_bitmap("../images/cloud.bmp", NULL); // charger le bitmap du nuage
    SAMPLE *saut = load_sample("../son/saut.wav"); // charger le son du saut
    SAMPLE *collision = load_sample("../son/collision.wav"); // charger le son du game over
    SAMPLE *scoreincremente = load_sample("../son/scoreincremente.wav"); // charger le son du score

    int oiseau1_x = SCREEN_W / 4 - TAILLEOISEAU / 2;
    int oiseau1_y = SCREEN_H / 2 - TAILLEOISEAU / 2;
    int vitesse1 = 0;

    int oiseau2_x = SCREEN_W * 3 / 4 - TAILLEOISEAU / 2;
    int oiseau2_y = SCREEN_H / 2 - TAILLEOISEAU / 2;
    int vitesse2 = 0;

    int tuyau = SCREEN_W;
    int obstacle_haut = SCREEN_H / 2 - DISTANCE / 2;
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
                tuyau = SCREEN_W;
                obstacle_haut = rand() % (SCREEN_H - DISTANCE);
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
            if (!game_over1 && oiseau1_y + TAILLEOISEAU >= SCREEN_H) {
                game_over1 = true;
                play_sample(collision, 255, 128, 1000, 0);
            }
            if (!game_over2 && oiseau2_y + TAILLEOISEAU >= SCREEN_H) {
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

        textprintf_right(buffer, font, SCREEN_W - 10, 10, makecol(255, 255, 255), "Player 1: %d", score1);
        textprintf_right(buffer, font, SCREEN_W - 10, 30, makecol(255, 255, 0), "Player 2: %d", score2);

        //dessiner le message de début de jeu sur le buffer

        if (!game_started) {
            BITMAP *menufloppybird = load_bitmap("../images/menufloppybird.bmp", NULL);
            draw_sprite(buffer, menufloppybird, 0, 0);
            rest(1000 / FPS);
            clear(menufloppybird);
        }
        if (game_over1 && game_over2) {
            if(score1 > score2){
                rest(2000);
                allegro_message("Le joueur 1 gagne !");


            } else if(score1 < score2){
                rest(2000);
                allegro_message("Le joueur 2 gagne !");

            } else {
                rest(2000);
                allegro_message("Egalité !");
            }
            gameovergeneral = true;
        }


        //copier le buffer sur l'écran

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
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
END_OF_MAIN();
