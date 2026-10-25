
#include "Input.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

string readLine(string text) {
    cout << text;
    string line;
    getline(cin, line);
    return line;
}

template <typename T>
bool correctNumber(string line, T& val) {
    stringstream ss(line);
    if (!(ss >> val)) return false;
    ss >> ws;
    return ss.eof();
}

template <typename T>
T positiveNumber(string text) {
    while (true) {
        T val;
        if (correctNumber(readLine(text), val) && val > 0) return val;
        cout << "wrong input, try again with a positive number :)\n";
    }
}

int inputInt(string text, int min, int max) {
    while (true) {
        int val;
        if (correctNumber(readLine(text), val) && val >= min && val <= max) return val;
        cout << "wrong input, try again :)\n";
    }
}

int plusInt(string text) {
    return positiveNumber<int>(text);
}

double plusDouble(string text) {
    return positiveNumber<double>(text);
}

string inputString(string text) {
    while (true) {
        string val = readLine(text);
        if (!val.empty() && val.find_first_not_of(" \t") != string::npos) return val;
        cout << "wrong input, try again, name cannot be empty :)\n";
    }
}
