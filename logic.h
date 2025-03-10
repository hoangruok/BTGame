#ifndef HANGMAN_H
#define HANGMAN_H

#include "rand_word.h"
#include  "defs.h"

struct HangMan
{
	string secretWord;
	string guessed_word;
	int count;
	int hidden;
	int trangthai;

	void init() {
		secretWord = getword("words.txt");
		guessed_word = string(secretWord.size(), '_');
		hidden = (int)secretWord.size();
		trangthai = START;
		count = 0;
	}
	void render() {
		cout << "Tu da doan hien tai: " << guessed_word << endl;
		cout << "So lan doan sai: " << count << endl;
		if (won())	cout << "YOU WON!!!";
		else if (lost()) cout << "YOU LOSE!!!. Tu khoa can tim la: " << secretWord;
	}
	void upload(const char& input) {
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
	void goiy()
	{
		int sz = secretWord.size();
		int num = rand() % sz;
		int cnt = 0;
		for (char c : secretWord) {
			if (c == secretWord[num]) cnt++;
		}
		cout << "Goi y: Tu khoa co chua " << cnt << " chu " << secretWord[num] << endl;
	}
	bool won()
	{
		return hidden <= 0;
	}
	bool lost()
	{
		return count >= 8;
	}
	bool end() {
		return won() || lost();
	}
};
#endif

