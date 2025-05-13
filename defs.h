#ifndef DEFS_H
#define DEFS_H

#include <bits/stdc++.h>
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define maxGuesses 7
#define WINDOW_TITLE "HangMan Game"
#define BG_COLOR_R 96
#define BG_COLOR_G 128
#define BG_COLOR_B 255
#define BG_COLOR_A 255

enum State {
    MENU,
    START,
    GOOD_GUESS,
    BAD_GUESS,
    PAUSED,
    END
};

#endif
