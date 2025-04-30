#include "rand_word.h"
#include "defs.h"
#include "graphics.h"
#include "logic.h"
#include "input.h"

using namespace std;

void HangMan::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "SDL_INIT failed: " << SDL_GetError() << endl;
        exit(1);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "SDL_mixer init error: " << Mix_GetError() << endl;
    }

    graphics.init();

    backgroundTexture = graphics.loadTexture("background.png");
    if (!backgroundTexture) {
        cerr << "Failed to load background.png" << endl;
    }

    titleTexture = graphics.loadTexture("gameTitle.png");
    if (!titleTexture) {
        cerr << "Failed to load gameTitle.png" << endl;
    }

    playButtonTexture = graphics.loadTexture("playButton.png");
    if (!playButtonTexture) {
        cerr << "Failed to load playButton.png" << endl;
    }

    playButtonHoverTexture = graphics.loadTexture("playButtonHover.png");
    if (!playButtonHoverTexture) {
        cerr << "Failed to load playButtonHover.png" << endl;
    }

    muteButtonTexture = graphics.loadTexture("muteButton.png");
    if (!muteButtonTexture) {
        cerr << "Failed to load muteButton.png" << endl;
    }

    unmuteButtonTexture = graphics.loadTexture("unmuteButton.png");
    if (!unmuteButtonTexture) {
        cerr << "Failed to load unmuteButton.png" << endl;
    }

    muteButtonHoverTexture = graphics.loadTexture("muteButtonHover.png");
    if (!muteButtonHoverTexture) {
        cerr << "Failed to load muteButtonHover.png" << endl;
    }

    unmuteButtonHoverTexture = graphics.loadTexture("unmuteButtonHover.png");
    if (!unmuteButtonHoverTexture) {
        cerr << "Failed to load unmuteButtonHover.png" << endl;
    }

    pauseButtonTexture = graphics.loadTexture("pauseButton.png");
    if (!pauseButtonTexture) {
        cerr << "Failed to load pauseButton.png" << endl;
    }

    pauseButtonHoverTexture = graphics.loadTexture("pauseButtonHover.png");
    if (!pauseButtonHoverTexture) {
        cerr << "Failed to load pauseButtonHover.png" << endl;
    }

    homeButtonTexture = graphics.loadTexture("homeButton.png");
    if (!homeButtonTexture) {
        cerr << "Failed to load homeButton.png" << endl;
    }

    homeButtonHoverTexture = graphics.loadTexture("homeButtonHover.png");
    if (!homeButtonHoverTexture) {
        cerr << "Failed to load homeButtonHover.png" << endl;
    }

    resumeButtonTexture = graphics.loadTexture("resumeButton.png");
    if (!resumeButtonTexture) {
        cerr << "Failed to load resumeButton.png" << endl;
    }

    resumeButtonHoverTexture = graphics.loadTexture("resumeButtonHover.png");
    if (!resumeButtonHoverTexture) {
        cerr << "Failed to load resumeButtonHover.png" << endl;
    }

    replayButtonTexture = graphics.loadTexture("replayButton.png");
    if (!replayButtonTexture) {
        cerr << "Failed to load replayButton.png" << endl;
    }

    replayButtonHoverTexture = graphics.loadTexture("replayButtonHover.png");
    if (!replayButtonHoverTexture) {
        cerr << "Failed to load replayButtonHover.png" << endl;
    }

    const char* hangmanFiles[] = {
        "hangman0.png", "hangman1.png", "hangman2.png", "hangman3.png",
        "hangman4.png", "hangman5.png", "hangman6.png", "hangman7.png"
    };
    for (int i = 0; i < 8; i++) {
        hangmanTextures[i] = graphics.loadTexture(hangmanFiles[i]);
        if (!hangmanTextures[i]) {
            cerr << "Failed to load " << hangmanFiles[i] << ": " << IMG_GetError() << endl;
        }
    }

    music = Mix_LoadMUS("Music.mp3");
    if(!music){
        cerr << "Failed to load Music.mp3";
    }
    else {
        Mix_PlayMusic(music, -1);
        Mix_VolumeMusic(20);
    }

    startSound = Mix_LoadWAV("start.wav");
    if (!startSound) cerr << "Failed to load start.wav: " << Mix_GetError() << endl;
    else Mix_VolumeChunk(startSound, 64);

    correctSound = Mix_LoadWAV("correct.wav");
    if (!correctSound) cerr << "Failed to load correct.wav: " << Mix_GetError() << endl;
    else Mix_VolumeChunk(correctSound, 32);

    incorrectSound = Mix_LoadWAV("incorrect.wav");
    if (!incorrectSound) cerr << "Failed to load incorrect.wav: " << Mix_GetError() << endl;
    else Mix_VolumeChunk(incorrectSound, 32);

    winSound = Mix_LoadWAV("win.wav");
    if (!winSound) cerr << "Failed to load win.wav: " << Mix_GetError() << endl;
    else Mix_VolumeChunk(winSound, 32);

    loseSound = Mix_LoadWAV("lose.wav");
    if (!loseSound) cerr << "Failed to load lose.wav: " << Mix_GetError() << endl;
    else Mix_VolumeChunk(loseSound, 32);

    hoverSound = Mix_LoadWAV("hover.wav");
    if (!hoverSound) cerr << "Failed to load hover.wav: " << Mix_GetError() << endl;
    else Mix_VolumeChunk(hoverSound, 64);

    trangthai = MENU;
    winSoundPlayed = false;
    loseSoundPlayed = false;
    isMuted = false;
    currentScale = 1.0f;
    targetScale = 1.0f;
    scaleSpeed = 0.25f;
    soundButtonCurrentScale = 1.0f;
    soundButtonTargetScale = 1.0f;
    soundButtonScaleSpeed = 0.25f;
    pauseButtonCurrentScale = 1.0f;
    pauseButtonTargetScale = 1.0f;
    pauseButtonScaleSpeed = 0.25f;
    homeButtonCurrentScale = 1.0f;
    homeButtonTargetScale = 1.0f;
    homeButtonScaleSpeed = 0.25f;
    resumeButtonCurrentScale = 1.0f;
    resumeButtonTargetScale = 1.0f;
    resumeButtonScaleSpeed = 0.25f;
    replayButtonCurrentScale = 1.0f;
    replayButtonTargetScale = 1.0f;
    replayButtonScaleSpeed = 0.25f;
    wasPlayButtonHovered = false;
    wasSoundButtonHovered = false;
    wasHomeButtonHovered = false;
    wasReplayButtonHovered = false;
    wasPauseButtonHovered = false;
}

