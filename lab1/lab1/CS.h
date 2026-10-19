#pragma once
#include <string>

class CS {
public:
    std::string name;
    int squant = 0;
    int wsquant = 0;
    char type = '\0';
    void view() const;
};

