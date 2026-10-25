#pragma once
#include <string>
#include <vector>

class Pipe {
public:
    int id = 0;
    std::string name;
    double len = 0;
    int d = 0;
    bool statePipe = false;
    void view() const;
};

void addPipe(Pipe& pipe);
void addNewPipe(std::vector<Pipe>& pipes, int& nextId);
void viewPipes(const std::vector<Pipe>& pipes);
void editPipe(Pipe& pipe);
void editSelectedPipe(std::vector<Pipe>& pipes);
void deleteSelectedPipe(std::vector<Pipe>& pipes);
void pipeMenu(std::vector<Pipe>& pipes);