void HangMan::startGame()
{
    secretWord = getword("words.txt");
    guessed_word = string(secretWord.size(), '_');
    hidden = (int)secretWord.size();
    trangthai = START;
    count = 0;
    winSoundPlayed = false;
    loseSoundPlayed = false;
    currentScale = 1.0f;
    targetScale = 1.0f;
    soundButtonCurrentScale = 1.0f;
    soundButtonTargetScale = 1.0f;
    if (startSound) Mix_PlayChannel(-1, startSound, 0);
}

void HangMan::run()
{
    bool running = true;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (running) {
        frameStart = SDL_GetTicks();

        running = handleEvents();
        render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

bool HangMan::handleEvents()
{
    SDL_Event event;
    bool running = true;
    while (SDL_PollEvent(&event)) {
        char input = getInput(event, running);
        if (!running) return false;

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                if (trangthai == START || trangthai == GOOD_GUESS || trangthai == BAD_GUESS) {
                    trangthai = PAUSED;
                }
                else if (trangthai == PAUSED) {
                    trangthai = START;
                }
            }
        }

        if (trangthai == MENU) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                int buttonWidth, buttonHeight;
                SDL_QueryTexture(playButtonTexture, NULL, NULL, &buttonWidth, &buttonHeight);
                int buttonX = (SCREEN_WIDTH - buttonWidth) / 2;
                int buttonY = (SCREEN_HEIGHT - buttonHeight) / 2;
                if (x >= buttonX && x <= buttonX + buttonWidth && y >= buttonY && y <= buttonY + buttonHeight) {
                    startGame();
                    goiy();
                }
            }
        }
        else if (trangthai == PAUSED) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            int homeButtonWidth, homeButtonHeight;
            SDL_QueryTexture(homeButtonTexture, NULL, NULL, &homeButtonWidth, &homeButtonHeight);
            int homeButtonCenterX = SCREEN_WIDTH / 2 - 80;
            int homeButtonCenterY = SCREEN_HEIGHT / 2 + 50;

            int homeButtonNewWidth = static_cast<int>(homeButtonWidth * homeButtonCurrentScale);
            int homeButtonNewHeight = static_cast<int>(homeButtonHeight * homeButtonCurrentScale);
            int homeButtonX = homeButtonCenterX - homeButtonNewWidth / 2;
            int homeButtonY = homeButtonCenterY - homeButtonNewHeight / 2;

            if (x >= homeButtonX && x <= homeButtonX + homeButtonNewWidth &&
                y >= homeButtonY && y <= homeButtonY + homeButtonNewHeight) {
                trangthai = MENU;
                currentScale = 1.0f;
                targetScale = 1.0f;
                continue;
            }

            int resumeButtonWidth, resumeButtonHeight;
            SDL_QueryTexture(resumeButtonTexture, NULL, NULL, &resumeButtonWidth, &resumeButtonHeight);
            int resumeButtonCenterX = SCREEN_WIDTH / 2;
            int resumeButtonCenterY = SCREEN_HEIGHT / 2 + 50;

            int resumeButtonNewWidth = static_cast<int>(resumeButtonWidth * resumeButtonCurrentScale);
            int resumeButtonNewHeight = static_cast<int>(resumeButtonHeight * resumeButtonCurrentScale);
            int resumeButtonX = resumeButtonCenterX - resumeButtonNewWidth / 2;
            int resumeButtonY = resumeButtonCenterY - resumeButtonNewHeight / 2;

            if (x >= resumeButtonX && x <= resumeButtonX + resumeButtonNewWidth &&
                y >= resumeButtonY && y <= resumeButtonY + resumeButtonNewHeight) {
                trangthai = START;
                continue;
            }

            int replayButtonWidth, replayButtonHeight;
            SDL_QueryTexture(replayButtonTexture, NULL, NULL, &replayButtonWidth, &replayButtonHeight);
            int replayButtonCenterX = SCREEN_WIDTH / 2 + 80;
            int replayButtonCenterY = SCREEN_HEIGHT / 2 + 50;

            int replayButtonNewWidth = static_cast<int>(replayButtonWidth * replayButtonCurrentScale);
            int replayButtonNewHeight = static_cast<int>(replayButtonHeight * replayButtonCurrentScale);
            int replayButtonX = replayButtonCenterX - replayButtonNewWidth / 2;
            int replayButtonY = replayButtonCenterY - replayButtonNewHeight / 2;

            if (x >= replayButtonX && x <= replayButtonX + replayButtonNewWidth &&
                y >= replayButtonY && y <= replayButtonY + replayButtonNewHeight) {
                startGame();
                goiy();
                continue;
            }
        }
    }

        else if (input != 0) {
            upload(input);
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (trangthai == START || trangthai == GOOD_GUESS || trangthai == BAD_GUESS) {
                int pauseButtonWidth, pauseButtonHeight;
                SDL_QueryTexture(pauseButtonTexture, NULL, NULL, &pauseButtonWidth, &pauseButtonHeight);
                int pauseButtonNewWidth = static_cast<int>(pauseButtonWidth * pauseButtonCurrentScale);
                int pauseButtonNewHeight = static_cast<int>(pauseButtonHeight * pauseButtonCurrentScale);
                int pauseButtonCenterX = SCREEN_WIDTH - 10 - pauseButtonWidth / 2;
                int pauseButtonCenterY = 10 + pauseButtonHeight / 2;
                int pauseButtonX = pauseButtonCenterX - pauseButtonNewWidth / 2;
                int pauseButtonY = pauseButtonCenterY - pauseButtonNewHeight / 2;
                if (x >= pauseButtonX && x <= pauseButtonX + pauseButtonNewWidth &&
                    y >= pauseButtonY && y <= pauseButtonY + pauseButtonNewHeight) {
                    trangthai = PAUSED;
                    continue;
                }
            }

            SDL_Texture* soundButtonTexture = isMuted ? unmuteButtonTexture : muteButtonTexture;
            if (soundButtonTexture) {
                int buttonWidth, buttonHeight;
                SDL_QueryTexture(soundButtonTexture, NULL, NULL, &buttonWidth, &buttonHeight);
                int newWidth = static_cast<int>(buttonWidth * soundButtonCurrentScale);
                int newHeight = static_cast<int>(buttonHeight * soundButtonCurrentScale);
                int centerX = SCREEN_WIDTH - 10 - buttonWidth / 2;
                int centerY = SCREEN_HEIGHT - 10 - buttonHeight / 2;
                int buttonX = centerX - newWidth / 2;
                int buttonY = centerY - newHeight / 2;
                if (x >= buttonX && x <= buttonX + newWidth && y >= buttonY && y <= buttonY + newHeight) {
                    isMuted = !isMuted;
                    if (isMuted) {
                        if (music) Mix_VolumeMusic(0);
                        if (startSound) Mix_VolumeChunk(startSound, 0);
                        if (correctSound) Mix_VolumeChunk(correctSound, 0);
                        if (incorrectSound) Mix_VolumeChunk(incorrectSound, 0);
                        if (winSound) Mix_VolumeChunk(winSound, 0);
                        if (loseSound) Mix_VolumeChunk(loseSound, 0);
                        if (hoverSound) Mix_VolumeChunk(hoverSound, 0);
                    } else {
                        if (music) Mix_VolumeMusic(20);
                        if (startSound) Mix_VolumeChunk(startSound, 64);
                        if (correctSound) Mix_VolumeChunk(correctSound, 32);
                        if (incorrectSound) Mix_VolumeChunk(incorrectSound, 32);
                        if (winSound) Mix_VolumeChunk(winSound, 32);
                        if (loseSound) Mix_VolumeChunk(loseSound, 32);
                        if (hoverSound) Mix_VolumeChunk(hoverSound, 64);
                    }
                }
            }
        }

        if (end() && trangthai != MENU) {
            if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
                return false;
            }
        }
    }
    return true;
}

