#pragma once
#include "Pipe.h"
#include "CS.h"
#include <vector>

void Save(const std::vector<Pipe>& pipes, const std::vector<CS>& stations, int& nextPipeId, int& nextCSId);
void Load(const std::vector<Pipe>& pipes, const std::vector<CS>& stations, int& nextPipeId, int& nextCSId);
void fileMenu(std::vector<Pipe>&pipes, std::vector<CS>&stations, int&nextPipeId, int&nextCSId);
