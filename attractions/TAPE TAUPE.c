#include <stdio.h>
#include <time.h>
#include <allegro.h>


void dessinerRectangleBleu(int x, int y, int cbleu, int crouge, int compteur, int joueuractif, int* J1, int* J2, BITMAP* dessprite2, BITMAP* dessprite3){
    for (int i = 0; i < compteur; i++) {
        draw_sprite(screen, dessprite2, x, y);
        if (mouse_b) {
            if (mouse_x >= x && mouse_x <= x + 100 && mouse_y >= y && mouse_y <= y + 100) {
                draw_sprite(screen, dessprite3,x,y); //taupe touchée
                rest(500);
                compteur = 0;
                if (joueuractif == 1) {
                    J1++;
                } else if (joueuractif == 2) {
                    J2++;
                }
            }
        }
    }
}

void lancerLeDecompte(int cvert, int cblanc) {

    rectfill(screen, 0, 0, 800, 600, cvert);
    textprintf_ex(screen, font, 300, 300, cblanc, -1, "le jeu va commencez dans 3 ");
    rest(1000);
    rectfill(screen, 300, 300, 510, 320, cvert);
    textprintf_ex(screen, font, 300, 300, cblanc, -1, "le jeu va commencez dans 2 ");
    rest(1000);
    rectfill(screen, 300, 300, 510, 320, cvert);
    textprintf_ex(screen, font, 300, 300, cblanc, -1, "le jeu va commencez dans 1 ");
    rest(1000);
    rectfill(screen, 300, 300, 510, 320, cvert);
    textprintf_ex(screen, font, 380, 300, cblanc, -1, "START ! ");
    rest(1000);
    rectfill(screen, 300, 300, 510, 320, cvert);

}

void afficherScores(int* J1, int* J2, int cbleu, int crouge, int cblanc) {
    rectfill(screen, 8, 10, 110, 20, cbleu);
    textprintf_ex(screen, font, 10, 10, cblanc, -1, "Joueur 1 : %d",  J1);
    rectfill(screen, 8, 20, 110, 30, crouge);
    textprintf_ex(screen, font, 10, 20, cblanc, -1, "Joueur 2 : %d",  J2);
}

