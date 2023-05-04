#include <stdio.h>
#include <allegro.h>
#include <time.h>

#define MAX_IMAGES_CASE 3


int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cblanc, crouge, cbleu, cnoir, cvert, cviolet;
    int v7 = 1, vviande = 2,vcoeur = 3;
    int fin;
    int nbrTicket = 5 ;

    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    show_mouse(screen);


    BITMAP *sprite1 = load_bitmap("../Projet_2/image_case/image_case0.bmp", NULL);
    BITMAP *sprite2 = load_bitmap("../Projet_2/image_case/image_case1.bmp", NULL);
    BITMAP *sprite3 = load_bitmap("../Projet_2/image_case/image_case2.bmp", NULL);
    BITMAP *sprite4 = load_bitmap("../Projet_2/point_d'interro.bmp", NULL);
    BITMAP *sprite5 = load_bitmap("../Projet_2/image_jackpot_3.bmp", NULL);

    BITMAP *dessprite1 = create_bitmap(86, 100);
    BITMAP *dessprite2 = create_bitmap(86, 100);
    BITMAP *dessprite3 = create_bitmap(86, 100);
    BITMAP *dessprite4 = create_bitmap(86, 100);

    BITMAP *dessprite5 = create_bitmap(800, 650);


    if (!sprite1 || !sprite2 || !sprite3) {
         sprite1 = load_bitmap("Projet_2\\image_case\\image_case0.bmp", NULL);
         sprite2 = load_bitmap("Projet_2\\image_case\\image_case1.bmp", NULL);
         sprite3 = load_bitmap("Projet_2\\image_case\\image_case2.bmp", NULL);
         sprite4 = load_bitmap("Projet_2\\point_d'interro.bmp", NULL);
         sprite5 = load_bitmap("Projet_2\\image_jackpot_3.bmp", NULL);
         if (!sprite1 || !sprite2 || !sprite3) {
             allegro_message("prb gfx mode");
             allegro_exit();
             exit(EXIT_FAILURE);
         }
    }
    stretch_blit(sprite1, dessprite1, 0, 0, sprite1->w, sprite1->h, 0, 0, dessprite1->w, dessprite1->h);
    stretch_blit(sprite2, dessprite2, 0, 0, sprite2->w, sprite2->h, 0, 0, dessprite2->w, dessprite2->h);
    stretch_blit(sprite3, dessprite3, 0, 0, sprite3->w, sprite3->h, 0, 0, dessprite3->w, dessprite3->h);
    stretch_blit(sprite4, dessprite4, 0, 0, sprite4->w, sprite4->h, 0, 0, dessprite4->w, dessprite4->h);
    stretch_blit(sprite5, dessprite5, 0, 0, sprite5->w, sprite5->h, 0, 0, dessprite5->w, dessprite5->h);

    cblanc=makecol(255,255,255);
    crouge=makecol(255,0,0);
    cbleu=makecol(0,0,255);
    cnoir= makecol(0,0,0);
    cvert= makecol(0,255,0);
    cviolet = makecol(163,73,164);

    fin=0;
    int dernierAppui = 0;



    draw_sprite(screen, dessprite5, 0, 0);
    draw_sprite(screen, dessprite4, 233, 273);
    draw_sprite(screen, dessprite4, 359, 273);
    draw_sprite(screen, dessprite4, 485, 273);


    textprintf_ex(screen,font,589,469,makecol(255,0,0),makecol(200,255,0),"START");
    textprintf_ex(screen, font, 300, 500, cblanc, -1, "il vous reste %d tickets", nbrTicket);

    while (!fin) {

        if (nbrTicket <= 0) {
            rectfill(screen, 300, 500, 400, 520, cviolet);
            textprintf_ex(screen, font, 300, 500, cblanc, -1, "Vous n'avez plus de tickets !");
            rest(1000);
            fin = 1;
        }
        if (mouse_b & 1 && mouse_x <= 660 && mouse_x >= 560 && mouse_y <= 490 && mouse_y >= 462) {
            if (time(NULL) - dernierAppui >= 1) {
                dernierAppui = time(NULL);

                nbrTicket = nbrTicket - 1;

                for(int i = 0 ; i < 3 ; i++) {
                    int choix = rand() % 3 + 1;
                    for (int j = 0; j < 14 ; j++){
                        if (j == 0) {
                            draw_sprite(screen, dessprite1, 233 + i * 126, 274);
                        } else if (j == 1) {
                            draw_sprite(screen, dessprite2, 233 + i * 126, 274);
                        } else if (j == 2) {
                            draw_sprite(screen, dessprite3, 233 + i * 126, 274);
                        } else if (j == 3) {
                            draw_sprite(screen, dessprite1, 233 + i * 126, 274);
                        } else if (j == 4) {
                            draw_sprite(screen, dessprite2, 233 + i * 126, 274);
                        } else if (j == 5) {
                            draw_sprite(screen, dessprite3, 233 + i * 126, 274);
                        } else if (j == 6) {
                            draw_sprite(screen, dessprite1, 233 + i * 126, 274);
                        } else if (j == 7) {
                            draw_sprite(screen, dessprite2, 233 + i * 126, 274);
                        } else if (j == 8) {
                            draw_sprite(screen, dessprite3, 233 + i * 126, 274);
                        } else if (j == 9) {
                            draw_sprite(screen, dessprite1, 233 + i * 126, 274);
                        } else if (j == 10) {
                            draw_sprite(screen, dessprite2, 233 + i * 126, 274);
                        } else if (j == 11) {
                            draw_sprite(screen, dessprite3, 233 + i * 126, 274);
                        } else if (j == 12) {
                            draw_sprite(screen, dessprite1, 233 + i * 126, 274);
                        } else if (j == 13) {
                            draw_sprite(screen, dessprite2, 233 + i * 126, 274);
                        }


                        rest(150);
                    }

                    if (choix == v7) {
                        draw_sprite(screen, dessprite1, 233 + i * 126, 274);
                    } else if (choix == vviande) {
                        draw_sprite(screen, dessprite2, 233 + i * 126, 274);
                    } else if (choix == vcoeur) {
                        draw_sprite(screen, dessprite3, 233 + i * 126, 274);
                    }
                }

                if (getpixel(screen, 234, 275) == cvert && getpixel(screen, 234 + 126, 274) == cvert && getpixel(screen, 234 + 2*126, 274) == cvert) {
                    rectfill(screen, 350, 45, 475, 60, cviolet);
                    textprintf_ex(screen,font,350,50,cblanc,-1,"Vous avez gagné");
                    nbrTicket = nbrTicket + 1;
                    rectfill(screen, 300, 500, 400, 520, cviolet);
                    textprintf_ex(screen, font, 300, 500, cblanc, -1, "il vous reste %d tickets", nbrTicket); // Affiche le nouveau texte

                } else if (getpixel(screen, 234, 275) == cbleu && getpixel(screen, 234 + 126, 275) == cbleu && getpixel(screen, 234 + 2*126, 275) == cbleu) {
                    rectfill(screen, 350, 45, 475, 60, cviolet);
                    textprintf_ex(screen,font,350,50,cblanc,-1,"Vous avez gagné");
                    nbrTicket = nbrTicket + 1;
                    rectfill(screen, 300, 500, 400, 520, cviolet);
                    textprintf_ex(screen, font, 300, 500, cblanc, -1, "il vous reste %d tickets", nbrTicket); // Affiche le nouveau texte

                } else if (getpixel(screen, 234, 275) == crouge && getpixel(screen, 234 + 126, 275) == crouge && getpixel(screen, 234 + 2*126, 275) == crouge) {
                    rectfill(screen, 350, 45, 475, 60, cviolet);
                    textprintf_ex(screen,font,350,50,cblanc,-1,"Vous avez gagné");
                    nbrTicket = nbrTicket + 1;
                    rectfill(screen, 300, 500, 400, 520, cviolet);
                    textprintf_ex(screen, font, 300, 500, cblanc, -1, "il vous reste %d tickets", nbrTicket); // Affiche le nouveau texte

                } else {
                    rectfill(screen, 350, 45, 475, 60, cviolet);
                    textprintf_ex(screen,font,350,50,cblanc,-1,"Vous avez perdu");
                    rectfill(screen, 300, 500, 500, 520, cviolet);
                    textprintf_ex(screen, font, 300, 500, cblanc, -1, "il vous reste %d tickets", nbrTicket); // Affiche le nouveau texte

                }
            }
        }
    }


    readkey();

    return 0;
}
END_OF_MAIN();