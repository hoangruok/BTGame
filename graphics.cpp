#include "graphics.h"

Graphics::Graphics() : renderer(nullptr), window(nullptr), font(nullptr){}
Graphics::~Graphics() { quit(); }

void Graphics::logErrorAndExit(const char* msg, const char* error)
{
    cerr<<msg<<"; "<<error<<endl;
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void Graphics::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logErrorAndExit("SDL init error:", SDL_GetError());
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
        logErrorAndExit("CreateWindow", SDL_GetError());

    if ((IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)) == 0)
        logErrorAndExit("SDL_image error:", IMG_GetError());

    if (TTF_Init() == -1)
        logErrorAndExit("SDL_ttf init error:", TTF_GetError());

    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer)
        logErrorAndExit("CreateRenderer", SDL_GetError());

    font = TTF_OpenFont("Lucida Sans Unicode.ttf", 32);
    if (!font)
        logErrorAndExit("Load font error:", TTF_GetError());

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

void Graphics::renderText(const char* text, int x, int y, SDL_Color color) {
    if (!font) {
        cerr << "Font not loaded!" << endl;
        return;
    }
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        cerr << "Render text error: " << TTF_GetError() << endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        cerr << "Create texture from surface error: " << SDL_GetError() << endl;
        SDL_FreeSurface(surface);
        return;
    }
    SDL_Rect dest = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Graphics::quit() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    if (TTF_WasInit()) {
        TTF_Quit();
    }
    IMG_Quit();
    SDL_Quit();
}
