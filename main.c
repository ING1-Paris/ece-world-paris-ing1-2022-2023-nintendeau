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


//define a new structure for the player (the player is a rectangle)
typedef struct {
    int x, y;
    int width, height;
    int speed;
    int score;
} Player;

int main() {

    // initialisation de la fenetre, de la souris et du clavier
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

    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * map = load_bitmap("C:\\Users\\ASUS ROG ALFRED\\Documents\\CODE\\ALGO\\SEMESTRE 2\\PROJET_ALGO_S2\\PROJET_ALGO_S2_POUR_DE_VRAI\\ece-world-paris-ing1-2022-2023-nintendeau\\assets\\map.bmp", NULL);
    BITMAP * player_sprite = load_bitmap("C:\\Users\\ASUS ROG ALFRED\\Documents\\CODE\\ALGO\\SEMESTRE 2\\PROJET_ALGO_S2\\PROJET_ALGO_S2_POUR_DE_VRAI\\ece-world-paris-ing1-2022-2023-nintendeau\\assets\\player.bmp", NULL);


    if (!map) {
        allegro_message("Error loading image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    // reste du code principal
    //summon the player at the center of the window
    Player player = {SCREEN_W / 2, SCREEN_H / 2, player_sprite->w, player_sprite->h, 7, 0}; //!{x, y, width, height, speed, score}


    while (!key[KEY_ESC]) {
        // boucle principale du menu (carte du parc)

        //clear the screen
        //clear_to_color(screen, makecol(0, 0, 0));

        //using arrow keys to move the rectangle around
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


        textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "Score: %d", player.score);

        //if the player is out of the screen, he will be summoned at the center
        if (player.x < 0 || player.x > SCREEN_W) {
            player.x = SCREEN_W / 2;
            player.y = SCREEN_H / 2;
        }
        if (player.y < 0 || player.y > SCREEN_H) {
            player.x = SCREEN_W / 2;
            player.y = SCREEN_H / 2;
        }

        //if the player touch the mouse, he earns 1 point
        if (mouse_x > player.x && mouse_x < player.x + player.width && mouse_y > player.y && mouse_y < player.y + player.height) {
            player.score++;
        }
        show_mouse(screen);

        // Pause de 10 millisecondes pour ralentir la boucle
        //rest(10);
        clear_bitmap(buffer);
        stretch_blit(map, buffer, 0, 0, map->w, map->h, 0, 0, buffer->w, buffer->h);
        masked_blit(player_sprite, buffer, 0, 0, player.x, player.y, player_sprite->w, player_sprite->h);
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    }

    readkey();
    allegro_exit();
    return 0;
}END_OF_MAIN();