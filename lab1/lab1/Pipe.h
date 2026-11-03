#pragma once
#include <string>
#include <unordered_map>

class Pipe {
public:
    int id = 0;
    std::string name;
    double len = 0;
    int d = 0;
    bool statePipe = false;
    void view() const;
};

void addNewPipe(std::unordered_map <int, Pipe>& pipes, int& nextId);
void viewPipes(const std::unordered_map <int, Pipe>& pipes);
void pipeMenu(std::unordered_map <int, Pipe>& pipes);
