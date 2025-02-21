#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;

int main(int argc, char* argv[]) {
            SDL_Window* window = SDL_CreateWindow("First program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 453, SDL_WINDOW_OPENGL);
            SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            SDL_Surface* lettuce_sur = IMG_Load("test.png");
            SDL_Texture* lettuce_tex = SDL_CreateTextureFromSurface(renderer, lettuce_sur);
            SDL_FreeSurface(lettuce_sur);
            while (true) {
                SDL_Event e;
                if (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        break;
                    }
                }
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, lettuce_tex, NULL, NULL);
                SDL_RenderPresent(renderer);
            }
            SDL_DestroyTexture(lettuce_tex);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();
            return 0;
}