void HangMan::render()
{
    graphics.prepareScene();

    if (backgroundTexture) {
        graphics.renderTexture(backgroundTexture, 0, 0);
    }

    SDL_Color black = {0, 0, 0, 255};
    if(trangthai == MENU)
    {
        if (titleTexture) {
            int titleWidth, titleHeight;
            SDL_QueryTexture(titleTexture, NULL, NULL, &titleWidth, &titleHeight);
            int titleX = (SCREEN_WIDTH - titleWidth) / 2;
            int titleY = 30;
            SDL_Rect titleRect = {titleX, titleY, titleWidth, titleHeight};
            SDL_RenderCopy(graphics.getRenderer(), titleTexture, NULL, &titleRect);
        }

        int buttonWidth, buttonHeight;
        SDL_QueryTexture(playButtonTexture, NULL, NULL, &buttonWidth, &buttonHeight);

        int buttonX = (SCREEN_WIDTH - buttonWidth) / 2;
        int buttonY = (SCREEN_HEIGHT - buttonHeight) / 2;

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        bool isHovering = (mouseX >= buttonX && mouseX <= buttonX + buttonWidth &&
                           mouseY >= buttonY && mouseY <= buttonY + buttonHeight);

        targetScale = isHovering ? 1.2f : 1.0f;

        currentScale += (targetScale - currentScale) * scaleSpeed;

        int newWidth = static_cast<int>(buttonWidth * currentScale);
        int newHeight = static_cast<int>(buttonHeight * currentScale);
        int newX = (SCREEN_WIDTH - newWidth) / 2;
        int newY = (SCREEN_HEIGHT - newHeight) / 2;

        isHovering = (mouseX >= newX && mouseX <= newX + newWidth &&
                           mouseY >= newY && mouseY <= newY + newHeight);

        if (isHovering && !wasPlayButtonHovered) {
            if (hoverSound && !isMuted) {
                Mix_PlayChannel(-1, hoverSound, 0);
            }
            wasPlayButtonHovered = true;
        }
        else if (!isHovering && wasPlayButtonHovered) {
            wasPlayButtonHovered = false;
        }

        SDL_Rect buttonRect = {newX, newY, newWidth, newHeight};
        SDL_Texture* currentTexture = isHovering ? playButtonHoverTexture : playButtonTexture;
        if (currentTexture) {
            SDL_RenderCopy(graphics.getRenderer(), currentTexture, NULL, &buttonRect);
        }
    }

    else if (trangthai == PAUSED)
    {
        SDL_Surface* surface = TTF_RenderText_Solid(graphics.getFont(), "Paused", black);
        if (!surface) {
            cerr << "Render text error: " << TTF_GetError() << endl;
            graphics.presentScene();
            return;
        }
        int textWidth = surface->w;
        int textHeight = surface->h;
        SDL_FreeSurface(surface);
        int textX = (SCREEN_WIDTH - textWidth) / 2;
        int textY = (SCREEN_HEIGHT - textHeight) / 2 - 100;
        graphics.renderText("Paused", textX, textY, black);

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        int homeButtonWidth, homeButtonHeight;
        SDL_QueryTexture(homeButtonTexture, NULL, NULL, &homeButtonWidth, &homeButtonHeight);
        int homeButtonCenterX = SCREEN_WIDTH / 2 - 80;
        int homeButtonCenterY = SCREEN_HEIGHT / 2 + 50;

        int homeButtonNewWidth = static_cast<int>(homeButtonWidth * homeButtonCurrentScale);
        int homeButtonNewHeight = static_cast<int>(homeButtonHeight * homeButtonCurrentScale);
        int homeButtonX = homeButtonCenterX - homeButtonNewWidth / 2;
        int homeButtonY = homeButtonCenterY - homeButtonNewHeight / 2;

        bool isHomeButtonHovering = (mouseX >= homeButtonX && mouseX <= homeButtonX + homeButtonNewWidth &&
                                     mouseY >= homeButtonY && mouseY <= homeButtonY + homeButtonNewHeight);

        homeButtonTargetScale = isHomeButtonHovering ? 1.2f : 1.0f;
        homeButtonCurrentScale += (homeButtonTargetScale - homeButtonCurrentScale) * homeButtonScaleSpeed;

        homeButtonNewWidth = static_cast<int>(homeButtonWidth * homeButtonCurrentScale);
        homeButtonNewHeight = static_cast<int>(homeButtonHeight * homeButtonCurrentScale);
        homeButtonX = homeButtonCenterX - homeButtonNewWidth / 2;
        homeButtonY = homeButtonCenterY - homeButtonNewHeight / 2;

        isHomeButtonHovering = (mouseX >= homeButtonX && mouseX <= homeButtonX + homeButtonNewWidth &&
                                mouseY >= homeButtonY && mouseY <= homeButtonY + homeButtonNewHeight);

        if (isHomeButtonHovering && !wasHomeButtonHovered) {
            if (hoverSound && !isMuted) {
                Mix_PlayChannel(-1, hoverSound, 0);
            }
            wasHomeButtonHovered = true;
        }
        else if (!isHomeButtonHovering && wasHomeButtonHovered) {
            wasHomeButtonHovered = false;
        }

        SDL_Rect homeButtonRect = {homeButtonX, homeButtonY, homeButtonNewWidth, homeButtonNewHeight};
        SDL_Texture* homeButtonCurrentTexture = isHomeButtonHovering ? homeButtonHoverTexture : homeButtonTexture;
        SDL_RenderCopy(graphics.getRenderer(), homeButtonCurrentTexture, NULL, &homeButtonRect);

        int resumeButtonWidth, resumeButtonHeight;
        SDL_QueryTexture(resumeButtonTexture, NULL, NULL, &resumeButtonWidth, &resumeButtonHeight);
        int resumeButtonCenterX = SCREEN_WIDTH / 2;
        int resumeButtonCenterY = SCREEN_HEIGHT / 2 + 50;

        int resumeButtonNewWidth = static_cast<int>(resumeButtonWidth * resumeButtonCurrentScale);
        int resumeButtonNewHeight = static_cast<int>(resumeButtonHeight * resumeButtonCurrentScale);
        int resumeButtonX = resumeButtonCenterX - resumeButtonNewWidth / 2;
        int resumeButtonY = resumeButtonCenterY - resumeButtonNewHeight / 2;

        bool isResumeButtonHovering = (mouseX >= resumeButtonX && mouseX <= resumeButtonX + resumeButtonNewWidth &&
                                       mouseY >= resumeButtonY && mouseY <= resumeButtonY + resumeButtonNewHeight);

        resumeButtonTargetScale = isResumeButtonHovering ? 1.2f : 1.0f;
        resumeButtonCurrentScale += (resumeButtonTargetScale - resumeButtonCurrentScale) * resumeButtonScaleSpeed;

        resumeButtonNewWidth = static_cast<int>(resumeButtonWidth * resumeButtonCurrentScale);
        resumeButtonNewHeight = static_cast<int>(resumeButtonHeight * resumeButtonCurrentScale);
        resumeButtonX = resumeButtonCenterX - resumeButtonNewWidth / 2;
        resumeButtonY = resumeButtonCenterY - resumeButtonNewHeight / 2;

        isResumeButtonHovering = (mouseX >= resumeButtonX && mouseX <= resumeButtonX + resumeButtonNewWidth &&
                                  mouseY >= resumeButtonY && mouseY <= resumeButtonY + resumeButtonNewHeight);

        if (isResumeButtonHovering && !wasResumeButtonHovered) {
            if (hoverSound && !isMuted) {
                Mix_PlayChannel(-1, hoverSound, 0);
            }
            wasResumeButtonHovered = true;
        }
        else if (!isResumeButtonHovering && wasResumeButtonHovered) {
            wasResumeButtonHovered = false;
        }
        SDL_Rect resumeButtonRect = {resumeButtonX, resumeButtonY, resumeButtonNewWidth, resumeButtonNewHeight};
        SDL_Texture* resumeButtonCurrentTexture = isResumeButtonHovering ? resumeButtonHoverTexture : resumeButtonTexture;
        SDL_RenderCopy(graphics.getRenderer(), resumeButtonCurrentTexture, NULL, &resumeButtonRect);

        int replayButtonWidth, replayButtonHeight;
        SDL_QueryTexture(replayButtonTexture, NULL, NULL, &replayButtonWidth, &replayButtonHeight);
        int replayButtonCenterX = SCREEN_WIDTH / 2 + 80;
        int replayButtonCenterY = SCREEN_HEIGHT / 2 + 50;

        int replayButtonNewWidth = static_cast<int>(replayButtonWidth * replayButtonCurrentScale);
        int replayButtonNewHeight = static_cast<int>(replayButtonHeight * replayButtonCurrentScale);
        int replayButtonX = replayButtonCenterX - replayButtonNewWidth / 2;
        int replayButtonY = replayButtonCenterY - replayButtonNewHeight / 2;

        bool isReplayButtonHovering = (mouseX >= replayButtonX && mouseX <= replayButtonX + replayButtonNewWidth &&
                                       mouseY >= replayButtonY && mouseY <= replayButtonY + replayButtonNewHeight);

        replayButtonTargetScale = isReplayButtonHovering ? 1.2f : 1.0f;
        replayButtonCurrentScale += (replayButtonTargetScale - replayButtonCurrentScale) * replayButtonScaleSpeed;

        replayButtonNewWidth = static_cast<int>(replayButtonWidth * replayButtonCurrentScale);
        replayButtonNewHeight = static_cast<int>(replayButtonHeight * replayButtonCurrentScale);
        replayButtonX = replayButtonCenterX - replayButtonNewWidth / 2;
        replayButtonY = replayButtonCenterY - replayButtonNewHeight / 2;

        isReplayButtonHovering = (mouseX >= replayButtonX && mouseX <= replayButtonX + replayButtonNewWidth &&
                                  mouseY >= replayButtonY && mouseY <= replayButtonY + replayButtonNewHeight);

        if (isReplayButtonHovering && !wasReplayButtonHovered) {
            if (hoverSound && !isMuted) {
                Mix_PlayChannel(-1, hoverSound, 0);
            }
            wasReplayButtonHovered = true;
        }
        else if (!isReplayButtonHovering && wasReplayButtonHovered) {
            wasReplayButtonHovered = false;
        }

        SDL_Rect replayButtonRect = {replayButtonX, replayButtonY, replayButtonNewWidth, replayButtonNewHeight};
        SDL_Texture* replayButtonCurrentTexture = isReplayButtonHovering ? replayButtonHoverTexture : replayButtonTexture;
        SDL_RenderCopy(graphics.getRenderer(), replayButtonCurrentTexture, NULL, &replayButtonRect);
    }

    else {
        if (count >= 0 && count < 8 && hangmanTextures[count]) {
            int texWidth, texHeight;
            SDL_QueryTexture(hangmanTextures[count], NULL, NULL, &texWidth, &texHeight);
            int x = (SCREEN_WIDTH - texWidth);
            int y = (SCREEN_HEIGHT - texHeight) / 2;
            SDL_Rect destRect = {x, y, texWidth, texHeight};
            SDL_RenderCopy(graphics.getRenderer(), hangmanTextures[count], NULL, &destRect);
        }

        if (won()) {
            SDL_Surface* surface = TTF_RenderText_Solid(graphics.getFont(), "YOU WIN", black);
            if (!surface) {
                cerr << "Render text error: " << TTF_GetError() << endl;
                graphics.presentScene();
                return;
            }
            int textWidth = surface->w;
            int textHeight = surface->h;
            SDL_FreeSurface(surface);
            int x = (SCREEN_WIDTH - textWidth) / 2;
            int y = (SCREEN_HEIGHT - textHeight) / 2;
            graphics.renderText("YOU WIN!!!", x, y, black);
        }
        else if (lost()) {
            graphics.renderText(("YOU LOSE!!!  SecretWord is: " + secretWord).c_str(), 200, 450, black);
        }
        else {
            graphics.renderText(guessed_word.c_str(), 50, SCREEN_HEIGHT / 2, black);
        }
        if (pauseButtonTexture && pauseButtonHoverTexture) {
            int pauseButtonWidth, pauseButtonHeight;
            SDL_QueryTexture(pauseButtonTexture, NULL, NULL, &pauseButtonWidth, &pauseButtonHeight);

            int pauseButtonCenterX = SCREEN_WIDTH - 10 - pauseButtonWidth / 2;
            int pauseButtonCenterY = 10 + pauseButtonHeight / 2;

            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            int pauseButtonNewWidth = static_cast<int>(pauseButtonWidth * pauseButtonCurrentScale);
            int pauseButtonNewHeight = static_cast<int>(pauseButtonHeight * pauseButtonCurrentScale);
            int pauseButtonX = pauseButtonCenterX - pauseButtonNewWidth / 2;
            int pauseButtonY = pauseButtonCenterY - pauseButtonNewHeight / 2;

            bool isHovering = (mouseX >= pauseButtonX && mouseX <= pauseButtonX + pauseButtonNewWidth &&
                               mouseY >= pauseButtonY && mouseY <= pauseButtonY + pauseButtonNewHeight);

            pauseButtonTargetScale = isHovering ? 1.2f : 1.0f;
            pauseButtonCurrentScale += (pauseButtonTargetScale - pauseButtonCurrentScale) * pauseButtonScaleSpeed;

            if (isHovering && !wasPauseButtonHovered) {
                if (hoverSound && !isMuted) {
                    Mix_PlayChannel(-1, hoverSound, 0);
                }
                wasPauseButtonHovered = true;
            }
            else if (!isHovering && wasPauseButtonHovered) {
                wasPauseButtonHovered = false;
            }

            SDL_Rect pauseButtonRect = {pauseButtonX, pauseButtonY, pauseButtonNewWidth, pauseButtonNewHeight};
            SDL_Texture* pauseButtonCurrentTexture = isHovering ? pauseButtonHoverTexture : pauseButtonTexture;
            SDL_RenderCopy(graphics.getRenderer(), pauseButtonCurrentTexture, NULL, &pauseButtonRect);
        }
    }

    SDL_Texture* soundButtonTexture = isMuted ? unmuteButtonTexture : muteButtonTexture;
    SDL_Texture* soundButtonHoverTexture = isMuted ? unmuteButtonHoverTexture : muteButtonHoverTexture;

    if (soundButtonTexture && soundButtonHoverTexture) {

        int buttonWidth, buttonHeight;
        SDL_QueryTexture(soundButtonTexture, NULL, NULL, &buttonWidth, &buttonHeight);

        int centerX = SCREEN_WIDTH - 10 - buttonWidth / 2;
        int centerY = SCREEN_HEIGHT - 10 - buttonHeight / 2;

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        int newWidth = static_cast<int>(buttonWidth * soundButtonCurrentScale);
        int newHeight = static_cast<int>(buttonHeight * soundButtonCurrentScale);
        int buttonX = centerX - newWidth / 2;
        int buttonY = centerY - newHeight / 2;

        bool isHovering = (mouseX >= buttonX && mouseX <= buttonX + newWidth &&
                           mouseY >= buttonY && mouseY <= buttonY + newHeight);

        if (isHovering && !wasSoundButtonHovered) {
            if (hoverSound && !isMuted) {
                Mix_PlayChannel(-1, hoverSound, 0);
            }
            wasSoundButtonHovered = true;
        }
        else if (!isHovering && wasSoundButtonHovered) {
            wasSoundButtonHovered = false;
        }

        soundButtonTargetScale = isHovering ? 1.2f : 1.0f;
        soundButtonCurrentScale += (soundButtonTargetScale - soundButtonCurrentScale) * soundButtonScaleSpeed;

        newWidth = static_cast<int>(buttonWidth * soundButtonCurrentScale);
        newHeight = static_cast<int>(buttonHeight * soundButtonCurrentScale);
        buttonX = centerX - newWidth / 2;
        buttonY = centerY - newHeight / 2;

        SDL_Rect buttonRect = {buttonX, buttonY, newWidth, newHeight};
        SDL_Texture* currentTexture = isHovering ? soundButtonHoverTexture : soundButtonTexture;
        SDL_RenderCopy(graphics.getRenderer(), currentTexture, NULL, &buttonRect);
    }

    graphics.presentScene();
}

