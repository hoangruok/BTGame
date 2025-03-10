#include "Logic.h"
#include "input.h"
#include "graphics.h"

int main(int argc, char* argv[])
{
	srand(time(0));
	HangMan game;
	game.init();
	game.render();
	game.goiy();
	do {
		char input = getinput();
		game.upload(input);
		game.render();
	} while (!game.end());
	return 0;
}
