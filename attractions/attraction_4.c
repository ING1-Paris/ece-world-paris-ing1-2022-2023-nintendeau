#include <stdio.h>
#include <time.h>
#include <allegro.h>

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

    while(!fin){
        textprintf_ex(screen, font, 10, 10, cblanc, -1, "Joueur 1 : %d", scoreJ1);
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
            for (int i = 0; i < compteur; i++){
                rectfill(screen, 130, 100, 130 + 100, 100 + 100, cbleu);
                if (mouse_b) {
                    if (mouse_x >= 130 && mouse_x <= 230 && mouse_y >= 100 && mouse_y <= 200) {
                        printf("bouton de la souris enfoncé\n");
                        scoreJ1++;
                        rectfill(screen, 130, 100, 130 + 100, 100 + 100, crouge);
                        rest(500);
                        compteur = 0;
                    }
                }
            }
        }else if (rectbleu == 2) {
            printf("rectbleu vaut 2\n");
            for (int i = 0; i < compteur; i++){
                rectfill(screen, 280, 100, 280 + 100, 100 + 100, cbleu);
                if (mouse_b) {
                    if (mouse_x >= 280 && mouse_x <= 380 && mouse_y >= 100 && mouse_y <= 200) {
                        printf("bouton de la souris enfoncé\n");
                        scoreJ1++;
                        rectfill(screen, 280, 100, 280 + 100, 100 + 100, crouge);
                        rest(500);
                        compteur = 0;
                    }
                }
            }
        }else if (rectbleu == 3) {
            printf("rectbleu vaut 3\n");
            for (int i = 0; i < compteur; i++){
                rectfill(screen, 430, 100, 430 + 100, 100 + 100, cbleu);
                if (mouse_b) {
                    if (mouse_x >= 430 && mouse_x <= 530 && mouse_y >= 100 && mouse_y <= 200) {
                        printf("bouton de la souris enfoncé\n");
                        scoreJ1++;
                        rectfill(screen, 430, 100, 430 + 100, 100 + 100, crouge);
                        rest(500);
                        compteur = 0;
                    }
                }
            }
        }else if (rectbleu == 4) {
            printf("rectbleu vaut 4\n");
            for (int i = 0; i < compteur; i++){
                rectfill(screen, 580, 100, 580 + 100, 100 + 100, cbleu);
                if (mouse_b) {
                    if (mouse_x >= 580 && mouse_x <= 680 && mouse_y >= 100 && mouse_y <= 200) {
                        printf("bouton de la souris enfoncé\n");
                        scoreJ1++;
                        rectfill(screen, 580, 100, 580 + 100, 100 + 100, crouge);
                        rest(500);
                        compteur = 0;
                    }
                }
            }
        }else if (rectbleu == 5) {
            printf("rectbleu vaut 5\n");
            for (int i = 0; i < compteur; i++){
                rectfill(screen, 130, 250, 130 + 100, 250 + 100, cbleu);
                if (mouse_b) {
                    if (mouse_x >= 130 && mouse_x <= 230 && mouse_y >= 250 && mouse_y <= 350) {
                        printf("bouton de la souris enfoncé\n");
                        scoreJ1++;
                        rectfill(screen, 130, 250, 130 + 100, 250 + 100, crouge);
                        rest(500);
                        compteur = 0;
                    }
                }
            }
        }else if (rectbleu == 6) {
            printf("rectbleu vaut 6\n");
            for (int i = 0; i < compteur; i++){
                rectfill(screen, 280, 250, 280 + 100, 250 + 100, cbleu);
                if (mouse_b) {
                    if (mouse_x >= 280 && mouse_x <= 380 && mouse_y >= 250 && mouse_y <= 350) {
                        printf("bouton de la souris enfoncé\n");
                        scoreJ1++;
                        rectfill(screen, 280, 250, 280 + 100, 250 + 100, crouge);
                        rest(500);
                        compteur = 0;
                    }
                }
            }
        }else if (rectbleu == 7) {
            printf("rectbleu vaut 7\n");
            for (int i = 0; i < compteur; i++){
                rectfill(screen, 430, 250, 430 + 100, 250 + 100, cbleu);
                if (mouse_b) {
                    if (mouse_x >= 430 && mouse_x <= 530 && mouse_y >= 250 && mouse_y <= 350) {
                        printf("bouton de la souris enfoncé\n");
                        scoreJ1++;
                        rectfill(screen, 430, 250, 430 + 100, 250 + 100, crouge);
                        rest(500);
                        compteur = 0;
                    }
                }
            }
        }else if (rectbleu == 8) {
            printf("rectbleu vaut 8\n");
            for (int i = 0; i < compteur; i++){
                rectfill(screen, 580, 250, 580 + 100, 250 + 100, cbleu);
                if (mouse_b) {
                    if (mouse_x >= 580 && mouse_x <= 680 && mouse_y >= 250 && mouse_y <= 350) {
                        printf("bouton de la souris enfoncé\n");
                        scoreJ1++;
                        rectfill(screen, 580, 250, 580 + 100, 250 + 100, crouge);
                        rest(500);
                        compteur = 0;
                    }
                }
            }
        }else if (rectbleu == 9) {
            printf("rectbleu vaut 9\n");
            for (int i = 0; i < compteur; i++){
                rectfill(screen, 130, 400, 130 + 100, 400 + 100, cbleu);
                if (mouse_b) {
                    if (mouse_x >= 130 && mouse_x <= 230 && mouse_y >= 400 && mouse_y <= 500) {
                        printf("bouton de la souris enfoncé\n");
                        scoreJ1++;
                        rectfill(screen, 130, 400, 130 + 100, 400 + 100, crouge);
                        rest(500);
                        compteur = 0;
                    }
                }
            }
        }else if (rectbleu == 10) {
            printf("rectbleu vaut 10\n");
            for (int i = 0; i < compteur; i++){
                rectfill(screen, 280, 400, 280 + 100, 400 + 100, cbleu);
                if (mouse_b) {
                    if (mouse_x >= 280 && mouse_x <= 380 && mouse_y >= 400 && mouse_y <= 500) {
                        printf("bouton de la souris enfoncé\n");
                        scoreJ1++;
                        rectfill(screen, 280, 400, 280 + 100, 400 + 100, crouge);
                        rest(500);
                        compteur = 0;
                    }
                }
            }
        }else if (rectbleu == 11) {
            printf("rectbleu vaut 11\n");
            for (int i = 0; i < compteur; i++){
                rectfill(screen, 430, 400, 430 + 100, 400 + 100, cbleu);
                if (mouse_b) {
                    if (mouse_x >= 430 && mouse_x <= 530 && mouse_y >= 400 && mouse_y <= 500) {
                        printf("bouton de la souris enfoncé\n");
                        scoreJ1++;
                        rectfill(screen, 430, 400, 430 + 100, 400 + 100, crouge);
                        rest(500);
                        compteur = 0;
                    }
                }
            }
        }else if (rectbleu == 12) {
            printf("rectbleu vaut 12\n");
            for (int i = 0; i < compteur; i++){
                rectfill(screen, 580, 400, 580 + 100, 400 + 100, cbleu);
                if (mouse_b) {
                    if (mouse_x >= 580 && mouse_x <= 680 && mouse_y >= 400 && mouse_y <= 500) {
                        printf("bouton de la souris enfoncé\n");
                        scoreJ1++;
                        rectfill(screen, 580, 400, 580 + 100, 400 + 100, crouge);
                        rest(500);
                        compteur = 0;
                    }
                }
            }
        }
    }
}
END_OF_MAIN();
