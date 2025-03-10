#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

struct Graphics {
public:

    Graphics();
    ~Graphics();
    void init();
    void prepareScene(void);
    void presentScene(void);
    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
    void quit();

private:
    SDL_Renderer *renderer;
	SDL_Window *window;
    void logErrorAndExit(const char* msg, const char* error);
};
#endif // _GRAPHICS__H
