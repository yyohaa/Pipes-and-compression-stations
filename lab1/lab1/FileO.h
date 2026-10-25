#pragma once
#include "Pipe.h"
#include "CS.h"
#include <vector>

void Save(const std::vector<Pipe>& pipes, const std::vector<CS>& stations, int nextId);
void Load(const std::vector<Pipe>& pipes, const std::vector<CS>& stations, int & nextId);
void fileMenu(std::vector<Pipe>&, std::vector<CS>&, int&nextId);
