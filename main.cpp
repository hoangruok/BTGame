#include "Logic.h"

char getinput()
{
	string str;
	cout << "Nhap tu doan: " << endl;
	cin >> str;
	return str[0];
}

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
}
