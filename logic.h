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
    SDL_Texture* muteButtonTexture;
    SDL_Texture* unmuteButtonTexture;
    SDL_Texture* muteButtonHoverTexture;
    SDL_Texture* unmuteButtonHoverTexture;
    float currentScale;
    float targetScale;
    float scaleSpeed;
    float soundButtonCurrentScale;
    float soundButtonTargetScale;
    float soundButtonScaleSpeed;

    Mix_Music* music;
    Mix_Chunk* startSound;
    Mix_Chunk* correctSound;
    Mix_Chunk* incorrectSound;
    Mix_Chunk* winSound;
    Mix_Chunk* loseSound;
    Mix_Chunk* hoverSound;

    string secretWord;
    string guessed_word;
    int count;
    int hidden;
    int trangthai;
    bool winSoundPlayed;
    bool loseSoundPlayed;
    bool wasPlayButtonHovered;
    bool wasSoundButtonHovered;
    bool isMuted;

    void init();
    void startGame();
    void render();
    void run();
    void upload(const char& input);
    void goiy();
    void cleanup();

    bool handleEvents();
    bool won();
    bool lost();
    bool end();

};
#endif