int verifierscores(int* J1, int* J2, int cblanc){
    if (J1 > J2) {
        textprintf_ex(screen, font, 300, 300, cblanc, -1, "Joueur 1 a gagné avec %d points", J1);
        textprintf_ex(screen, font, 300, 300, cblanc, -1, "Joueur 2 a perdu avec %d points", J2);
        return 1;
    } else if (J2 > J1) {
        textprintf_ex(screen, font, 300, 300, cblanc, -1, "Joueur 2 a gagné avec %d points", J2);
        textprintf_ex(screen, font, 300, 300, cblanc, -1, "Joueur 1 a perdu avec %d points", J1);
        return 2;
    } else {
        textprintf_ex(screen, font, 250, 300, cblanc, -1, "Egalité ! Les deux joueurs ont %d points", J1);
        return 3;
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

    BITMAP *sprite1 = load_bitmap("../Projet_2/image_taupe0.bmp", NULL);
    BITMAP *sprite2 = load_bitmap("../Projet_2/image_taupe1.bmp", NULL);
    BITMAP *sprite3 = load_bitmap("../Projet_2/image_taupe2.bmp", NULL);


    BITMAP *dessprite1 = create_bitmap(150, 150);
    BITMAP *dessprite2 = create_bitmap(150, 150);
    BITMAP *dessprite3 = create_bitmap(150, 150);

    if (!sprite1 || !sprite2 || !sprite3) {
        sprite1 = load_bitmap("Projet_2\\image_taupe0.bmp", NULL);
        sprite2 = load_bitmap("Projet_2\\image_taupe1.bmp", NULL);
        sprite3 = load_bitmap("Projet_2\\image_taupe2.bmp", NULL);
        if (!sprite1 || !sprite2 || !sprite3) {
            allegro_message("prb gfx mode");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    stretch_blit(sprite1, dessprite1, 0, 0, sprite1->w, sprite1->h, 0, 0, dessprite1->w, dessprite1->h);
    stretch_blit(sprite2, dessprite2, 0, 0, sprite2->w, sprite2->h, 0, 0, dessprite2->w, dessprite2->h);
    stretch_blit(sprite3, dessprite3, 0, 0, sprite3->w, sprite3->h, 0, 0, dessprite3->w, dessprite3->h);

    int cvert = makecol(34, 177, 76) , cbleu = makecol(0, 0, 255),cblanc = makecol(255, 255, 255), crouge = makecol(255, 0, 0),nbrdetours = 0,joueuractif = 1;
    int gagnant = 0;
    int* J1 = 0;
    int* J2 = 0;

    rectfill(screen, 0, 0, 800, 600, cvert);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            draw_sprite(screen, dessprite1 ,120 + i * 200, 80 + j * 150);
        }
    }
    textprintf_ex(screen, font, 290, 300, cblanc, -1, "Le joueur 1 ce prépare pour jouer");
    rest(5000);
    lancerLeDecompte(cvert, cblanc);

    while(joueuractif != 3){

        int rectbleu = rand() % 12 + 1;
        int tempsderepos = rand() % 500 + 500;
        int compteur = rand () % 6000 + 4000;

        //création des rectangles verts
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                draw_sprite(screen, dessprite1 ,120 + i * 200, 80 + j * 150);
            }
        }
        //verification du nbr de tours pour changer de joueur
        if (nbrdetours == 15) {
            joueuractif = 2;
            textprintf_ex(screen, font, 310, 300, cblanc, -1, "Joueur 1 a %d points", J1);
            textprintf_ex(screen, font, 270, 270, cblanc, -1, "Joueur 2 ce prépare pour jouer", J2);
            rest(5000);
            lancerLeDecompte(cvert, cblanc);
        } else if (nbrdetours == 30) {
            joueuractif = 3;
        }

        // temps de repos entre chaque rectangle bleu entre 500 et 1000 ms
        rest (tempsderepos);

        //affichage du nbr de tours
        nbrdetours++;
        printf("nbr de tours : %d\n", nbrdetours);

        //affichage des scores
        afficherScores(J1, J2, cbleu, crouge, cblanc);

        //affichage des rectangles bleus (taupe qui sortent)
        if (rectbleu == 1) {
            printf("rectbleu vaut 1\n");
            dessinerRectangleBleu(120, 80, cbleu, crouge, compteur, joueuractif, J1, J2, dessprite2, dessprite3);
        }else if (rectbleu == 2) {
            printf("rectbleu vaut 2\n");
            dessinerRectangleBleu(320, 80, cbleu, crouge, compteur, joueuractif, J1, J2, dessprite2, dessprite3);
        }else if (rectbleu == 3) {
            printf("rectbleu vaut 3\n");
            dessinerRectangleBleu(520, 80, cbleu, crouge, compteur, joueuractif, J1, J2, dessprite2, dessprite3);
        }else if (rectbleu == 4) {
            printf("rectbleu vaut 4\n");
            dessinerRectangleBleu(120, 230, cbleu, crouge, compteur, joueuractif, J1, J2, dessprite2, dessprite3);
        }else if (rectbleu == 5) {
            printf("rectbleu vaut 5\n");
            dessinerRectangleBleu(320, 230, cbleu, crouge, compteur, joueuractif, J1, J2, dessprite2, dessprite3);
        }else if (rectbleu == 6) {
            printf("rectbleu vaut 6\n");
            dessinerRectangleBleu(520, 230, cbleu, crouge, compteur, joueuractif, J1, J2, dessprite2, dessprite3);
        }else if (rectbleu == 7) {
            printf("rectbleu vaut 7\n");
            dessinerRectangleBleu(120, 380, cbleu, crouge, compteur, joueuractif, J1, J2, dessprite2, dessprite3);
        }else if (rectbleu == 8) {
            printf("rectbleu vaut 8\n");
            dessinerRectangleBleu(320, 380, cbleu, crouge, compteur, joueuractif, J1, J2, dessprite2, dessprite3);
        }else if (rectbleu == 9) {
            printf("rectbleu vaut 9\n");
            dessinerRectangleBleu(520, 380, cbleu, crouge, compteur, joueuractif, J1, J2, dessprite2, dessprite3);

        }
    }

    //affichage des scores finaux
    gagnant = verifierscores(J1, J2, cblanc);
    readkey();
    allegro_exit();
    EXIT_SUCCESS;
}
END_OF_MAIN();
