#include <allegro.h>
#include <stdlib.h>

#define SCREEN_W 1500
#define SCREEN_H 700

typedef struct {
    int x; //coordonnées du cheval
    int y; //coordonnées du cheval
    int dx; //vitesse du cheval
    int dy; //vitesse du cheval
} cheval;

typedef struct {
    int soldetickets; //5 tickets au départ
    int chevalchoisi; //1,2,3,4 en fonction du cheval choisi par le joueur 1 ou 2
} joueur;


void regles_jeu(){
    install_keyboard();
    set_color_depth(32);
    BITMAP *buffer = create_bitmap(800, 500);

    //couleur de fond
    clear_to_color(buffer, makecol(150, 150, 150));

    //titre
    textprintf_centre_ex(buffer, font, 400, 20, makecol(255, 255, 255), -1, "BIENVENUE DANS LE JEU PARIS HIPPIQUES");

    //sous-titres
    textprintf_ex(buffer, font, 10, 60, makecol(255, 255, 255), -1, "Les règles du jeu :");
    textprintf_ex(buffer, font, 10, 120, makecol(255, 255, 255), -1, "Choix du cheval :");
    textprintf_ex(buffer, font, 10, 180, makecol(255, 255, 255), -1, "Mise des tickets :");
    textprintf_ex(buffer, font, 10, 240, makecol(255, 255, 255), -1, "Gains et pertes :");
    textprintf_ex(buffer, font, 10, 300, makecol(255, 255, 255), -1, "Solde et fin de partie :");

    //texte
    textprintf_ex(buffer, font, 10, 80, makecol(255, 255, 255), -1, "Vous serez 2 JOUEURS et vous allez devoir choisir un cheval parmi les 4 qui vous sont proposés.");
    textprintf_ex(buffer, font, 10, 140, makecol(255, 255, 255), -1, "Vous allez ensuite miser un ou plusieurs tickets sur ce cheval.");
    textprintf_ex(buffer, font, 10, 200, makecol(255, 255, 255), -1, "Si votre cheval gagne, vous remportez 2 fois votre mise.");
    textprintf_ex(buffer, font, 10, 260, makecol(255, 255, 255), -1, "Mais si vous perdez, vous perdez un ticket.");
    textprintf_ex(buffer, font, 10, 320, makecol(255, 255, 255), -1, "Chaque joueur commence avec un solde de 5 tickets.");
    textprintf_ex(buffer, font, 10, 340, makecol(255, 255, 255), -1, "Le premier joueur qui arrive à un solde de 0 ticket a perdu.");
    textprintf_ex(buffer, font, 10, 380, makecol(255, 255, 255), -1, "EST-CE QUE C'EST BON POUR VOUS ?");

    //bordure
    rect(buffer, 5, 5, 795, 495, makecol(255, 255, 255));

    //affichage
    blit(buffer, screen, 0, 0, 0, 0, 800, 500);
    readkey();
}

void choix_cheval() {
    
    int choix1 = 0;
    int choix2 = 0;
    BITMAP *buffer = create_bitmap(800, 500);
    textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "JOUEUR 1,CHOISISSEZ VOTRE CHEVAL");
    textprintf_ex(buffer, font, 10, 30, makecol(255, 0, 0), -1, "1. CHEVAL 1");
    textprintf_ex(buffer, font, 10, 50, makecol(0, 128, 0), -1, "2. CHEVAL 2");
    textprintf_ex(buffer, font, 10, 70, makecol(255, 255, 0), -1, "3. CHEVAL 3");
    textprintf_ex(buffer, font, 10, 90, makecol(128, 0, 128), -1, "4. CHEVAL 4");
    textprintf_ex(buffer, font, 10, 110, makecol(255, 255, 255), -1, "5. QUITTER");
    blit(buffer, screen, 0, 0, 0, 0, 800, 500);
    while (choix1 == 0){
        if (key[KEY_1]){
            choix1 = 1;
        }
        if (key[KEY_2]){
            choix1 = 2;
        }
        if (key[KEY_3]){
            choix1 = 3;
        }
        if (key[KEY_4]){
            choix1 = 4;
        }
        if (key[KEY_5]){
            choix1 = 5;
        }
    }
    if (choix1 == 5){
        allegro_exit();
    }
    rest(2000);
    clear(buffer);
    textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "JOUEUR 2,CHOISISSEZ VOTRE CHEVAL");
    textprintf_ex(buffer, font, 10, 30, makecol(255, 0, 0), -1, "1. CHEVAL 1");
    textprintf_ex(buffer, font, 10, 50, makecol(0, 128, 0), -1, "2. CHEVAL 2");
    textprintf_ex(buffer, font, 10, 70, makecol(255, 255, 0), -1, "3. CHEVAL 3");
    textprintf_ex(buffer, font, 10, 90, makecol(128, 0, 128), -1, "4. CHEVAL 4");
    textprintf_ex(buffer, font, 10, 110, makecol(255, 255, 255), -1, "5. QUITTER");
    blit(buffer, screen, 0, 0, 0, 0, 800, 500);
    while (choix2 == 0){
        if (key[KEY_1]){
            choix2 = 1;
        }
        if (key[KEY_2]){
            choix2 = 2;
        }
        if (key[KEY_3]){
            choix2 = 3;
        }
        if (key[KEY_4]){
            choix2 = 4;
        }
        if (key[KEY_5]){
            choix2 = 5;
        }
    }
    if (choix2 == 5){
        allegro_exit();
    }
    clear(buffer);
    if (choix1 == choix2){
        textprintf_ex(buffer, font, 290, 250, makecol(255, 0, 0), -1, "VOUS AVEZ CHOISI LE MEME CHEVAL");
        textprintf_ex(buffer, font, 325, 270, makecol(255, 0, 0), -1, "VEUILLEZ RECOMMENCER");
        blit(buffer, screen, 0, 0, 0, 0, 800, 500);
        rest(2000);
        choix_cheval();
    }else{
        joueur joueur1;
        joueur joueur2;
        joueur1.chevalchoisi = choix1;
        joueur2.chevalchoisi = choix2;


    }
}



