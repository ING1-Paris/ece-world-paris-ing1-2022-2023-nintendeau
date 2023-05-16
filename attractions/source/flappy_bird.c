#include <llegro.h>
#include <stdbool.h>

#define SCREEN_W 640
#define SCREEN_H 480

int main() {
    allegro_init();
    install_keyboard();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0);

    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *square = create_bitmap(20, 20);
    clear_to_color(square, makecol(255, 255, 255));

    int square_x = SCREEN_W / 2 - square->w / 2;
    int square_y = SCREEN_H / 2 - square->h / 2;
    int square_dy = 0;

    int rect_x = SCREEN_W;
    int rect_y = 0;
    int rect_w = 20;
    int rect_h = SCREEN_H / 2;

    bool game_over = false;

    while (!key[KEY_ESC]) {
        clear_to_color(buffer, makecol(0, 0, 0));

        // Déplacer le carré
        if (!game_over) {
            if (key[KEY_SPACE]) {
                square_dy = -5;
            }

            square_y += square_dy;
            square_dy += 1;
        }

        // Vérifier si le carré est en collision avec l'obstacle
        if (square_x + square->w >= rect_x && square_x <= rect_x + rect_w) {
            if (square_y <= rect_y || square_y + square->h >= rect_y + rect_h) {
                // Collision détectée
                game_over = true;
                textout_centre_ex(buffer, font, "Perdu ! Appuyez sur Entree pour recommencer", SCREEN_W/2, SCREEN_H/2, makecol(255,255,255), -1);
            }
        }

        // Dessiner le carré et l'obstacle
        rectfill(buffer, rect_x, rect_y, rect_x + rect_w, rect_y + rect_h, makecol(255, 255, 255));
        draw_sprite(buffer, square, square_x, square_y);

        // Déplacer l'obstacle
        rect_x -= 5;
        if (rect_x + rect_w < 0) {
            rect_x = SCREEN_W;
            rect_h = rand() % (SCREEN_H / 2);
        }

        // Afficher le buffer à l'écran
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // Attendre un peu pour limiter la vitesse d'affichage
        rest(20);
    }

    destroy_bitmap(square);
    destroy_bitmap(buffer);

    return 0;
}
END_OF_MAIN();
