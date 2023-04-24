//! Code principal du projet d'algo du dexieme semestre

//? Objectif: Creer un jeu de parc d'attraction.
//?  - possibilité de se deplacer sur la carte du parc, qui servira aussi de menu.
//?  - systeme de tickets pour participer aux attractions.
//?  - systeme de sauvegarde des scores.
//?  - chaque membre de l'equipe doit programmer integrallement au moins une attraction.

//& 4 fichiers .h seront mis en place dans le dossier "attractions" pour accueilir les codes des 4 attractions (4 membres de l'equipe).
//& les fichiers .h seront inclus dans le main.c, dans lequel le code principal sera ecrit.

#include <stdio.h>
#include <Allegro.h>


// Structure Player qui contient les informations du joueur
typedef struct {
    int x, y;
    int width, height;
    int speed;
    int score;
    int tickets;
} Player;

int main() {

    //& initialisation de la fenetre, de la souris et du clavier
    allegro_init();
    install_keyboard();
    install_mouse();

    set_window_title("Projet Algo S2");
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1200, 800, 0, 0) != 0) {
        allegro_message("GFX ERROR");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    //& charger les images (compaptible avec vscode et Clion grace au if)
    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * map = load_bitmap("assets\\map1.bmp", NULL);
    BITMAP * player_sprite = load_bitmap("assets\\character_resized.bmp", NULL);

    if (!map || !player_sprite) {
        map = load_bitmap("../assets/map.bmp", NULL);
        player_sprite = load_bitmap("../assets/player.bmp", NULL);
        if (!map || !player_sprite) {
            allegro_message("Error loading image");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }


    //& reste du code principal
    // fait apparaitre le joueur au centre de l'ecran
    Player player = {SCREEN_W / 2, SCREEN_H / 2, player_sprite->w, player_sprite->h, 4, 0, 5}; //!{x, y, width, height, speed, score}


    while (!key[KEY_ESC]) {
        //& boucle principale du menu (carte du parc)


        // deplacements du joueur (touches directionnelles)
        if (key[KEY_LEFT]) {
            player.x -= player.speed;
        }
        if (key[KEY_RIGHT]) {
            player.x += player.speed;
        }
        if (key[KEY_UP]) {
            player.y -= player.speed;
        }
        if (key[KEY_DOWN]) {
            player.y += player.speed;
        }

        // gerer les collisions avec les bords de l'ecran
        if (player.x < 0) {
            player.x = 0;
        }
        if (player.x > SCREEN_W - player.width) {
            player.x = SCREEN_W - player.width;
        }
        if (player.y < 0) {
            player.y = 0;
        }
        if (player.y > SCREEN_H - player.height) {
            player.y = SCREEN_H - player.height;
        }

        // afficher le score du joueur en haut a gauche de l'ecran
        textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "Score: %d", player.score);


        // test pour le score
        if (mouse_x > player.x && mouse_x < player.x + player.width && mouse_y > player.y && mouse_y < player.y + player.height) {
            player.score++;
        }
        show_mouse(screen);

        // afficher le joueur et la carte
        clear_bitmap(buffer);
        stretch_blit(map, buffer, 0, 0, map->w, map->h, 0, 0, buffer->w, buffer->h);
        masked_blit(player_sprite, buffer, 0, 0, player.x, player.y, player_sprite->w, player_sprite->h);
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    }

    readkey();
    allegro_exit();
    return 0;
}END_OF_MAIN();