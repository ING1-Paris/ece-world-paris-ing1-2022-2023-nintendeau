#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x, y;
    int number;
    int previous_x, previous_y;
    int direction, speed;
    int score, tickets;
    int leader;
    BITMAP * sprite;
    int color;
    char name[100];
} Player;

#endif // PLAYER_H
