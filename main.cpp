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
            if(game.trangthai == MENU)
            {
                if(event.type == SDL_MOUSEBUTTONDOWN || input!=0){
                    game.startGame();
                    game.goiy();
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