void HangMan::cleanup()
{
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
    if (startSound) {
        Mix_FreeChunk(startSound);
        startSound = nullptr;
    }
    if (correctSound) {
        Mix_FreeChunk(correctSound);
        correctSound = nullptr;
    }
    if (incorrectSound) {
        Mix_FreeChunk(incorrectSound);
        incorrectSound = nullptr;
    }
    if (winSound) {
        Mix_FreeChunk(winSound);
        winSound = nullptr;
    }
    if (loseSound) {
        Mix_FreeChunk(loseSound);
        loseSound = nullptr;
    }
    if (hoverSound) {
        Mix_FreeChunk(hoverSound);
        hoverSound = nullptr;
    }
    for (int i = 0; i < 8; i++) {
        if (hangmanTextures[i]) {
            SDL_DestroyTexture(hangmanTextures[i]);
            hangmanTextures[i] = nullptr;
        }
    }
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }
    if (playButtonTexture) {
        SDL_DestroyTexture(playButtonTexture);
        playButtonTexture = nullptr;
    }
    if (playButtonHoverTexture) {
        SDL_DestroyTexture(playButtonHoverTexture);
        playButtonHoverTexture = nullptr;
    }
    if (titleTexture) {
        SDL_DestroyTexture(titleTexture);
        titleTexture = nullptr;
    }
    if (muteButtonTexture) {
        SDL_DestroyTexture(muteButtonTexture);
        muteButtonTexture = nullptr;
    }
    if (unmuteButtonTexture) {
        SDL_DestroyTexture(unmuteButtonTexture);
        unmuteButtonTexture = nullptr;
    }
    if (muteButtonHoverTexture) {
        SDL_DestroyTexture(muteButtonHoverTexture);
        muteButtonHoverTexture = nullptr;
    }
    if (unmuteButtonHoverTexture) {
        SDL_DestroyTexture(unmuteButtonHoverTexture);
        unmuteButtonHoverTexture = nullptr;
    }
    if (pauseButtonTexture) {
        SDL_DestroyTexture(pauseButtonTexture);
        pauseButtonTexture = nullptr;
    }
    if (pauseButtonHoverTexture) {
        SDL_DestroyTexture(pauseButtonHoverTexture);
        pauseButtonHoverTexture = nullptr;
    }
    if (homeButtonTexture) {
        SDL_DestroyTexture(homeButtonTexture);
        homeButtonTexture = nullptr;
    }
    if (homeButtonHoverTexture) {
        SDL_DestroyTexture(homeButtonHoverTexture);
        homeButtonHoverTexture = nullptr;
    }
    if (resumeButtonTexture) {
        SDL_DestroyTexture(resumeButtonTexture);
        resumeButtonTexture = nullptr;
    }
    if (resumeButtonHoverTexture) {
        SDL_DestroyTexture(resumeButtonHoverTexture);
        resumeButtonHoverTexture = nullptr;
    }
    if (replayButtonTexture) {
        SDL_DestroyTexture(replayButtonTexture);
        replayButtonTexture = nullptr;
    }
    if (replayButtonHoverTexture) {
        SDL_DestroyTexture(replayButtonHoverTexture);
        replayButtonHoverTexture = nullptr;
    }

    Mix_CloseAudio();
    graphics.quit();
}

