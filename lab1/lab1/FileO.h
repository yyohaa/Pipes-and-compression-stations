#pragma once
#include <vector>
#include "Pipe.h"
#include "CS.h"

void Save(const std::vector<Pipe>& pipes, const std::vector<CS>& stations, int nextPipeId, int nextCSId);

void Load(std::vector<Pipe>& pipes, std::vector<CS>& stations, int& nextPipeId, int& nextCSId);

void fileMenu(std::vector<Pipe>& pipes, std::vector<CS>& stations, int& nextPipeId, int& nextCSId);