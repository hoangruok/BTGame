#include <iostream>
#include <string>
#include "input.h"

using namespace std;

char getinput() {
    string str;
    cout << "Nhap tu doan: " << endl;
    cin >> str;
    return str[0];
}
