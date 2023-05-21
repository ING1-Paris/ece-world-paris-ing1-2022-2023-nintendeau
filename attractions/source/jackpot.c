#include <stdio.h>
#include <allegro.h>
#include <time.h>

#include "../header/jackpot.h"
#include "../header/loader.h"
#include "../header/player.h"

#define MAX_IMAGES_CASE 3

int jackpot(Player* player)
{
    srand(time(NULL));
    int cblanc, crouge, cbleu, cvert, cviolet, cnoir;
    int v7 = 1, vviande = 2,vcoeur = 3;
    int fin;
    int nbrTicket = 5 ;
    int nbrTicketGagne = 3 ;

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    show_mouse(screen);


    BITMAP *sprite1 = image_loader("attractions/assets/jackpot/image_case/image_case0.bmp");
    BITMAP *sprite2 = image_loader("attractions/assets/jackpot/image_case/image_case1.bmp");
    BITMAP *sprite3 = image_loader("attractions/assets/jackpot/image_case/image_case2.bmp");
    BITMAP *sprite5 = image_loader("attractions/assets/jackpot/image_jackpot_3.bmp");

    BITMAP *dessprite1 = create_bitmap(86, 100);
    BITMAP *dessprite2 = create_bitmap(86, 100);
    BITMAP *dessprite3 = create_bitmap(86, 100);
    BITMAP *dessprite5 = create_bitmap(800, 650);

    SAMPLE *FondSonore = sound_loader("attractions/assets/jackpot/jackpot_fond.wav");// ajouter fond sonore
    SAMPLE *Roulette = sound_loader("attractions/assets/jackpot/jackpot_precase.wav");// son roulette
    SAMPLE *SortieCase = sound_loader("attractions/assets/jackpot/jackpot_case.wav");// quand une image sort
    SAMPLE *SonWin = sound_loader("attractions/assets/jackpot/jackpot_win.wav");// quand on gagne


    play_sample(FondSonore, 255, 128, 1000, 5);

    stretch_blit(sprite1, dessprite1, 0, 0, sprite1->w, sprite1->h, 0, 0, dessprite1->w, dessprite1->h);
    stretch_blit(sprite2, dessprite2, 0, 0, sprite2->w, sprite2->h, 0, 0, dessprite2->w, dessprite2->h);
    stretch_blit(sprite3, dessprite3, 0, 0, sprite3->w, sprite3->h, 0, 0, dessprite3->w, dessprite3->h);
    stretch_blit(sprite5, dessprite5, 0, 0, sprite5->w, sprite5->h, 0, 0, dessprite5->w, dessprite5->h);

    cblanc=makecol(255,255,255);
    crouge=makecol(255,0,0);
    cbleu=makecol(0,0,255);
    cvert= makecol(0,255,0);
    cnoir = makecol(0,0,0);

    fin=0;
    int dernierAppui = 0;

    draw_sprite(screen, dessprite5, 0, 0);
    draw_sprite(screen, dessprite1, 233, 273);
    draw_sprite(screen, dessprite2, 359, 273);
    draw_sprite(screen, dessprite3, 485, 273);


    while (!fin && !key[KEY_ESC] ) {
        if (nbrTicket <= 0) {
            rectfill(screen, 300, 545, 500, 560, cnoir);
            textprintf_ex(screen, font, 300, 550, cblanc, -1, "Vous n'avez plus de tickets !");
            rest(1000);
            fin = 1;
        }
        while (mouse_b & 1 && mouse_x <= 660 && mouse_x >= 560 && mouse_y <= 490 && mouse_y >= 462) {
            if (time(NULL) - dernierAppui >= 1) {
                dernierAppui = time(NULL);

                nbrTicket = nbrTicket - 1;
                rectfill(screen, 300, 545, 500, 560, cnoir);
                textprintf_ex(screen, font, 300, 550, cblanc, -1, "il vous reste %d tickets", nbrTicket);

                for(int i = 0 ; i < 3 ; i++) {
                    play_sample(Roulette, 255, 128, 1000, 0);
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
                        play_sample(SortieCase, 255, 128, 1000, 0);
                    } else if (choix == vviande) {
                        draw_sprite(screen, dessprite2, 233 + i * 126, 274);
                        play_sample(SortieCase, 255, 128, 1000, 0);
                    } else if (choix == vcoeur) {
                        draw_sprite(screen, dessprite3, 233 + i * 126, 274);
                        play_sample(SortieCase, 255, 128, 1000, 0);
                    }
                }

                if (getpixel(screen, 234, 275) == cvert && getpixel(screen, 234 + 126, 274) == cvert && getpixel(screen, 234 + 2*126, 274) == cvert) {
                    play_sample(SonWin, 255, 128, 1000, 0);
                    rectfill(screen, 350, 580, 475, 600,  cnoir);
                    textprintf_ex(screen,font,340,570,cblanc,-1,"Vous avez gagné");
                    nbrTicket = nbrTicket + nbrTicketGagne;
                    rectfill(screen, 300, 545, 500, 560, cnoir);
                    textprintf_ex(screen, font, 300, 550, cblanc, -1, "il vous reste %d tickets", nbrTicket); // Affiche le nouveau texte

                } else if (getpixel(screen, 234, 275) == cbleu && getpixel(screen, 234 + 126, 275) == cbleu && getpixel(screen, 234 + 2*126, 275) == cbleu) {
                    play_sample(SonWin, 255, 128, 1000, 0);
                    rectfill(screen, 350, 580, 475, 600,  cnoir);
                    textprintf_ex(screen,font,340,570,cblanc,-1,"Vous avez gagné");
                    nbrTicket = nbrTicket + nbrTicketGagne;
                    rectfill(screen, 300, 545, 500, 560,  cnoir);
                    textprintf_ex(screen, font, 300, 550, cblanc, -1, "il vous reste %d tickets", nbrTicket); // Affiche le nouveau texte

                } else if (getpixel(screen, 234, 275) == crouge && getpixel(screen, 234 + 126, 275) == crouge && getpixel(screen, 234 + 2*126, 275) == crouge) {
                    play_sample(SonWin, 255, 128, 1000, 0);
                    rectfill(screen, 350, 580, 475, 600,  cnoir);
                    textprintf_ex(screen,font,340,570,cblanc,-1,"Vous avez gagné");
                    nbrTicket = nbrTicket + nbrTicketGagne;
                    rectfill(screen, 300, 545, 500, 560,  cnoir);
                    textprintf_ex(screen, font, 300, 550, cblanc, -1, "il vous reste %d tickets", nbrTicket); // Affiche le nouveau texte

                } else {
                    rectfill(screen, 350, 580, 475, 600,  cnoir);
                    textprintf_ex(screen,font,340,570,cblanc,-1,"Vous avez perdu");
                }
            }
        }
    }

    stop_sample(FondSonore);
    destroy_sample(FondSonore);
    destroy_sample(SonWin);
    destroy_sample(SortieCase);
    destroy_sample(Roulette);
}


// Structure Player qui contient les informations du joueur
