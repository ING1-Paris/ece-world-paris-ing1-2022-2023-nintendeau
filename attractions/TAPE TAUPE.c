#include <stdio.h>
#include <time.h>
#include <allegro.h>


typedef struct {
    int scoreJ1;
    int scoreJ2;
} ScoreJoueurs;

void dessinerRectangleBleu(int x, int y, int cbleu, int crouge, ScoreJoueurs * scores, int compteur, int joueuractif) {
    for (int i = 0; i < compteur; i++) {
        rectfill(screen, x, y, x + 100, y + 100, cbleu);
        if (mouse_b) {
            if (mouse_x >= x && mouse_x <= x + 100 && mouse_y >= y && mouse_y <= y + 100) {
                printf("bouton de la souris enfoncé\n");
                if (joueuractif == 1) scores->scoreJ1++;
                else if (joueuractif == 2) scores->scoreJ2++;
                rectfill(screen, x, y, x + 100, y + 100, crouge);
                rest(500);
                compteur = 0;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0) != 0) {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);

    int cvert = makecol(0, 255, 0) , cbleu = makecol(0, 0, 255),cblanc = makecol(255, 255, 255), crouge = makecol(255, 0, 0);
    int fin=0;
    int scoreJ1 = 0, scoreJ2 = 0, nbrTicket = 5;
    int tempsBleu = 0;

    ScoreJoueurs * scores;
    scores->scoreJ1 = 0;
    scores->scoreJ2 = 0;

    int joueuractif = 1;

    while(!fin){

        rectfill(screen, 8, 10, 110, 20, cbleu);
        textprintf_ex(screen, font, 10, 10, cblanc, -1, "Joueur 1 : %d", scores->scoreJ1);
        rectfill(screen, 8, 20, 110, 30, crouge);
        textprintf_ex(screen, font, 10, 20, cblanc, -1, "Joueur 2 : %d", scores->scoreJ2);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                rectfill(screen, 130 + i * 150, 100 + j * 150, 130 + i * 150 + 100, 100 + j * 150 + 100, cvert);
            }
        }
        int rectbleu = rand() % 12 + 1;
        int tempsderepos = rand() % 500 + 500;
        int compteur = rand () % 6000 + 4000;
        rest (tempsderepos);
        if (rectbleu == 1) {
            printf("rectbleu vaut 1\n");
            dessinerRectangleBleu(130, 100, cbleu, crouge, scores, compteur, joueuractif);
        }else if (rectbleu == 2) {
            printf("rectbleu vaut 2\n");
            dessinerRectangleBleu(280, 100, cbleu, crouge, scores, compteur, joueuractif);
        }else if (rectbleu == 3) {
            printf("rectbleu vaut 3\n");
            dessinerRectangleBleu(430, 100, cbleu, crouge, scores, compteur, joueuractif);
        }else if (rectbleu == 4) {
            printf("rectbleu vaut 4\n");
            dessinerRectangleBleu(580, 100, cbleu, crouge, scores, compteur, joueuractif);
        }else if (rectbleu == 5) {
            printf("rectbleu vaut 5\n");
            dessinerRectangleBleu(130, 250, cbleu, crouge, scores, compteur, joueuractif);
        }else if (rectbleu == 6) {
            printf("rectbleu vaut 6\n");
            dessinerRectangleBleu(280, 250, cbleu, crouge, scores, compteur, joueuractif);
        }else if (rectbleu == 7) {
            printf("rectbleu vaut 7\n");
            dessinerRectangleBleu(430, 250, cbleu, crouge, scores, compteur, joueuractif);
        }else if (rectbleu == 8) {
            printf("rectbleu vaut 8\n");
            dessinerRectangleBleu(580, 250, cbleu, crouge, scores, compteur, joueuractif);
        }else if (rectbleu == 9) {
            printf("rectbleu vaut 9\n");
            dessinerRectangleBleu(130, 400, cbleu, crouge, scores, compteur, joueuractif);
        }else if (rectbleu == 10) {
            printf("rectbleu vaut 10\n");
            dessinerRectangleBleu(280, 400, cbleu, crouge, scores, compteur, joueuractif);
        }else if (rectbleu == 11) {
            printf("rectbleu vaut 11\n");
            dessinerRectangleBleu(430, 400, cbleu, crouge, scores, compteur, joueuractif);
        }else if (rectbleu == 12) {
            printf("rectbleu vaut 12\n");
            dessinerRectangleBleu(580, 400, cbleu, crouge, scores, compteur, joueuractif);
        }
    }
}
END_OF_MAIN();