void HangMan::upload(const char& input)
{
    if(trangthai == MENU) return;
    trangthai = BAD_GUESS;
    for (int i = 0; i < secretWord.size(); i++) {
        if (secretWord[i] == input && guessed_word[i] == '_') {
            guessed_word[i] = input;
            trangthai = GOOD_GUESS;
            hidden--;
            if (correctSound) Mix_PlayChannel(-1, correctSound, 0);
        }
    }
    if (trangthai == BAD_GUESS) {
            count++;
            if (incorrectSound) Mix_PlayChannel(-1, incorrectSound, 0);
    }
    if (won() && !winSoundPlayed) {
        if (winSound) Mix_PlayChannel(-1, winSound, 0);
        winSoundPlayed = true;
    }
    else if (lost() && !loseSoundPlayed) {
        if (loseSound) Mix_PlayChannel(-1, loseSound, 0);
        loseSoundPlayed = true;
    }
}

void HangMan::goiy()
{
    if(trangthai == MENU) return;

    int sz = secretWord.size();
    int num = rand() % sz;
    int cnt = 0;
    for (char c : secretWord) {
        if (c == secretWord[num]) {
            cnt++;
        }
    }
    cout << "Goi y: Tu khoa co chua " + to_string(cnt) + " chu " + secretWord[num] << endl;
}

bool HangMan::won()
{
    return hidden <= 0;
}

bool HangMan::lost()
{
    return count >= 7;
}

bool HangMan::end()
{
    return won() || lost();
}
