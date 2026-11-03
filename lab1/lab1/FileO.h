#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"

void Save(const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, CS>& stations, int nextPipeId, int nextCSId);
void Load(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CS>& stations, int& nextPipeId, int& nextCSId);
void fileMenu(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CS>& stations, int& nextPipeId, int& nextCSId);