int main() {
    //initialisation d'Allegro
    allegro_init();
    install_keyboard();
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0);

    //chargement des bitmaps
    BITMAP* background = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\coursefinal.bmp", NULL);
    BITMAP* sprite1 = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\applejack1.bmp", NULL);
    BITMAP* sprite2 = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\purplewave1.bmp", NULL);
    BITMAP *sprite3 = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\rainbowdash1.bmp", NULL);
    BITMAP *sprite4 = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\purseypink1.bmp", NULL);


    //initialisation des variables de position et de vitesse pour chaque sprite
    int x1 = 99, y1 = 580, speed1 = rand() % 10 + 1;
    int x2 = 99, y2 = 550, speed2 = rand() % 10 + 1;
    int x3 = 99, y3 = 520, speed3 = rand() % 10 + 1;
    int x4 = 99, y4 = 490, speed4 = rand() % 10 + 1;



    // Boucle de jeu
    while (!key[KEY_ESC]) {
        //si toutes les vitesses sont égales, on relance le random pour tous les sprites
        if(speed4 == speed3 && speed3 == speed2 && speed2 == speed1){
            speed4 = rand() % 10 + 1;
            speed3 = rand() % 10 + 1;
            speed2 = rand() % 10 + 1;
            speed1 = rand() % 10 + 1;
        }
        //un meme sprite ne peut pas avoir la meme vitesse que lors du tour précédent
        if(speed4 == speed3 || speed4 == speed2 || speed4 == speed1){
            speed2 = rand() % 10 + 1;
        }
        if(speed3 == speed2 || speed3 == speed1){
            speed3 = rand() % 10 + 1;
        }
        if(speed2 == speed1){
            speed2 = rand() % 10 + 1;
        }

        // Affichage du fond
        blit(background, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        line(screen, 100, 530, 100, 703, makecol(255, 255, 0));
        line(screen, 1400, 530, 1400, 703, makecol(50, 0, 50));


        // Déplacement du sprite 1
        x1 += speed1;
        if (x1 > 1410) {
            allegro_message("Le sprite 1 a gagné !");
            break;
        }
        draw_sprite(screen, sprite1, x1, y1);

        // Déplacement du sprite 2
        x2 += speed2;
        if (x2 > 1410) {
            allegro_message("Le sprite 2 a gagné !");
            break;
        }
        draw_sprite(screen, sprite2, x2, y2);

        // Déplacement du sprite 3
        x3 += speed3;
        if (x3 > 1410) {
            allegro_message("Le sprite 3 a gagné !");
            break;
        }
        draw_sprite(screen, sprite3, x3, y3);

        // Déplacement du sprite 4
        x4 += speed4;
        if (x4 > 1410) {
            allegro_message("Le sprite 4 a gagné !");
            break;
        }
        draw_sprite(screen, sprite4, x4, y4);


    }

    // Libération de la mémoire allouée aux bitmaps
    destroy_bitmap(background);
    destroy_bitmap(sprite1);
    destroy_bitmap(sprite2);
    destroy_bitmap(sprite3);
    destroy_bitmap(sprite4);

    return 0;
}END_OF_MAIN();
