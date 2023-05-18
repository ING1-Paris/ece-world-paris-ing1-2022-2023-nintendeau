#include <stdio.h>
#include <time.h>
#include <allegro.h>


void dessinerRectangleBleu(int x, int y, int cbleu, int crouge, int compteur, int joueuractif, int* J1, int* J2, BITMAP* dessprite1 , BITMAP* dessprite2, BITMAP* dessprite3, BITMAP* dessprite4, SAMPLE* taupe_bonk){
    for (int i = 0; i < compteur; i++) {
        draw_sprite(screen, dessprite2, x, y);
        if (mouse_b) {
            if (mouse_x >= x && mouse_x <= x + 100 && mouse_y >= y && mouse_y <= y + 100) {
                play_sample(taupe_bonk, 255, 128, 1000, 0);
                draw_sprite(screen, dessprite3,x,y); //taupe touchée*
                rest(1000);
                draw_sprite(screen, dessprite4,x,y); //taupe morte
                rest(500);
                compteur = 0;
                if (joueuractif == 1) {
                    (*J1)++;
                    printf("J1 : %d\n", *J1);
                } else if (joueuractif == 2) {
                    (*J2)++;
                    printf("J2 : %d\n", *J2);
                }
            }
        }
    }
    rest(10);
    draw_sprite(screen, dessprite1 ,x,y);
}

void lancerLeDecompte(int cnoir, int cblanc) {

    rectfill(screen, 200, 40, 610, 60, cnoir);
    textprintf_ex(screen, font, 300, 40, cblanc, -1, "le jeu va commencez dans 3 ");
    rest(1000);
    rectfill(screen, 200, 40, 610, 60, cnoir);
    textprintf_ex(screen, font, 300, 40, cblanc, -1, "le jeu va commencez dans 2 ");
    rest(1000);
    rectfill(screen, 300, 40, 510, 60, cnoir);
    textprintf_ex(screen, font, 300, 40, cblanc, -1, "le jeu va commencez dans 1 ");
    rest(1000);
    rectfill(screen, 200, 40, 610, 60, cnoir);
    textprintf_ex(screen, font, 380, 40, cblanc, -1, "START ! ");
    rest(1000);
    rectfill(screen, 200, 40, 610, 60, cnoir);

}

void afficherScores(int* J1, int* J2, int cbleu, int crouge, int cblanc, int cnoir) {
    rectfill(screen, 0, 0, 800, 72, cblanc);
    rectfill(screen, 2, 2, 797, 70, cnoir);
    rectfill(screen, 8, 10, 120, 20, cbleu);
    textprintf_ex(screen, font, 10, 10, cblanc, -1, "Joueur 1 : %d",  *J1);
    rectfill(screen, 8, 20, 120, 30, crouge);
    textprintf_ex(screen, font, 10, 20, cblanc, -1, "Joueur 2 : %d",  *J2);
}

int verifierscores(int* J1, int* J2, int cblanc){
    if (*J1 > *J2) {
        textprintf_ex(screen, font, 300, 20, cblanc, -1, "Joueur 1 a gagné avec %d points", *J1);
        textprintf_ex(screen, font, 300, 40, cblanc, -1, "Joueur 2 a perdu avec %d points", *J2);
        return 1;
    } else if (*J2 > *J1) {
        textprintf_ex(screen, font, 300, 20, cblanc, -1, "Joueur 2 a gagné avec %d points", *J2);
        textprintf_ex(screen, font, 300, 40, cblanc, -1, "Joueur 1 a perdu avec %d points", *J1);
        return 2;
    } else {
        textprintf_ex(screen, font, 250, 20, cblanc, -1, "Egalité ! Les deux joueurs ont %d points", *J1);
        return 3;
    }
}



