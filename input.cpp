#include "input.h"

char getInput(SDL_Event& event, bool& running) {
    char input = 0;

    if (event.type == SDL_QUIT) {
        running = false;
    }
    else if (event.type == SDL_KEYDOWN) {
        SDL_Keycode key = event.key.keysym.sym;
        if (key >= SDLK_a && key <= SDLK_z) {
            input = static_cast<char>(key);
        }
    }

    return input;
}
