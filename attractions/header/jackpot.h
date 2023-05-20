#ifndef JACKPOT_H
#define JACKPOT_H

typedef struct {
    int x, y;
    int number;
    int previous_x, previous_y;
    int direction, speed;
    int score, tickets;
    int leader;
    BITMAP * sprite;
    int color;
} Playerh;

// Function declaration
int jackpot(Playerh* player);

#endif // jackpot