int main(int argc, char *argv[]) {

    srand(time(NULL));

    allegro_init();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);

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
    BITMAP *sprite4 = load_bitmap("../Projet_2/fuite_fumée.bmp", NULL);


    BITMAP *dessprite1 = create_bitmap(150, 150);
    BITMAP *dessprite2 = create_bitmap(150, 150);
    BITMAP *dessprite3 = create_bitmap(150, 150);
    BITMAP *dessprite4 = create_bitmap(150, 150);

    if (!sprite1 || !sprite2 || !sprite3) {
        sprite1 = load_bitmap("Projet_2\\image_taupe0.bmp", NULL);
        sprite2 = load_bitmap("Projet_2\\image_taupe1.bmp", NULL);
        sprite3 = load_bitmap("Projet_2\\image_taupe2.bmp", NULL);
        sprite4 = load_bitmap("Projet_2\\fuite_fumée.bmp", NULL);
        if (!sprite1 || !sprite2 || !sprite3 || !sprite4) {
            allegro_message("prb gfx mode");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    stretch_blit(sprite1, dessprite1, 0, 0, sprite1->w, sprite1->h, 0, 0, dessprite1->w, dessprite1->h);
    stretch_blit(sprite2, dessprite2, 0, 0, sprite2->w, sprite2->h, 0, 0, dessprite2->w, dessprite2->h);
    stretch_blit(sprite3, dessprite3, 0, 0, sprite3->w, sprite3->h, 0, 0, dessprite3->w, dessprite3->h);
    stretch_blit(sprite4, dessprite4, 0, 0, sprite4->w, sprite4->h, 0, 0, dessprite4->w, dessprite4->h);

    SAMPLE *son1 = load_sample("../Projet_2/taupe_fond.wav");// ajouter fond sonore
    SAMPLE *son2 = load_sample("../Projet_2/taupe_arrivé.wav");// son quand la taupe arrive
    SAMPLE *son3 = load_sample("../Projet_2/taupe_bonk.wav");// quand on tape la taupe
    SAMPLE *son4 = load_sample("../Projet_2/taupe_sortie.wav");// quand la taupe sort

    //play_sample( son1, 255, 128, 1000, 6);// jouer le son 1 (fond sonore)

    int cvert = makecol(34, 177, 76) , cbleu = makecol(0, 0, 255),cblanc = makecol(255, 255, 255),cnoir = makecol(0,0,0), crouge = makecol(255, 0, 0),nbrdetours = 0,joueuractif = 1;
    int gagnant = 0;
    int J1 = 0;
    int J2 = 0;

    int *pJ1 = &J1;
    int *pJ2 = &J2;

    rectfill(screen, 0, 0, 800, 600, cvert);
    afficherScores(pJ1, pJ2, cbleu, crouge, cblanc, cnoir);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            draw_sprite(screen, dessprite1 ,120 + i * 200, 80 + j * 150);
        }
    }
    textprintf_ex(screen, font, 270, 10, cblanc, -1, "BIENVENUE DANS LE JEU TAPE TAUPE");
    textprintf_ex(screen, font, 270, 40, cblanc, -1, "Le joueur 1 ce prépare pour jouer");
    rest(5000);
    lancerLeDecompte(cnoir, cblanc);

    while(joueuractif != 3){

        int rectbleu = rand() % 9 + 1;
        int tempsderepos = rand() % 600 + 500;
        int compteur = rand () % 500 + 600;

        // temps de repos entre chaque rectangle bleu entre 500 et 1000 ms
        rest (tempsderepos);

        //affichage du nbr de tours
        nbrdetours++;
        printf("nbr de tours : %d\n", nbrdetours);

        //affichage des rectangles bleus (taupe qui sortent)
        if (rectbleu == 1) {
            printf("rectbleu vaut 1\n");
            dessinerRectangleBleu(120, 80, cbleu, crouge, compteur, joueuractif, pJ1, pJ2,dessprite1, dessprite2, dessprite3, dessprite4, son3);
        }else if (rectbleu == 2) {
            printf("rectbleu vaut 2\n");
            dessinerRectangleBleu(320, 80, cbleu, crouge, compteur, joueuractif, pJ1, pJ2,dessprite1, dessprite2, dessprite3, dessprite4, son3);
        }else if (rectbleu == 3) {
            printf("rectbleu vaut 3\n");
            dessinerRectangleBleu(520, 80, cbleu, crouge, compteur, joueuractif, pJ1, pJ2,dessprite1, dessprite2, dessprite3, dessprite4,  son3);
        }else if (rectbleu == 4) {
            printf("rectbleu vaut 4\n");
            dessinerRectangleBleu(120, 230, cbleu, crouge, compteur, joueuractif, pJ1, pJ2,dessprite1, dessprite2, dessprite3, dessprite4, son3);
        }else if (rectbleu == 5) {
            printf("rectbleu vaut 5\n");
            dessinerRectangleBleu(320, 230, cbleu, crouge, compteur, joueuractif, pJ1, pJ2, dessprite1,dessprite2, dessprite3, dessprite4,  son3);
        }else if (rectbleu == 6) {
            printf("rectbleu vaut 6\n");
            dessinerRectangleBleu(520, 230, cbleu, crouge, compteur, joueuractif, pJ1, pJ2,dessprite1, dessprite2, dessprite3, dessprite4, son3);
        }else if (rectbleu == 7) {
            printf("rectbleu vaut 7\n");
            dessinerRectangleBleu(120, 380, cbleu, crouge, compteur, joueuractif, pJ1, pJ2,dessprite1, dessprite2, dessprite3, dessprite4, son3);
        }else if (rectbleu == 8) {
            printf("rectbleu vaut 8\n");
            dessinerRectangleBleu(320, 380, cbleu, crouge, compteur, joueuractif, pJ1, pJ2,dessprite1, dessprite2, dessprite3, dessprite4, son3);
        }else if (rectbleu == 9) {
            printf("rectbleu vaut 9\n");
            dessinerRectangleBleu(520, 380, cbleu, crouge, compteur, joueuractif, pJ1, pJ2, dessprite1,dessprite2, dessprite3, dessprite4, son3);

        }
        //verification du nbr de tours pour changer de joueur
        if (nbrdetours == 15) {
            joueuractif = 2;
            textprintf_ex(screen, font, 310, 40, cblanc, -1, "Joueur 1 a %d points", J1);
            textprintf_ex(screen, font, 270, 60, cblanc, -1, "Joueur 2 ce prépare pour jouer");
            rest(5000);
            lancerLeDecompte(cnoir, cblanc);
        } else if (nbrdetours == 30) {
            joueuractif = 3;
        }
        //affichage des scores
        afficherScores(pJ1, pJ2, cbleu, crouge, cblanc,cnoir);
    }

    //affichage des scores finaux
    gagnant = verifierscores(pJ1, pJ2, cblanc);
    rest (3000) ;
    rectfill(screen, 290, 15, 600, 50, cnoir);
    if (gagnant == 1) {
        textprintf_ex(screen, font, 300, 40, cblanc, -1, "Joueur 1 a gagné 1 ticket");
    } else if (gagnant == 2) {
        textprintf_ex(screen, font, 300, 40, cblanc, -1, "Joueur 2 a gagné 1 ticket");
    }
    
    readkey();
    allegro_exit();
    EXIT_SUCCESS;
}
END_OF_MAIN();
