#include "rand_word.h"
#include  "defs.h"
#include "graphics.h"
#include "logic.h"
#include <iostream>

using namespace std;

void HangMan::init()
{
    graphics.init();
    hangmanTexture = graphics.loadTexture("tes.png");

    secretWord = getword("words.txt");
	guessed_word = string(secretWord.size(), '_');
	hidden = (int)secretWord.size();
	trangthai = START;
	count = 0;
}
void HangMan::render()
{
    cout << "Tu da doan hien tai: " << guessed_word << endl;
    cout << "So lan doan sai: " << count << endl;
	if (won())	cout << "YOU WON!!!";
	else if (lost()) cout << "YOU LOSE!!!. Tu khoa can tim la: " << secretWord;

    graphics.prepareScene();
    graphics.renderTexture(hangmanTexture, 100, 100);
    graphics.presentScene();
}
void HangMan::upload(const char& input)
{
    trangthai = BAD_GUESS;
    for (int i = 0; i < secretWord.size(); i++) {
		if (secretWord[i] == input && guessed_word[i] == '_') {
			guessed_word[i] = input;
			trangthai = GOOD_GUESS;
			hidden--;
		}
	}
	if (trangthai == BAD_GUESS) count++;
}
void HangMan::goiy()
{
    int sz = secretWord.size();
	int num = rand() % sz;
	int cnt = 0;
	for (char c : secretWord) {
		if (c == secretWord[num]) cnt++;
	}
	cout << "Goi y: Tu khoa co chua " << cnt << " chu " << secretWord[num] << endl;
}
bool HangMan::won()
{
	return hidden <= 0;
}
bool HangMan::lost()
{
    return count >= 8;

}
bool HangMan::end()
{
    return won() || lost();

}
