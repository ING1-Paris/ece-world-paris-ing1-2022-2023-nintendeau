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

    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0 , 0); //

    BITMAP *accueil = create_bitmap(SCREEN_W, SCREEN_H); //création d'un bitmap
    //titre
    textprintf_ex(accueil, font, 900, 20, makecol(255, 255, 255), -1, "BIENVENUE DANS LE JEU PARIS HIPPIQUES");

    //texte
    textprintf_ex(accueil, font, 10, 80, makecol(255, 255, 255), -1, "Vous serez 2 JOUEURS et vous allez devoir choisir un cheval parmi les 4 qui vous sont proposés.");
    textprintf_ex(accueil, font, 10, 140, makecol(255, 255, 255), -1, "Vous allez ensuite miser un ticket sur ce cheval.");
    textprintf_ex(accueil, font, 10, 200, makecol(255, 255, 255), -1, "Si votre cheval gagne, vous remportez un ticket.");
    textprintf_ex(accueil, font, 10, 260, makecol(255, 255, 255), -1, "Mais si vous perdez, vous perdez un ticket.");
    textprintf_ex(accueil, font, 10, 320, makecol(255, 255, 255), -1, "Chaque joueur commence avec un solde de 5 tickets.");
    textprintf_ex(accueil, font, 10, 340, makecol(255, 255, 255), -1, "Le premier joueur qui arrive à un solde de 0 ticket a perdu.");
    textprintf_ex(accueil, font, 10, 380, makecol(255, 255, 255), -1, "Appuyez sur ENTREE pour continuer.");
    while (!key[KEY_ENTER]) {
        blit(accueil, screen, 0, 0, 0, 0, 800, 500); //affichage de l'image
        rest(20);
    }
    int choix1 = 0; //variable qui va permettre de choisir le cheval
    int choix2 = 0; //variable qui va permettre de choisir le cheval
    if (key[KEY_ENTER]) {
        clear(accueil);
        textprintf_ex(accueil, font, 10, 10, makecol(255, 255, 255), -1, "JOUEUR 1,CHOISISSEZ VOTRE CHEVAL"); //affichage du texte
        textprintf_ex(accueil, font, 10, 30, makecol(255, 0, 0), -1, "1. CHEVAL 1");
        textprintf_ex(accueil, font, 10, 50, makecol(0, 128, 0), -1, "2. CHEVAL 2");
        textprintf_ex(accueil, font, 10, 70, makecol(255, 255, 0), -1, "3. CHEVAL 3");
        textprintf_ex(accueil, font, 10, 90, makecol(128, 0, 128), -1, "4. CHEVAL 4");
        textprintf_ex(accueil, font, 10, 110, makecol(255, 255, 255), -1, "5. QUITTER");
        blit(accueil, screen, 0, 0, 0, 0, 800, 500);
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
    rest(3000);
    clear(accueil);
    textprintf_ex(accueil, font, 10, 10, makecol(255, 255, 255), -1, "JOUEUR 2,CHOISISSEZ VOTRE CHEVAL");
    textprintf_ex(accueil, font, 10, 30, makecol(255, 0, 0), -1, "1. CHEVAL 1");
    textprintf_ex(accueil, font, 10, 50, makecol(0, 128, 0), -1, "2. CHEVAL 2");
    textprintf_ex(accueil, font, 10, 70, makecol(255, 255, 0), -1, "3. CHEVAL 3");
    textprintf_ex(accueil, font, 10, 90, makecol(128, 0, 128), -1, "4. CHEVAL 4");
    textprintf_ex(accueil, font, 10, 110, makecol(255, 255, 255), -1, "5. QUITTER");
    blit(accueil, screen, 0, 0, 0, 0, 800, 500);

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
        clear(accueil);
        textprintf_ex(accueil, font, 10, 10, makecol(255, 255, 255), -1, "VOUS AVEZ CHOISI LE MEME CHEVAL");
        textprintf_ex(accueil, font, 10, 30, makecol(255, 255, 255), -1, "Appuyez sur ENTREE pour recommencer.");
        blit(accueil, screen, 0, 0, 0, 0, 800, 500);
        while (!key[KEY_ENTER]) {
            blit(accueil, screen, 0, 0, 0, 0, 800, 500);
        }
        if (key[KEY_ENTER]){
            choix();

        }
    }
    clear(accueil);
    textprintf_ex(accueil, font, 10, 10, makecol(255, 255, 255), -1, "JOUEUR 1,VOUS AVEZ CHOISI LE CHEVAL %d", choix1);
    textprintf_ex(accueil, font, 10, 30, makecol(255, 255, 255), -1, "JOUEUR 2,VOUS AVEZ CHOISI LE CHEVAL %d", choix2);
    textprintf_ex(accueil, font, 10, 50, makecol(255, 255, 255), -1, "Appuyez sur ENTREE pour commencer la course.");
    blit(accueil, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    while (!key[KEY_ENTER]) {
        blit(accueil, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    clear(accueil);
    blit(accueil, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    if (key[KEY_ENTER]){

        //DECLARATION DES VARIABLES
        int compteur = 0;
        int anim = 0;
        bool gagne = false; //variable qui permet de savoir si un cheval a gagné
        int score1 = 0; //variable qui permet de cumuler les points du joueur 1
        int score2 = 0; //variable qui permet de cumuler les points du joueur 2
        int soldeticket1 = 5; //variable qui permet de savoir combien de tickets le joueur 1 a acheté
        int soldeticket2 = 5; //variable qui permet de savoir combien de tickets le joueur 2 a acheté
        srand(time(NULL));

        BITMAP* background = load_bitmap("../images/coursefinal.bmp", NULL);
        BITMAP*page = create_bitmap(SCREEN_W, SCREEN_H);
        BITMAP* sprite1[3];
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

        //boucle de jeu
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

            // Affichage du fond
            blit(background, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            line(page, 100, 530, 100, 703, makecol(255, 255, 0));
            line(page, 1400, 530, 1400, 703, makecol(50, 0, 50));


            // Déplacement du sprite 1
            x1 += speed1/10;
            if (x1 > 1410) {
                bool gagne = true;
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

            // Déplacement du sprite 2
            x2 += speed2/10;
            if (x2 > 1410) {
                bool gagne = true;
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
                bool gagne = true;
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
                bool gagne = true;
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

    BITMAP *accueil = create_bitmap(1500, 700);
    //titre
    textprintf_ex(accueil, font, 900, 20, makecol(255, 255, 255), -1, "BIENVENUE DANS LE JEU PARIS HIPPIQUES");

    //texte
    textprintf_ex(accueil, font, 10, 80, makecol(255, 255, 255), -1, "Vous serez 2 JOUEURS et vous allez devoir choisir un cheval parmi les 4 qui vous sont proposés.");
    textprintf_ex(accueil, font, 10, 140, makecol(255, 255, 255), -1, "Vous allez ensuite miser un ticket sur ce cheval.");
    textprintf_ex(accueil, font, 10, 200, makecol(255, 255, 255), -1, "Si votre cheval gagne, vous remportez un ticket.");
    textprintf_ex(accueil, font, 10, 260, makecol(255, 255, 255), -1, "Mais si vous perdez, vous perdez un ticket.");
    textprintf_ex(accueil, font, 10, 320, makecol(255, 255, 255), -1, "Chaque joueur commence avec un solde de 5 tickets.");
    textprintf_ex(accueil, font, 10, 340, makecol(255, 255, 255), -1, "Le premier joueur qui arrive à un solde de 0 ticket a perdu.");
    textprintf_ex(accueil, font, 10, 380, makecol(255, 255, 255), -1, "Appuyez sur ENTREE pour continuer.");
    while (!key[KEY_ENTER]) {
        blit(accueil, screen, 0, 0, 0, 0, 800, 500);
    }
    int choix1 = 0;
    int choix2 = 0;
    if (key[KEY_ENTER]) {
        clear(accueil);
        textprintf_ex(accueil, font, 10, 10, makecol(255, 255, 255), -1, "JOUEUR 1,CHOISISSEZ VOTRE CHEVAL");
        textprintf_ex(accueil, font, 10, 30, makecol(255, 0, 0), -1, "1. CHEVAL 1");
        textprintf_ex(accueil, font, 10, 50, makecol(0, 128, 0), -1, "2. CHEVAL 2");
        textprintf_ex(accueil, font, 10, 70, makecol(255, 255, 0), -1, "3. CHEVAL 3");
        textprintf_ex(accueil, font, 10, 90, makecol(128, 0, 128), -1, "4. CHEVAL 4");
        textprintf_ex(accueil, font, 10, 110, makecol(255, 255, 255), -1, "5. QUITTER");
        blit(accueil, screen, 0, 0, 0, 0, 800, 500);
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
    rest(3000);
    clear(accueil);
    textprintf_ex(accueil, font, 10, 10, makecol(255, 255, 255), -1, "JOUEUR 2,CHOISISSEZ VOTRE CHEVAL");
    textprintf_ex(accueil, font, 10, 30, makecol(255, 0, 0), -1, "1. CHEVAL 1");
    textprintf_ex(accueil, font, 10, 50, makecol(0, 128, 0), -1, "2. CHEVAL 2");
    textprintf_ex(accueil, font, 10, 70, makecol(255, 255, 0), -1, "3. CHEVAL 3");
    textprintf_ex(accueil, font, 10, 90, makecol(128, 0, 128), -1, "4. CHEVAL 4");
    textprintf_ex(accueil, font, 10, 110, makecol(255, 255, 255), -1, "5. QUITTER");
    blit(accueil, screen, 0, 0, 0, 0, 800, 500);

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
        clear(accueil);
        textprintf_ex(accueil, font, 10, 10, makecol(255, 255, 255), -1, "VOUS AVEZ CHOISI LE MEME CHEVAL");
        textprintf_ex(accueil, font, 10, 30, makecol(255, 255, 255), -1, "Appuyez sur ENTREE pour recommencer.");
        blit(accueil, screen, 0, 0, 0, 0, 800, 500);
        while (!key[KEY_ENTER]) {
            blit(accueil, screen, 0, 0, 0, 0, 800, 500);
        }
        if (key[KEY_ENTER]){
            choix();

        }
    }
}
