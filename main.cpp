#include "Logic.h"
#include "input.h"
#include "graphics.h"

int main(int argc, char* argv[])
{
    srand(time(0));
    HangMan game;
    game.init();

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            char input = getInput(event, running);
            if (game.trangthai == MENU) {
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    int buttonWidth, buttonHeight;
                    SDL_QueryTexture(game.playButtonTexture, NULL, NULL, &buttonWidth, &buttonHeight);
                    int buttonX = (SCREEN_WIDTH - buttonWidth) / 2;
                    int buttonY = (SCREEN_HEIGHT - buttonHeight) / 2;
                    if (x >= buttonX && x <= buttonX + buttonWidth && y >= buttonY && y <= buttonY + buttonHeight) {
                        game.startGame();
                        game.goiy();
                    }
                }
            }
            else if (input != 0) {
                game.upload(input);
            }
        }
        game.render();
        if (game.end() && game.trangthai != MENU) {
            SDL_Delay(2000);
            running = false;
        }
    }
    return 0;
}
