#include "rand_word.h"
#include "defs.h"

string getword(const string& filename) {
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
    if (words.empty()) {
        cout << "File is empty!" << endl;
        exit(0);
    }
    int k = rand() % words.size();
    return words[k];
}
