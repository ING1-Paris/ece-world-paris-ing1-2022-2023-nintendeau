#include <allegro.h>
#include <stdlib.h>
#include <stdbool.h>

#define SCREEN_W 1500
#define SCREEN_H 700

void choix();

int main() {
    //initialisation d'Allegro
    allegro_init();
    install_keyboard();
    set_color_depth(32);

    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0 , 0);

    BITMAP *accueil = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\accueil.bmp",NULL); //création d'un bitmap
    BITMAP *choixjoueur1 = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\choixjoueur1.bmp",NULL);

    while (!key[KEY_ENTER]) {
        blit(accueil, screen, 0, 0, 0, 0, 1500, 700); //affichage de l'image
        rest(20);
    }
    int choix1 = 0; //variable qui va permettre de choisir le cheval
    int choix2 = 0; //variable qui va permettre de choisir le cheval
    if (key[KEY_ENTER]) {
        clear(accueil);
        destroy_bitmap(accueil);
        BITMAP *choixjoueur1 = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\choixjoueur1.bmp",NULL);
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

    BITMAP *choixjoueur2 = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\choixjoueur2.bmp",NULL);
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
            choix();

        }
    }
    textprintf_ex(choixjoueur2, font, 600, 620, makecol(0, 55, 255), -1, "JOUEUR 1,VOUS AVEZ CHOISI LE CHEVAL %d", choix1);
    textprintf_ex(choixjoueur2, font, 600, 650, makecol(0, 0, 0), -1, "JOUEUR 2,VOUS AVEZ CHOISI LE CHEVAL %d", choix2);
    textprintf_ex(choixjoueur2, font, 570, 680, makecol(255, 0, 0), -1, "Appuyez sur ENTREE pour commencer la course.");
    blit(choixjoueur2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    while (!key[KEY_ENTER]) {
        blit(choixjoueur2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    clear(choixjoueur2);
    blit(choixjoueur2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

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

        BITMAP *background = load_bitmap("../images/coursefinal.bmp", NULL);
        if (!background) {
            allegro_message("Erreur lors du chargement de l'image");
            exit(EXIT_FAILURE);
        }
        BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
        BITMAP *sprite1[3];
        sprite1[0] = load_bitmap("../images/applejack1.bmp", NULL);
        sprite1[1] = load_bitmap("../images/applejack2.bmp", NULL);
        sprite1[2] = load_bitmap("../images/applejack3.bmp", NULL);
        if (!sprite1[0] || !sprite1[1] || !sprite1[2]) {
            allegro_message("Erreur lors du chargement des sprites");
            exit(EXIT_FAILURE);
        }
        BITMAP *sprite2[3];
        sprite2[0] = load_bitmap("../images/rainbowdash1.bmp", NULL);
        sprite2[1] = load_bitmap("../images/rainbowdash2.bmp", NULL);
        sprite2[2] = load_bitmap("../images/rainbowdash3.bmp", NULL);
        if (!sprite2[0] || !sprite2[1] || !sprite2[2]) {
            allegro_message("Erreur lors du chargement des sprites 1");
            exit(EXIT_FAILURE);
        }
        BITMAP *sprite3[3];
        sprite3[0] = load_bitmap("../images/purseypink1.bmp", NULL);
        sprite3[1] = load_bitmap("../images/purseypink2.bmp", NULL);
        sprite3[2] = load_bitmap("../images/purseypink3.bmp", NULL);
        if (!sprite3[0] || !sprite3[1] || !sprite3[2]) {
            allegro_message("Erreur lors du chargement des sprites 2");
            exit(EXIT_FAILURE);
        }
        BITMAP *sprite4[3];
        sprite4[0] = load_bitmap("../images/purplewave1.bmp", NULL);
        sprite4[1] = load_bitmap("../images/purplewave2.bmp", NULL);
        sprite4[2] = load_bitmap("../images/purplewave3.bmp", NULL);
        if (!sprite4[0] || !sprite4[1] || !sprite4[2]) {
            allegro_message("Erreur lors du chargement des sprites 3");
            exit(EXIT_FAILURE);
        }
        //initialisation des variables de position et de vitesse pour chaque sprite
        float x1 = 99, y1 = 580, speed1 = rand() % 20 + 1;
        float x2 = 99, y2 = 550, speed2 = rand() % 20 + 1;
        float x3 = 99, y3 = 520, speed3 = rand() % 20 + 1;
        float x4 = 99, y4 = 490, speed4 = rand() % 20 + 1;

        textprintf_ex(background, font, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), -1, "3");
        blit(background, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(1000);
        textprintf_ex(background, font, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), -1, "2");
        blit(background, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(1000);
        textprintf_ex(background, font, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), -1, "1");
        blit(background, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(1000);
        textprintf_ex(background, font, SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), -1, "GO !");
        blit(background, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(1000);



        //boucle de jeu principal
        while (!key[KEY_ESC]) {
            compteur++;
            if(compteur % 4==0){ //changer d'image toutes les 4 frames (pour ralentir l'animation)
                //changer d'image
                anim++;
                if (anim > 2)
                    anim = 0;
            }

            if(speed4 == speed1){
                speed1 = rand() % 20 + 1;
            }
            if(speed3 == speed2){
                speed3 = rand() % 20 + 1;
            }
            if(speed2 == speed1){
                speed2 = rand() % 20 + 1;
            }
            if (speed2 == speed4){
                speed4 = rand() % 20 + 1;
            }

            //affichage du fond
            blit(background, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            line(page, 100, 530, 100, 703, makecol(255, 255, 255));
            line(page, 1400, 530, 1400, 703, makecol(255, 255, 255));


            //déplacement du cheval 1
            x1 += speed1/10;
            if (x1 > 1410) {
                gagne = true;
                if(choix1 == 1){
                    score1 ++;
                    soldeticket1 += 1;
                    soldeticket2 -= 1;
                    allegro_message("Joueur 1,remporte la course !");
                }else if(choix2 ==1){
                    score2 ++;
                    soldeticket2 += 1;
                    soldeticket1 -= 1;
                    allegro_message("Joueur 2,remporte la course !");
                }else{
                    soldeticket1 -= 1;
                    soldeticket2 -= 1;
                    allegro_message("Match nul ! Solde J1 = %d, Solde J2 = %d",soldeticket1,soldeticket2);
                }
            }
            draw_sprite(page, sprite1[anim], x1, y1);

            //déplacement du cheval 2
            x2 += speed2/10;
            if (x2 > 1410) {
                gagne = true;
                if (choix1 == 2) {
                    score1++;
                    soldeticket1 += 1;
                    soldeticket2 -= 1;
                    allegro_message("Joueur 1,remporte la course !");
                } else if (choix2 == 2) {
                    score2++;
                    soldeticket2 += 1;
                    soldeticket1 -= 1;
                    allegro_message("Joueur 2,remporte la course !");
                } else {
                    soldeticket1 -= 1; //
                    soldeticket2 -= 1;
                    allegro_message("Match nul ! Solde J1 = %d, Solde J2 = %d", soldeticket1, soldeticket2);
                }
            }
            draw_sprite(page, sprite2[anim], x2, y2);

            //déplacement du cheval 3
            x3 += speed3/10; //vitesse du cheval divisée par 10 pour ralentir le cheval
            if (x3 > 1410) {
                gagne = true;
                if(choix1 == 3){
                    score1 ++;
                    soldeticket1 += 1;
                    soldeticket2 -= 1;
                    allegro_message("Joueur 1,remporte la course !");
                }else if(choix2 ==3){
                    score2 ++;
                    soldeticket2 += 1;
                    soldeticket1 -= 1;
                    allegro_message("Joueur 2,remporte la course !");
                } else{
                    soldeticket1 -= 1;
                    soldeticket2 -= 1;
                    allegro_message("Match nul ! Solde J1 = %d, Solde J2 = %d",soldeticket1,soldeticket2);
                }
            }
            draw_sprite(page, sprite3[anim], x3, y3);

            //deplacement du cheval 4
            x4 += speed4/10;
            if (x4 > 1410) {
                gagne = true;
                if(choix1 == 4){
                    score1 ++;
                    soldeticket1 += 1;
                    soldeticket2 -= 1;
                    allegro_message("Joueur 1,remporte la course !");
                }else if(choix2 ==4){
                    score2 ++;
                    soldeticket2 += 1;
                    soldeticket1 -= 1;
                    allegro_message("Joueur 2,remporte la course !");
                } else{
                    soldeticket1 -= 1;
                    soldeticket2 -= 1;
                    allegro_message("Match nul ! Solde J1 = %d, Solde J2 = %d",soldeticket1,soldeticket2);
                }
            }
            draw_sprite(page, sprite4[anim], x4, y4);
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }

    }
    return 0;
}END_OF_MAIN();

void choix(){

    BITMAP *accueil = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\accueil.bmp",NULL); //création d'un bitmap
    BITMAP *choixjoueur1 = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\choixjoueur1.bmp",NULL);

    while (!key[KEY_ENTER]) {
        blit(accueil, screen, 0, 0, 0, 0, 1500, 700); //affichage de l'image
        rest(20);
    }
    int choix1 = 0; //variable qui va permettre de choisir le cheval
    int choix2 = 0; //variable qui va permettre de choisir le cheval
    if (key[KEY_ENTER]) {
        clear(accueil);
        destroy_bitmap(accueil);
        BITMAP *choixjoueur1 = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\choixjoueur1.bmp",NULL);
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

    BITMAP *choixjoueur2 = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\choixjoueur2.bmp",NULL);
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
            choix();

        }
    }
    textprintf_ex(choixjoueur2, font, 10, 10, makecol(255, 255, 255), -1, "JOUEUR 1,VOUS AVEZ CHOISI LE CHEVAL %d", choix1);
    textprintf_ex(choixjoueur2, font, 10, 30, makecol(0, 0, 0), -1, "JOUEUR 2,VOUS AVEZ CHOISI LE CHEVAL %d", choix2);
    textprintf_ex(choixjoueur2, font, 10, 50, makecol(0, 0, 0), -1, "Appuyez sur ENTREE pour commencer la course.");
    blit(choixjoueur2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    while (!key[KEY_ENTER]) {
        blit(choixjoueur2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    clear(choixjoueur2);
    blit(choixjoueur2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
