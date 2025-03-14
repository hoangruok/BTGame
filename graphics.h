#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "defs.h"

class Graphics {
public:

    Graphics();
    ~Graphics();
    void init();
    void prepareScene(void);
    void presentScene(void);
    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void renderText(const char* text, int x, int y, SDL_Color color);
    void quit();

private:
    SDL_Renderer *renderer;
	SDL_Window *window;
	TTF_Font *font;
    void logErrorAndExit(const char* msg, const char* error);
};
#endif // _GRAPHICS__H
