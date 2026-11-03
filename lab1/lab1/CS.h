#pragma once
#include <string>
#include <unordered_map>

class CS {
public:
    int id = 0;
    std::string name;
    int squant = 0;
    int wsquant = 0;
    char type = '\0';
    void view() const;
};

void addNewCS(std::unordered_map<int, CS>& stations, int& nextId);
void viewStations(const std::unordered_map<int, CS>& stations);
void stationMenu(std::unordered_map<int, CS>& stations);
