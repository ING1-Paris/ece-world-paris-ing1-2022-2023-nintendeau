#include <allegro.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../header/paris_hippiques.h"
#include "../header/loader.h"

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 700

void choix(char * nom1, char * nom2);

int paris_hippiques(char * nom1, char * nom2) {
    SAMPLE *music = sound_loader("attractions/assets/paris_hippiques/accueil.wav");
    play_sample(music, 255, 128, 1000, 1); //permet de jouer de la musique en boucle

    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 , 0);

    BITMAP *accueil = image_loader("attractions/assets/paris_hippiques/accueil.bmp"); //création d'un bitmap
    BITMAP *choixjoueur1 = image_loader("attractions/assets/paris_hippiques/choixjoueur1.bmp");

    while (!key[KEY_ENTER]) {
        blit(accueil, screen, 0, 0, 0, 0, 1500, 700); //affichage de l'image
        rest(20);
    }
    int choix1 = 0; //variable qui va permettre de choisir le cheval
    int choix2 = 0; //variable qui va permettre de choisir le cheval
    if (key[KEY_ENTER]) {
        clear(accueil);
        destroy_bitmap(accueil);
        BITMAP *choixjoueur1 = image_loader("attractions/assets/paris_hippiques/choixjoueur1.bmp");
        blit(choixjoueur1, screen, 0, 0, 0, 0, 1500, 700);
    }


    while (choix1 == 0) {
        if (key[KEY_1]) {
            choix1 = 1;
            textprintf_ex(choixjoueur1, font, 600, 620, makecol(0, 55, 255), -1, "%s,VOUS AVEZ CHOISI LE CHEVAL 1",nom1, choix1);
            blit(choixjoueur1, screen, 0, 0, 0, 0, 1500, 700);
        }
        if (key[KEY_2]) {
            choix1 = 2;
            textprintf_ex(choixjoueur1, font, 600, 620, makecol(0, 55, 255), -1, "%s,VOUS AVEZ CHOISI LE CHEVAL 1",nom1, choix1);
            blit(choixjoueur1, screen, 0, 0, 0, 0, 1500, 700);
        }
        if (key[KEY_3]) {
            choix1 = 3;
            textprintf_ex(choixjoueur1, font, 600, 620, makecol(0, 55, 255), -1, "%s,VOUS AVEZ CHOISI LE CHEVAL 1",nom1, choix1);
            blit(choixjoueur1, screen, 0, 0, 0, 0, 1500, 700);
        }
        if (key[KEY_4]) {
            choix1 = 4;
            textprintf_ex(choixjoueur1, font, 600, 620, makecol(0, 55, 255), -1, "%s,VOUS AVEZ CHOISI LE CHEVAL 1",nom1, choix1);
            blit(choixjoueur1, screen, 0, 0, 0, 0, 1500, 700);
        }
        if (key[KEY_5]) {
            choix1 = 5;
        }
    }
    if (choix1 == 5) {
        allegro_exit();
    }

    rest(2000);
    clear_bitmap(choixjoueur1);
    destroy_bitmap(choixjoueur1);

    BITMAP *choixjoueur2 = image_loader("attractions/assets/paris_hippiques/choixjoueur2.bmp");
    blit(choixjoueur2, screen, 0, 0, 0, 0, 1500, 700);

    if (choixjoueur2)
    while (choix2 == 0) {
        if (key[KEY_1]) {
            choix2 = 1;
        }
        if (key[KEY_2]) {
            choix2 = 2;
        }
        if (key[KEY_3]) {
            choix2 = 3;
        }
        if (key[KEY_4]) {
            choix2 = 4;
        }
        if (key[KEY_5]) {
            choix2 = 5;
        }
    }
        if (choix2 == 5) {
        allegro_exit();
        }

    if (choix1== choix2){
        textprintf_ex(choixjoueur2, font, 600, 620, makecol(255, 0, 0), -1, "VOUS AVEZ CHOISI LE MEME CHEVAL");
        textprintf_ex(choixjoueur2, font, 600, 650, makecol(255, 0, 0), -1, "Appuyez sur ENTREE pour recommencer.");
        blit(choixjoueur2, screen, 0, 0, 0, 0, 1500, 700);
        while (!key[KEY_ENTER]) {
            blit(choixjoueur2, screen, 0, 0, 0, 0, 1500, 700);
        }
        if (key[KEY_ENTER]){
            choix(nom1, nom2);

        }
    }
    textprintf_ex(choixjoueur2, font, 600, 620, makecol(0, 55, 255), -1, "%s,VOUS AVEZ CHOISI LE CHEVAL %d",nom1, choix1);
    textprintf_ex(choixjoueur2, font, 600, 650, makecol(0, 0, 0), -1, "%s,VOUS AVEZ CHOISI LE CHEVAL %d",nom2, choix2);
    textprintf_ex(choixjoueur2, font, 570, 680, makecol(255, 0, 0), -1, "Appuyez sur ENTREE pour commencer la course.");
    blit(choixjoueur2, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    while (!key[KEY_ENTER]) {
        blit(choixjoueur2, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    clear(choixjoueur2);
    destroy_bitmap(choixjoueur2);
    stop_sample(music); //arret de la musique d'accueil

    int winner = 0;


    if (key[KEY_ENTER]){

        //DECLARATION DES VARIABLES
        int compteur = 0;
        int anim = 0;
        bool gagne = false; //variable qui permet de savoir si un cheval a gagné
        int score1 = 0; //variable qui permet de cumuler les points du joueur 1
        int score2 = 0; //variable qui permet de cumuler les points du joueur 2
        int soldeticket1 = 5; //variable qui permet de savoir combien de tickets le joueur 1 a acheté
        int soldeticket2 = 5; //variable qui permet de savoir combien de tickets le joueur 2 a acheté

        srand(time(NULL)); //initialisation de la fonction random pour l'attribution des vitesses des chevaux de maniere aleatoire

        BITMAP *background = image_loader("attractions/assets/paris_hippiques/coursefinal.bmp");
        if (!background) {
            allegro_message("Erreur lors du chargement de l'image");
            exit(EXIT_FAILURE);
        }
        BITMAP *page = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
        BITMAP *sprite1[3];
        sprite1[0] = image_loader("attractions/assets/paris_hippiques/applejack1.bmp");
        sprite1[1] = image_loader("attractions/assets/paris_hippiques/applejack2.bmp");
        sprite1[2] = image_loader("attractions/assets/paris_hippiques/applejack3.bmp");
        if (!sprite1[0] || !sprite1[1] || !sprite1[2]) {
            allegro_message("Erreur lors du chargement des sprites");
            exit(EXIT_FAILURE);
        }
        BITMAP *sprite2[3];
        sprite2[0] = image_loader("attractions/assets/paris_hippiques/rainbowdash1.bmp");
        sprite2[1] = image_loader("attractions/assets/paris_hippiques/rainbowdash2.bmp");
        sprite2[2] = image_loader("attractions/assets/paris_hippiques/rainbowdash3.bmp");
        if (!sprite2[0] || !sprite2[1] || !sprite2[2]) {
            allegro_message("Erreur lors du chargement des sprites 1");
            exit(EXIT_FAILURE);
        }
        BITMAP *sprite3[3];
        sprite3[0] = image_loader("attractions/assets/paris_hippiques/purseypink1.bmp");
        sprite3[1] = image_loader("attractions/assets/paris_hippiques/purseypink2.bmp");
        sprite3[2] = image_loader("attractions/assets/paris_hippiques/purseypink3.bmp");
        if (!sprite3[0] || !sprite3[1] || !sprite3[2]) {
            allegro_message("Erreur lors du chargement des sprites 2");
            exit(EXIT_FAILURE);
        }
        BITMAP *sprite4[3];
        sprite4[0] = image_loader("attractions/assets/paris_hippiques/purplewave1.bmp");
        sprite4[1] = image_loader("attractions/assets/paris_hippiques/purplewave2.bmp");
        sprite4[2] = image_loader("attractions/assets/paris_hippiques/purplewave3.bmp");
        if (!sprite4[0] || !sprite4[1] || !sprite4[2]) {
            allegro_message("Erreur lors du chargement des sprites 3");
            exit(EXIT_FAILURE);
        }
        //initialisation des variables de position et de vitesse pour chaque sprite
        float x1 = 88, y1 = 580, speed1 = 1 + rand() % 10 + 1;
        float x2 = 88, y2 = 550, speed2 = 1 + rand() % 10 + 1;
        float x3 = 88, y3 = 520, speed3 = 1 + rand() % 10 + 1;
        float x4 = 88, y4 = 490, speed4 = 1 + rand() % 10 + 1;

        SAMPLE *music2 = sound_loader("attractions/assets/paris_hippiques/course1.wav"); //chargement de la musique de course
        if (!music2) {
            allegro_message("Erreur lors du chargement de la musique");
            exit(EXIT_FAILURE);
        }
        play_sample(music2, 255, 128, 1000, 1); //lancement de la musique de course

        textprintf_ex(page, font, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, makecol(255, 255, 255), -1, "3");
        blit(page, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        rest(1000);
        clear(page);
        textprintf_ex(page, font, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, makecol(255, 255, 255), -1, "2");
        blit(page, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        rest(1000);
        clear(page);
        textprintf_ex(page, font, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, makecol(255, 255, 255), -1, "1");
        SAMPLE *music3 = sound_loader("attractions/assets/paris_hippiques/pistolet.wav"); //chargement de la musique de course
        if (!music3) {
            allegro_message("Erreur lors du chargement de la musique");
            exit(EXIT_FAILURE);
        }
        play_sample(music3, 255, 128, 1000, 0); //lancement de la musique de course
        blit(page, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        rest(1000);
        clear(page);


        //boucle de jeu principal
        while (!key[KEY_ESC] && gagne == false) {
            compteur++;
            if(compteur % 4==0){ //changer d'image toutes les 4 frames (pour ralentir l'animation)
                //changer d'image
                rest(50);
                anim++;
                if (anim > 2)
                    anim = 0;
            }

            if(speed4 == speed1){
                speed1 = 1 + rand() % 10 + 1;
            }
            if(speed3 == speed2){
                speed3 = 1 + rand() % 10 + 1;
            }
            if(speed2 == speed1){
                speed2 = 1 + rand() % 10 + 1;
            }
            if (speed2 == speed4){
                speed4 = 1 + rand() % 10 + 1;
            }

            //affichage du fond
            blit(background, page, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            line(page, 100, 530, 100, 703, makecol(255, 255, 255));
            line(page, 1400, 530, 1400, 703, makecol(255, 255, 255));


            //déplacement du cheval 1
            x1 += speed1/4;
            if (x1 > 1410) {
                gagne = true;
                if(choix1 == 1){
                    score1 ++;
                    soldeticket1 += 1;
                    soldeticket2 -= 1;
                    allegro_message("%s remporte la course !", nom1);
                    winner = 1;
                    stop_sample(music2);
                }else if(choix2 ==1){
                    score2 ++;
                    soldeticket2 += 1;
                    soldeticket1 -= 1;
                    allegro_message("%s remporte la course !", nom2);
                    winner = 2;
                    stop_sample(music2);
                }else{
                    soldeticket1 -= 1;
                    soldeticket2 -= 1;
                    allegro_message("Match nul ! Solde %s = %d, Solde %s = %d",nom1, nom2,soldeticket1,soldeticket2);
                    winner = 0;
                    stop_sample(music2);
                }
            }
            draw_sprite(page, sprite1[anim], x1, y1);

            //déplacement du cheval 2
            x2 += speed2/4;
            if (x2 > 1410) {
                gagne = true;
                if (choix1 == 2) {
                    score1++;
                    soldeticket1 += 1;
                    soldeticket2 -= 1;
                    allegro_message("%s remporte la course !", nom1);
                    winner = 1;
                    stop_sample(music2);
                } else if (choix2 == 2) {
                    score2++;
                    soldeticket2 += 1;
                    soldeticket1 -= 1;
                    allegro_message("%s remporte la course !", nom2);
                    winner = 2;
                    stop_sample(music2);
                } else {
                    soldeticket1 -= 1;
                    soldeticket2 -= 1;
                    allegro_message("Match nul ! Solde %s = %d, Solde %s = %d",nom1, nom2,soldeticket1,soldeticket2);
                    winner = 0;
                    stop_sample(music2);
                }
            }
            draw_sprite(page, sprite2[anim], x2, y2);

            //déplacement du cheval 3
            x3 += speed3/4; //vitesse du cheval divisée par 10 pour ralentir le cheval
            if (x3 > 1410) {
                gagne = true;
                if(choix1 == 3){
                    score1 ++;
                    soldeticket1 += 1;
                    soldeticket2 -= 1;
                    allegro_message("%s remporte la course !", nom1);
                    winner = 1;
                    stop_sample(music2);
                }else if(choix2 ==3){
                    score2 ++;
                    soldeticket2 += 1;
                    soldeticket1 -= 1;
                    allegro_message("%s remporte la course !", nom2);
                    winner = 2;
                    stop_sample(music2);
                } else{
                    soldeticket1 -= 1;
                    soldeticket2 -= 1;
                    allegro_message("Match nul ! Solde %s = %d, Solde %s = %d",nom1, nom2,soldeticket1,soldeticket2);
                    winner = 0;
                    stop_sample(music2);
                }
            }
            draw_sprite(page, sprite3[anim], x3, y3);

            //deplacement du cheval 4
            x4 += speed4/4;
            if (x4 > 1410) {
                gagne = true;
                if(choix1 == 4){
                    score1 ++;
                    soldeticket1 += 1;
                    soldeticket2 -= 1;
                    allegro_message("%s remporte la course !", nom1);
                    winner = 1;
                    stop_sample(music2);
                }else if(choix2 ==4){
                    score2 ++;
                    soldeticket2 += 1;
                    soldeticket1 -= 1;
                    allegro_message("%s remporte la course !", nom2);
                    winner = 2;
                    stop_sample(music2);
                } else{
                    soldeticket1 -= 1;
                    soldeticket2 -= 1;
                    allegro_message("Match nul ! Solde %s = %d, Solde %s = %d",nom1, nom2,soldeticket1,soldeticket2);
                    winner = 0;
                    stop_sample(music2);
                }
            }
            draw_sprite(page, sprite4[anim], x4, y4);
            blit(page, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        }
        stop_sample(music2);

    }
    return winner;
}

void choix(char * nom1, char * nom2){

    BITMAP *accueil = image_loader("attractions/assets/paris_hippiques/accueil.bmp"); //création d'un bitmap
    BITMAP *choixjoueur1 = image_loader("attractions/assets/paris_hippiques/choixjoueur1.bmp");

    while (!key[KEY_ENTER]) {
        blit(accueil, screen, 0, 0, 0, 0, 1500, 700); //affichage de l'image
        rest(20);
    }
    int choix1 = 0; //variable qui va permettre de choisir le cheval
    int choix2 = 0; //variable qui va permettre de choisir le cheval
    if (key[KEY_ENTER]) {
        clear(accueil);
        destroy_bitmap(accueil);
        BITMAP *choixjoueur1 = image_loader("attractions/assets/paris_hippiques/choixjoueur1.bmp");
        blit(choixjoueur1, screen, 0, 0, 0, 0, 1500, 700);
    }

    while (choix1 == 0) {
        if (key[KEY_1]) {
            choix1 = 1;
        }
        if (key[KEY_2]) {
            choix1 = 2;
        }
        if (key[KEY_3]) {
            choix1 = 3;
        }
        if (key[KEY_4]) {
            choix1 = 4;
        }
        if (key[KEY_5]) {
            choix1 = 5;
        }
    }
    if (choix1 == 5) {
        allegro_exit();
    }
    rest(2000);
    clear_bitmap(choixjoueur1);
    destroy_bitmap(choixjoueur1);

    BITMAP *choixjoueur2 = image_loader("attractions/assets/paris_hippiques/choixjoueur2.bmp");
    blit(choixjoueur2, screen, 0, 0, 0, 0, 1500, 700);
    while (choix2 == 0) {
        if (key[KEY_1]) {
            choix2 = 1;
        }
        if (key[KEY_2]) {
            choix2 = 2;
        }
        if (key[KEY_3]) {
            choix2 = 3;
        }
        if (key[KEY_4]) {
            choix2 = 4;
        }
        if (key[KEY_5]) {
            choix2 = 5;
        }
    }
    if (choix2 == 5) {
        allegro_exit();
    }

    if (choix1== choix2){
        textprintf_ex(choixjoueur2, font, 10, 10, makecol(255, 255, 255), -1, "VOUS AVEZ CHOISI LE MEME CHEVAL");
        textprintf_ex(choixjoueur2, font, 10, 30, makecol(255, 255, 255), -1, "Appuyez sur ENTREE pour recommencer.");
        blit(choixjoueur2, screen, 0, 0, 0, 0, 1500, 700);
        while (!key[KEY_ENTER]) {
            blit(choixjoueur2, screen, 0, 0, 0, 0, 1500, 700);
        }
        if (key[KEY_ENTER]){
            choix(nom1, nom2);

        }
    }
    textprintf_ex(choixjoueur2, font, 10, 10, makecol(255, 255, 255), -1, " %s,VOUS AVEZ CHOISI LE CHEVAL %d",nom1, choix1);
    textprintf_ex(choixjoueur2, font, 10, 30, makecol(0, 0, 0), -1, "%s,VOUS AVEZ CHOISI LE CHEVAL %d",nom2, choix2);
    textprintf_ex(choixjoueur2, font, 10, 50, makecol(0, 0, 0), -1, "Appuyez sur ENTREE pour commencer la course.");
    blit(choixjoueur2, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    while (!key[KEY_ENTER]) {
        blit(choixjoueur2, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    clear(choixjoueur2);
    blit(choixjoueur2, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}