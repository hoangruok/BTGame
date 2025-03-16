#ifndef HANGMAN_H
#define HANGMAN_H

#include "rand_word.h"
#include "defs.h"
#include "graphics.h"

struct HangMan
{
    Graphics graphics;
    SDL_Texture* hangmanTextures[9];
    SDL_Texture* backgroundTexture;

    string secretWord;
    string guessed_word;
    int count;
    int hidden;
    int trangthai;

    void init();
    void startGame();
    void render();
    void upload(const char& input);
    void goiy();
    bool won();
    bool lost();
    bool end();
};
#endif
