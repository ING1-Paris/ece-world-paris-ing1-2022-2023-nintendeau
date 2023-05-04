#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>

#define LONGUEUR 800
#define LARGEUR 500


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

void initialiser_chevaux();
void initialiser_joueur();
void choix_cheval();
void regles_jeu();
void afficher();

void initialiser_chevaux(){
    cheval cheval1;
    cheval cheval2;
    cheval cheval3;
    cheval cheval4;
    cheval1.x = 0;
    cheval1.y = 0;
    cheval1.dx = 0;
    cheval1.dy = 0;
    cheval2.x = 0;
    cheval2.y = 0;
    cheval2.dx = 0;
    cheval2.dy = 0;
    cheval3.x = 0;
    cheval3.y = 0;
    cheval3.dx = 0;
    cheval3.dy = 0;
    cheval4.x = 0;
    cheval4.y = 0;
    cheval4.dx = 0;
    cheval4.dy = 0;
}

void initialiser_joueur(){
    joueur joueur1;
    joueur joueur2;
    joueur1.soldetickets = 5;
    joueur1.chevalchoisi = 0;
    joueur2.soldetickets = 5;
    joueur2.chevalchoisi = 0;
}

void choix_cheval() {
    initialiser_chevaux();
    initialiser_joueur();
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

void afficher() {
   //charger l'image dans le buffer
    BITMAP *course = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\coursefinal.bmp", NULL);
    if(!course){
        allegro_message("Erreur lors du chargement de l'image");
        exit(EXIT_FAILURE);
    }
    //afficher l'image
    blit(course, screen, 0, 0, 0, 0, course->w, course->h);//

    //dessiner la ligne de depart de couleur jaune fluo sur l'image course, les coordonnées de la ligne sont (x = 67, y1 = 530, y2= 703)
    line(screen, 111, 530, 111, 703, makecol(255, 255, 0));

    //dessiner la ligne d'arrivée de couleur violet sur l'image course, les coordonnées de la ligne sont (x=1377, y1=530, y2=703)
    line(screen, 1377, 530, 1377, 707, makecol(255, 0, 255));


    //charger les chevaux dans le buffer
    BITMAP *cheval1 = load_bitmap("C:\\Users\\shaïma\\CLionProjects\\parishippiques\\images\\cat2.bmp", NULL);
    if(!cheval1){
        allegro_message("Erreur lors du chargement de l'image");
        exit(EXIT_FAILURE);
    }
    blit(cheval1, screen, 0, 0, 0, 500, cheval1->w, cheval1->h);
    //faire bouger le cheval 1 avec une vitesse aléatoire entre 1 et 10 pixels par seconde et afficher le cheval 1 sur l'image course
    deplacer_cheval1(cheval1);



}

//initalialiser la position du cheval 1
void init_cheval1(player1 *cheval1){
    cheval1->x1 = 0;
    cheval1->y = 500;
    cheval1->dx1 = 0;
    cheval1->dy1 = 0;
}

void deplacer_cheval1(player1 *cheval1){
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    //initialiser la position du cheval 1
    init_cheval1(cheval1);
    //afficher le cheval 1
    afficher();
    //dessiner le cheval 1 dans le buffer
    draw_sprite(buffer, cheval1, cheval1->x1, cheval1->y);
    //deplacer le cheval 1 avec une vitesse aléatoire entre 1 et 10 pixels par seconde
    cheval1->dx1 = rand() % 10 + 1;
    cheval1->x1 += cheval1->dx1;
    //afficher le buffer sur l'écran
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}



void condition_victoire(player1 *cheval1){
    if(cheval1->x1 == 1377 && getpixel(cheval1,cheval1->x1, cheval1->y) == makecol(255, 0, 255)){
        allegro_message("Le cheval 1 a gagné");
    }
}


int main(){
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 500, 0, 0);
    BITMAP *buffer = create_bitmap(800, 500);
    textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "BIENVENUE DANS LE JEU DE LA COURSE DE CHEVAUX");
    textprintf_ex(buffer, font, 10, 30, makecol(255, 255, 255), -1, "LE BUT DU JEU EST DE CHOISIR LE CHEVAL GAGNANT");
    textprintf_ex(buffer, font, 10, 50, makecol(255, 255, 255), -1, "POUR CELA, VOUS DEVEZ CHOISIR UN CHEVAL ENTRE 1 ET 4");
    textprintf_ex(buffer, font, 10, 70, makecol(255, 255, 255), -1, "SI VOUS GAGNEZ, VOUS GAGNEZ UN TICKET.");
    textprintf_ex(buffer, font, 10, 90, makecol(255, 255, 255), -1, "SI VOUS PERDEZ, VOUS PERDEZ UN TICKET.");
    textprintf_ex(buffer, font, 10, 110, makecol(255, 255, 255), -1, "LE PREMIER JOUEUR QUI AURA 0 TICKET AURA PERDU.");
    textprintf_ex(buffer, font, 10, 130, makecol(255, 255, 255), -1, "BONNE CHANCE !");
    textprintf_ex(buffer, font, 10, 150, makecol(255, 255, 255), -1, "APPUYEZ SUR ENTREE POUR CONTINUER");
    blit(buffer, screen, 0, 0, 0, 0, 800, 500);
    while (!key[KEY_ENTER]){
    }
    clear(buffer);
    if (key[KEY_ENTER]){
        choix_cheval();
    }
    return 0;
}END_OF_MAIN();
