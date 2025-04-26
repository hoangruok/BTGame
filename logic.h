#ifndef HANGMAN_H
#define HANGMAN_H

#include "rand_word.h"
#include "defs.h"
#include "graphics.h"
#include <SDL_mixer.h>

struct HangMan
{
    Graphics graphics;
    SDL_Texture* hangmanTextures[8];
    SDL_Texture* backgroundTexture;
    SDL_Texture* playButtonTexture;
    SDL_Texture* playButtonHoverTexture;
    SDL_Texture* titleTexture;
    Mix_Music* music;
    Mix_Chunk* startSound;
    Mix_Chunk* correctSound;
    Mix_Chunk* incorrectSound;
    Mix_Chunk* winSound;
    Mix_Chunk* loseSound;

    string secretWord;
    string guessed_word;
    int count;
    int hidden;
    int trangthai;
    bool winSoundPlayed;
    bool loseSoundPlayed;

    void init();
    void startGame();
    void render();
    void upload(const char& input);
    void goiy();
    void cleanup();
    bool won();
    bool lost();
    bool end();

};
#endif
