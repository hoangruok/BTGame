#ifndef RANDWORD_H
#define RANDWORD_H

#include "defs.h"
string getword (const string& filename)
{
	ifstream file(filename);
	vector<string> words;
	if (!file.is_open()) {
		cout << "Can't open this file!" << endl;
		exit(0);
	}
	string tmp;
	while (file >> tmp) {
		words.push_back(tmp);
	}
	int k = rand() % 201;
	return words[k];
}

#endif

