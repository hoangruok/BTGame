#include "rand_word.h"
#include "defs.h"
#include "graphics.h"
#include "logic.h"

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
    Mix_AllocateChannels(16);

    graphics.init();
    backgroundTexture = graphics.loadTexture("background.png");
    if (!backgroundTexture) {
        cerr << "Failed to load background.png" << endl;
    }

    playButtonTexture = graphics.loadTexture("playButton.png");
    if (!playButtonTexture) {
        cerr << "Failed to load playButton.png" << endl;
    }

    playButtonHoverTexture = graphics.loadTexture("playButtonHover.png");
    if (!playButtonHoverTexture) {
        cerr << "Failed to load playButtonHover.png" << endl;
    }

    titleTexture = graphics.loadTexture("gameTitle.png");
    if (!titleTexture) {
        cerr << "Failed to load gameTitle.png" << endl;
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
    else Mix_VolumeChunk(startSound, 32);

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

    trangthai = MENU;
    winSoundPlayed = false;
    loseSoundPlayed = false;
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
    if (startSound) Mix_PlayChannel(-1, startSound, 0);
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
        SDL_Rect buttonRect = {buttonX, buttonY, buttonWidth, buttonHeight};
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        bool isHovering = (mouseX >= buttonX && mouseX <= buttonX + buttonWidth &&
                           mouseY >= buttonY && mouseY <= buttonY + buttonHeight);
        SDL_Texture* currentTexture = isHovering ? playButtonHoverTexture : playButtonTexture;
        if (currentTexture) {
            SDL_RenderCopy(graphics.getRenderer(), currentTexture, NULL, &buttonRect);
        }
    }
    else{

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
    }
    graphics.presentScene();
}

void HangMan::cleanup()
{
    if  (music) {
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
