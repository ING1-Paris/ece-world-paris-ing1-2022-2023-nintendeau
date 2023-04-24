//! Code principal du projet d'algo du dexieme semestre

//? Objectif: Creer un jeu de parc d'attraction.
//?  - possibilité de se deplacer sur la carte du parc, qui servira aussi de menu.
//?  - systeme de tickets pour participer aux attractions.
//?  - systeme de sauvegarde du meilleur score de chaque attractions.
//?  - chaque membre de l'equipe doit programmer integrallement au moins une attraction.

//& 4 fichiers .h seront mis en place dans le dossier "attractions" pour accueilir les codes des 4 attractions (4 membres de l'equipe).
//& les fichiers .h seront inclus dans le main.c, dans lequel le code principal sera ecrit.

#include <stdio.h>
#include <Allegro.h>


// Structure Player qui contient les informations du joueur
typedef struct {
    int x, y;
    int speed;
    int score;
    int tickets;
} Player;


// fonction pour ecrire le meilleur score dans le fichier "meilleurs_scores.txt"
void write_best_score(int score) {

    FILE * file = fopen("saves\\meilleurs_scores.txt", "w");

    if (!file) {
        file = fopen("../saves/meilleurs_scores.txt", "w");

        if (!file) {
            allegro_message("FILE ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    int best_score = 0;
    fscanf(file, "%d", &best_score);
    if (score > best_score) {
        fprintf(file, "%d\n", score);
    }
    fclose(file);
}


// afifcher le score
void afficher_score(BITMAP * score_image, BITMAP * buffer, Player player) {
    stretch_blit(score_image, buffer, 0, 0, score_image->w, score_image->h, 0, 0, SCREEN_W, SCREEN_H);
    textprintf_ex(buffer, font, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Score: %d", player.score);
}


// fonction d'affichage
void afficher_map(BITMAP * titre, BITMAP * buffer, BITMAP * map, BITMAP * player_sprite, Player player, int * can_move, BITMAP * score_image) {

    clear_bitmap(buffer);
    stretch_blit(map, buffer, 0, 0, map->w, map->h, 0, 0, buffer->w, buffer->h);
    masked_blit(player_sprite, buffer, 0, 0, player.x, player.y, player_sprite->w, player_sprite->h);
    masked_stretch_blit(titre, buffer, 0, 0, titre->w, titre->h, SCREEN_W/2 - titre->w/1.35, SCREEN_H/2 - titre->h*1.5, titre->w*1.5, titre->h*1.5);

    // enlever le titre si la souris est clique
    if (mouse_b & 1) {
        clear_to_color(titre, makecol(255, 0, 255));
        *can_move = 1;
    }

    // afficher le score si le joueur est sur la case "score"
    if (940 < player.x && player.x < 1000 && 100 < player.y && player.y < 200) {
        afficher_score(score_image, buffer, player);
    }

    blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
}


//! fonction principale
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


    //! VARIABLES
    int frame_count = 0;
    int can_move = 0;

    //! CHARGEMENT DES BITMAPS
    BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP * titre = load_bitmap("assets\\Titre.bmp", NULL);
    BITMAP * map = load_bitmap("assets\\map1.bmp", NULL);
    BITMAP * player_sprite = load_bitmap("assets\\anim_player_bas\\frame_1.bmp", NULL);
    BITMAP * score_image = load_bitmap("assets\\score.bmp", NULL);


    // si le chemin d'acces ne fonctionne pas, on essaye avec un autre chemin d'acces (pour Clion et vscode)
    if (!map || !player_sprite || !titre || !score_image) {
        map = load_bitmap("assets/map1.bmp", NULL);
        player_sprite = load_bitmap("../assets/anim_player_bas/frame_1.bmp", NULL);
        titre = load_bitmap("../assets/Titre.bmp", NULL);
        if (!map || !player_sprite) {
            allegro_message("BITMAP ERROR");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    //& reste du code principal
    // fait apparaitre le joueur au centre de l'ecran
    Player player = {200, 200, 4, 0, 5}; //!{x, y, width, height, speed, score}


    //& boucle principale du menu (carte du parc)
    while (!key[KEY_ESC]) {

        // deplacements du joueur (touches directionnelles)
        if (can_move) {
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
        }

        // gerer les collisions avec les bords de l'ecran
        if (player.x < 0) {
            player.x = 0;
        }
        if (player.x > SCREEN_W - player_sprite->w) {
            player.x = SCREEN_W - player_sprite->w;
        }
        if (player.y < 0) {
            player.y = 0;
        }
        if (player.y > SCREEN_H - player_sprite->h) {
            player.y = SCREEN_H - player_sprite->h;
        }

        // afficher le score du joueur en haut a gauche de l'ecran
        textprintf_ex(screen, font, 10, 10, makecol(0, 0, 0), -1, "Score: %d", player.score);

        // test pour le score
        if (mouse_x > player.x && mouse_x < player.x + player_sprite->w && mouse_y > player_sprite->h && mouse_y < player.y + player_sprite->h) {
            player.score++;
        }
        write_best_score(player.score);

        show_mouse(screen);

        // passer a la frame suivante de l'animation du joueur (4 frames)
        frame_count = (frame_count + 1) % 4;
        afficher_map(titre, buffer, map, player_sprite, player, &can_move, score_image);
    }

    readkey();
    allegro_exit();
    return 0;
}END_OF_MAIN();