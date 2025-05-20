#include "rand_word.h"
#include "defs.h"

void getword(const string& filename, string &x, string &y) {
    ifstream file(filename);
    vector<string> words;
    if (!file.is_open()) {
        cout << "Can't open " << filename << endl;
        exit(0);
    }
    string tmp;
    while (file >> tmp) {
        words.push_back(tmp);
    }
    if (words.empty() || words.size() % 2 != 0) {
        cout << "File format error or empty!" << endl;
        exit(0);
    }
    int k = (rand() % (words.size() / 2)) * 2;
    x = words[k];
    y = words[k+1];
}

