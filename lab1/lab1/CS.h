#pragma once
#include <string>
#include <vector>

class CS {
public:
    int id = 0;
    std::string name;
    int squant = 0;
    int wsquant = 0;
    char type = '\0';
    void view() const;
};

void addNewCS(std::vector<CS>& stations, int& nextId);
void viewStations(const std::vector<CS>& stations);
void stationMenu(std::vector<CS>& stations);
