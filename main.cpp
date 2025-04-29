#include "logic.h"
#include "input.h"
#include "graphics.h"

int main(int argc, char* argv[])
{
    srand(time(0));
    HangMan game;
    game.init();
    game.run();
    game.cleanup();
    return 0;
}
