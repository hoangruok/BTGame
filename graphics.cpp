#include "graphics.h"
#include "defs.h"
#include <iostream>

using namespace std;

Graphics::Graphics() : renderer(nullptr), window(nullptr){}
Graphics::~Graphics()
{
    quit();
}

void Graphics::logErrorAndExit(const char* msg, const char* error)
{
    cerr<<msg<<"; "<<error<<endl;
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void Graphics::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_INIT", SDL_GetError());

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
        logErrorAndExit("CreateWindow", SDL_GetError());
    if ((IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)) == 0)
        logErrorAndExit("SDL_image error:", IMG_GetError());
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer)
        logErrorAndExit("CreateRenderer", SDL_GetError());
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Graphics::prepareScene() {
    SDL_SetRenderDrawColor(renderer, BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, BG_COLOR_A);
    SDL_RenderClear(renderer);
}

void Graphics::presentScene() {
    SDL_RenderPresent(renderer);
}

SDL_Texture* Graphics::loadTexture(const char *filename) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (!texture) std::cerr << "Load texture error: " << IMG_GetError() << std::endl;
    return texture;
}

void Graphics::renderTexture(SDL_Texture *texture, int x, int y) {
    SDL_Rect dest = { x, y, 0, 0 };
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Graphics::quit() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
