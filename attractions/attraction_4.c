#include <stdio.h>
#include <time.h>
#include <allegro.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));

    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0) != 0) {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);

    int cvert = makecol(0, 255, 0) , cbleu = makecol(0, 0, 255);
    int fin=0;
    int nbrtaupesJ1 = 0, nbrtaupesJ2 = 0;

    while(!fin){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                rectfill(screen, 130 + i * 150, 100 + j * 150, 130 + i * 150 + 100, 100 + j * 150 + 100, cvert);
            }
        }
        int rectbleu = rand() % 12 + 1;
        int tempsderepos = rand() % 500 + 1000;

        if  (rectbleu == 1) {
            rectfill(screen, 130, 100, 130 + 100, 100 + 100, cbleu);
            rest (tempsderepos);
            rectfill(screen, 130, 100, 130 + 100, 100 + 100, cvert);
            rest (tempsderepos);
        }else if (rectbleu == 2) {
            rectfill(screen, 130 + 150, 100, 130 + 150 + 100, 100 + 100, cbleu);
            rest (tempsderepos);
            rectfill(screen, 130 + 150, 100, 130 + 150 + 100, 100 + 100, cvert);
            rest (tempsderepos);
        }else if (rectbleu == 3) {
            rectfill(screen, 130 + 300, 100, 130 + 300 + 100, 100 + 100, cbleu);
            rest (tempsderepos);
            rectfill(screen, 130 + 300, 100, 130 + 300 + 100, 100 + 100, cvert);
            rest (tempsderepos);
        }else if (rectbleu == 4) {
            rectfill(screen, 130 + 450, 100, 130 + 450 + 100, 100 + 100, cbleu);
            rest (tempsderepos);
            rectfill(screen, 130 + 450, 100, 130 + 450 + 100, 100 + 100, cvert);
            rest (tempsderepos);
        }else if (rectbleu == 5) {
            rectfill(screen, 130, 100 + 150, 130 + 100, 100 + 150 + 100, cbleu);
            rest (tempsderepos);
            rectfill(screen, 130, 100 + 150, 130 + 100, 100 + 150 + 100, cvert);
            rest (tempsderepos);
        }else if (rectbleu == 6) {
            rectfill(screen, 130 + 150, 100 + 150, 130 + 150 + 100, 100 + 150 + 100, cbleu);
            rest (tempsderepos);
            rectfill(screen, 130 + 150, 100 + 150, 130 + 150 + 100, 100 + 150 + 100, cvert);
            rest (tempsderepos);
        }else if (rectbleu == 7) {
            rectfill(screen, 130 + 300, 100 + 150, 130 + 300 + 100, 100 + 150 + 100, cbleu);
            rest (tempsderepos);
            rectfill(screen, 130 + 300, 100 + 150, 130 + 300 + 100, 100 + 150 + 100, cvert);
            rest (tempsderepos);
        }else if (rectbleu == 8) {
            rectfill(screen, 130 + 450, 100 + 150, 130 + 450 + 100, 100 + 150 + 100, cbleu);
            rest (tempsderepos);
            rectfill(screen, 130 + 450, 100 + 150, 130 + 450 + 100, 100 + 150 + 100, cvert);
            rest (tempsderepos);
        }else if (rectbleu == 9) {
            rectfill(screen, 130, 100 + 300, 130 + 100, 100 + 300 + 100, cbleu);
            rest (tempsderepos);
            rectfill(screen, 130, 100 + 300, 130 + 100, 100 + 300 + 100, cvert);
            rest (tempsderepos);
        }else if (rectbleu == 10) {
            rectfill(screen, 130 + 150, 100 + 300, 130 + 150 + 100, 100 + 300 + 100, cbleu);
            rest (tempsderepos);
            rectfill(screen, 130 + 150, 100 + 300, 130 + 150 + 100, 100 + 300 + 100, cvert);
            rest (tempsderepos);
        }else if (rectbleu == 11) {
            rectfill(screen, 130 + 300, 100 + 300, 130 + 300 + 100, 100 + 300 + 100, cbleu);
            rest (tempsderepos);
            rectfill(screen, 130 + 300, 100 + 300, 130 + 300 + 100, 100 + 300 + 100, cvert);
            rest (tempsderepos);
        }else if (rectbleu == 12) {
            rectfill(screen, 130 + 450, 100 + 300, 130 + 450 + 100, 100 + 300 + 100, cbleu);
            rest (tempsderepos);
            rectfill(screen, 130 + 450, 100 + 300, 130 + 450 + 100, 100 + 300 + 100, cvert);
            rest (tempsderepos);
        }
        
        
        if (mouse_b & 1 && mouse_x > 130 && mouse_x < 130 + 100 && mouse_y > 100 && mouse_y < 100 + 100 && getpixel(screen, 131, 101)) {
            nbrtaupesJ1++;
            rectfill(screen, 130, 100, 130 + 100, 100 + 100, cvert);
        }else if (mouse_b & 1 && mouse_x > 130 + 150 && mouse_x < 130 + 100 + 150 && mouse_y > 100 && mouse_y < 100 + 100 && getpixel(screen, 131, 101)){
            nbrtaupesJ1++;
            rectfill(screen, 130 + 150, 100, 130 + 100 + 150, 100 + 100, cvert);
        }else if (mouse_b & 1 && mouse_x > 130 + 150 && mouse_x < 130 + 100 + 150 && mouse_y > 100 && mouse_y < 100 + 100 && getpixel(screen, 131, 101)) {
            nbrtaupesJ1++;
            rectfill(screen, 130 + 150, 100, 130 + 100 + 150, 100 + 100, cvert);
        }else if (mouse_b & 1 && mouse_x > 130 + 150 && mouse_x < 130 + 100 + 150 && mouse_y > 100 && mouse_y < 100 + 100 && getpixel(screen, 131, 101)){
            nbrtaupesJ1++;
            rectfill(screen, 130 + 150, 100, 130 + 100 + 150, 100 + 100, cvert);
        }else if (mouse_b & 1 && mouse_x > 130 + 300 && mouse_x < 130 + 100 + 300 && mouse_y > 100 && mouse_y < 100 + 100 && getpixel(screen, 131, 101)){
            nbrtaupesJ1++;
            rectfill(screen, 130 + 300, 100, 130 + 100 + 300, 100 + 100, cvert);
        }else if (mouse_b & 1 && mouse_x > 130 + 450 && mouse_x < 130 + 100 + 450 && mouse_y > 100 && mouse_y < 100 + 100 && getpixel(screen, 131, 101)){
            nbrtaupesJ1++;
            rectfill(screen, 130 + 450, 100, 130 + 100 + 450, 100 + 100, cvert);
        }else if (mouse_b & 1 && mouse_x > 130 && mouse_x < 130 + 100 && mouse_y > 100 + 150 && mouse_y < 100 + 100 + 150 && getpixel(screen, 131, 101)){
            nbrtaupesJ1++;
            rectfill(screen, 130, 100 + 150, 130 + 100, 100 + 150 + 100, cvert);
        }else if (mouse_b & 1 && mouse_x > 130 + 150 && mouse_x < 130 + 100 + 150 && mouse_y > 100 + 150 && mouse_y < 100 + 100 + 150 && getpixel(screen, 131, 101)){
            nbrtaupesJ1++;
            rectfill(screen, 130 + 150, 100 + 150, 130 + 100 + 150, 100 + 150 + 100, cvert);
        }else if (mouse_b & 1 && mouse_x > 130 + 300 && mouse_x < 130 + 100 + 300 && mouse_y > 100 + 150 && mouse_y < 100 + 100 + 150 && getpixel(screen, 131, 101)){
            nbrtaupesJ1++;
            rectfill(screen, 130 + 300, 100 + 150, 130 + 100 + 300, 100 + 150 + 100, cvert);
        }else if (mouse_b & 1 && mouse_x > 130 + 450 && mouse_x < 130 + 100 + 450 && mouse_y > 100 + 150 && mouse_y < 100 + 100 + 150 && getpixel(screen, 131, 101)){
            nbrtaupesJ1++;
            rectfill(screen, 130 + 450, 100 + 150, 130 + 100 + 450, 100 + 150 + 100, cvert);
        }else if (mouse_b & 1 && mouse_x > 130 && mouse_x < 130 + 100 && mouse_y > 100 + 300 && mouse_y < 100 + 100 + 300 && getpixel(screen, 131, 101)){
            nbrtaupesJ1++;
            rectfill(screen, 130, 100 + 300, 130 + 100, 100 + 300 + 100, cvert);
        }else if (mouse_b & 1 && mouse_x > 130 + 150 && mouse_x < 130 + 100 + 150 && mouse_y > 100 + 300 && mouse_y < 100 + 100 + 300 && getpixel(screen, 131, 101)){
            nbrtaupesJ1++;
            rectfill(screen, 130 + 150, 100 + 300, 130 + 100 + 150, 100 + 300 + 100, cvert);
        }
    }
}
END_OF_MAIN();
