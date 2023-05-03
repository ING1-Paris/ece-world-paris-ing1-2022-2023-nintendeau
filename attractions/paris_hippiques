//le but du projet est de créer un jeu de paris hippiques
//
//le jeu se joue à 2 joueurs
//
//chaque joueur commence avec un solde de 5 tickets
//
//le premier joueur qui arrive à un solde de 0 ticket a perdu
//
//le jeu ne s'arretera que lorsque l'un des joueurs aura perdu
//
//le joueur peut aussi choisir de quitter le jeu à tout moment grace à la touche echap
//
//le jeu se déroule sur une piste de 20 cases
//
//chaque joueur choisit un cheval parmi les 4 qui lui sont proposés
//
//chaque joueur mise un ou plusieurs tickets sur le cheval qu'il a choisi
//
//si le cheval choisi par le joueur gagne, le joueur remporte 2 fois sa mise
//
//si le cheval choisi par le joueur perd, le joueur perd un ticket
//
//le joueur peut miser plusieurs tickets sur un cheval
//
//il faut initilaliser les chevaux
//
//il faut initialiser les joueurs
//
//il faut initialiser les tickets
//
//il faut initialiser la piste
//
//il faut initialiser le jeu
//
//il faut initialiser le menu
//
//il faut relier les fonctions entre elles
//

//premiere etape : initialiser les chevaux
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

void choix_cheval();
void regles_jeu();
void initialiser_chevaux();
void initialiser_joueur();
void afficher_chevaux();
void afficher_decor();



void menu(){
    BITMAP *buffer = create_bitmap(800, 500);
    textprintf_ex(buffer, font, 400, 10, makecol(255, 255, 255), -1, "MENU");
    textprintf_ex(buffer, font, 10, 90, makecol(255, 255, 255), -1, "1. REGLES DU JEU");
    textprintf_ex(buffer, font, 10, 130, makecol(255, 255, 255), -1, "2. JOUER");
    textprintf_ex(buffer, font, 10, 170, makecol(255, 255, 255), -1, "3. QUITTER");
    blit(buffer, screen, 0, 0, 0, 0, 800, 500);
    int choix = 0;
    while (choix == 0){
        if (key[KEY_1]){
            choix = 1;
        }
        if (key[KEY_2]){
            choix = 2;
        }
        if (key[KEY_3]){
            choix = 3;
        }
    }
    if (choix == 1){
        regles_jeu();
    }
    if (choix == 2){
        choix_cheval();
    }
    if (choix == 3){
        allegro_exit();
    }
}

void regles_jeu(){
    install_keyboard();
    set_color_depth(32);
    BITMAP *buffer = create_bitmap(800, 500);
    textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "BIENVENUE DANS LE JEU PARIS HIPPIQUES");
    textprintf_ex(buffer, font, 10, 30, makecol(255, 255, 255), -1, "Avant de jouer, laissez moi vous expliquer les règles du jeu:");
    textprintf_ex(buffer, font, 10, 50, makecol(255, 255, 255), -1, "Vous serez 2 JOUEURS et vous allez devoir choisir un cheval parmi les 4 qui vous sont proposés.");
    textprintf_ex(buffer, font, 10, 70, makecol(255, 255, 255), -1, "Vous allez ensuite miser un ou plusieurs tickets sur ce cheval.");
    textprintf_ex(buffer, font, 10, 90, makecol(255, 255, 255), -1, "Si votre cheval gagne, vous remportez 2 fois votre mise.");
    textprintf_ex(buffer, font, 10, 110, makecol(255, 255, 255), -1, "Mais si vous perdez, vous perdez un ticket.");
    textprintf_ex(buffer, font, 10, 130, makecol(255, 255, 255), -1, "Chaque joueur commence avec un solde de 5 tickets.");
    textprintf_ex(buffer, font, 10, 150, makecol(255, 255, 255), -1, "Le premier joueur qui arrive à un solde de 0 ticket a perdu.");
    textprintf_ex(buffer, font, 10, 170, makecol(255, 255, 255), -1, "EST-CE QUE C'EST BON POUR VOUS ?");
    if(key[KEY_ENTER]){
        choix_cheval();
    }

}

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

void afficher_decor(){
    BITMAP *buffer = create_bitmap(800, 500);
    BITMAP *fond = load_bitmap("course.bmp", NULL);
    blit(fond, buffer, 0, 0, 0, 0, 800, 500);
    blit(buffer, screen, 0, 0, 0, 0, 800, 500);
}

void afficher_chevaux(){
    BITMAP *buffer = create_bitmap(800, 500);
    BITMAP *cheval1 = load_bitmap("cheval1.bmp", NULL);
    BITMAP *cheval2 = load_bitmap("cheval2.bmp", NULL);
    BITMAP *cheval3 = load_bitmap("cheval3.bmp", NULL);
    BITMAP *cheval4 = load_bitmap("cheval4.bmp", NULL);
    blit(cheval1, buffer, 0, 0, 0, 0, 800, 500);
    blit(cheval2, buffer, 0, 0, 0, 0, 800, 500);
    blit(cheval3, buffer, 0, 0, 0, 0, 800, 500);
    blit(cheval4, buffer, 0, 0, 0, 0, 800, 500);
    blit(buffer, screen, 0, 0, 0, 0, 800, 500);
}

void afficher_tout(){
    afficher_decor();
    afficher_chevaux();
}

void deplacer_chevaux(){
    cheval cheval1;
    cheval cheval2;
    cheval cheval3;
    cheval cheval4;
    cheval1.x = 207;
    cheval2.x = 207;
    cheval3.x = 207;
    cheval4.x = 207;

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
