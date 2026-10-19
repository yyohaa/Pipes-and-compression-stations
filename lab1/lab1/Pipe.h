#pragma once
#include <string>

class Pipe {
public:
    std::string name;
    double len = 0;
    int d = 0;
    bool statePipe = false;
    void view() const;
};

