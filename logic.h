#ifndef HANGMAN_H
#define HANGMAN_H

#include "defs.h"
#include "graphics.h"

struct HangMan
{
    Graphics graphics;

    SDL_Texture* hangmanTextures[8];
    SDL_Texture* winTextures[6];
    SDL_Texture* loseTextures[4];
    SDL_Texture* backgroundTexture;
    SDL_Texture* titleTexture;
    SDL_Texture* playButtonTexture;
    SDL_Texture* playButtonHoverTexture;
    SDL_Texture* muteButtonTexture;
    SDL_Texture* unmuteButtonTexture;
    SDL_Texture* muteButtonHoverTexture;
    SDL_Texture* unmuteButtonHoverTexture;
    SDL_Texture* pauseButtonTexture;
    SDL_Texture* pauseButtonHoverTexture;
    SDL_Texture* homeButtonTexture;
    SDL_Texture* homeButtonHoverTexture;
    SDL_Texture* resumeButtonTexture;
    SDL_Texture* resumeButtonHoverTexture;
    SDL_Texture* replayButtonTexture;
    SDL_Texture* replayButtonHoverTexture;
    SDL_Texture* gameoverTexture;
    SDL_Texture* welldoneTexture;



    float currentScale;
    float targetScale;
    float scaleSpeed;
    float soundButtonCurrentScale;
    float soundButtonTargetScale;
    float soundButtonScaleSpeed;
    float pauseButtonCurrentScale;
    float pauseButtonTargetScale;
    float pauseButtonScaleSpeed;
    float homeButtonCurrentScale;
    float homeButtonTargetScale;
    float homeButtonScaleSpeed;
    float resumeButtonCurrentScale;
    float resumeButtonTargetScale;
    float resumeButtonScaleSpeed;
    float replayButtonCurrentScale;
    float replayButtonTargetScale;
    float replayButtonScaleSpeed;

    Mix_Music* music;
    Mix_Chunk* startSound;
    Mix_Chunk* correctSound;
    Mix_Chunk* incorrectSound;
    Mix_Chunk* winSound;
    Mix_Chunk* loseSound;
    Mix_Chunk* hoverSound;
    Mix_Chunk* clickSound;

    string secretWord;
    string guessed_word;
    string currentCategory;
    int count;
    int hidden;
    State trangthai;
    int score;
    int highScore;
    bool keyUsed[26];
    SDL_Rect keyRects[26];

    int animFrame;
    Uint32 animStartTime;
    bool isAnimating;
    const int ANIM_FRAME_DELAY = 100;

    bool winSoundPlayed;
    bool loseSoundPlayed;
    bool wasPlayButtonHovered;
    bool wasSoundButtonHovered;
    bool wasHomeButtonHovered;
    bool wasReplayButtonHovered;
    bool wasPauseButtonHovered;
    bool wasResumeButtonHovered;
    bool isMuted;

    void init();
    void startGame();
    void render();
    void run();
    void upload(const char& input);
    void cleanup();

    bool handleEvents();
    bool won();
    bool lost();
    bool end();

};
#endif
