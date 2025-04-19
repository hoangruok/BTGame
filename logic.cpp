#include "rand_word.h"
#include "defs.h"
#include "graphics.h"
#include "logic.h"

using namespace std;

void HangMan::init()
{
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
        cerr << "Failed to load title.png" << endl;
    }

    trangthai = MENU;
}

void HangMan::startGame()
{
    secretWord = getword("words.txt");
    guessed_word = string(secretWord.size(), '_');
    hidden = (int)secretWord.size();
    trangthai = START;
    count = 0;
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
            graphics.renderText(guessed_word.c_str(), 50, 300, black);
            string countStr = "So lan doan sai: " + to_string(count);
            graphics.renderText(countStr.c_str(), 600, 350, black);
        }
    }
    graphics.presentScene();
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
        }
    }
    if (trangthai == BAD_GUESS) count++;
}

void HangMan::goiy()
{
    if(trangthai == MENU) return;

    int sz = secretWord.size();
    int num = rand() % sz;
    int cnt = 0;
    for (char c : secretWord) {
        if (c == secretWord[num]) cnt++;
    }
    cout << "Goi y: Tu khoa co chua " + to_string(cnt) + " chu " + secretWord[num] << endl;
}

bool HangMan::won()
{
    return hidden <= 0;
}

bool HangMan::lost()
{
    return count >= 8;
}

bool HangMan::end()
{
    return won() || lost();
}
