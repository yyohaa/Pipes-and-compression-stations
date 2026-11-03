
#include "FileO.h"
#include "Input.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;


void savePipe(const Pipe& pipe, ofstream& file) {
    file << pipe.id << '\n' << pipe.name << '\n';
    file << pipe.len << '\n' << pipe.d << '\n';
    file << pipe.statePipe << '\n';
}

void saveCS(const CS& cs, ofstream& file) {
    file << cs.id << '\n' << cs.name << '\n';
    file << cs.squant << '\n' << cs.wsquant << '\n';
    file << cs.type << '\n';
}

void Save(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CS>& stations, int nextPipeId, int nextCSId) {
    ofstream file(inputString("enter file name to save: "));
    if (!file) { 
        cout << "\nfile error\n"; return; }

    file << "PIPES\n" << pipes.size() << '\n';
    for (const auto& item : pipes) savePipe(item.second, file);
    file << "CS\n" << stations.size() << '\n';
    for (const auto& item : stations) saveCS(item.second, file);
    file << "NEXT_PIPE_ID\n" << nextPipeId << '\n';
    file << "NEXT_CS_ID\n" << nextCSId << '\n';
    file.close();
    cout << (file ? "\ndata was saved\n" : "\nfile write error\n");
}

bool loadPipe(ifstream& file, Pipe& pipe) {
    if (!(file >> pipe.id)) return false;
    file.ignore(10000, '\n');
    if (!getline(file, pipe.name) || pipe.name.empty()) return false;
    if (!(file >> pipe.len >> pipe.d >> pipe.statePipe)) return false;
    file.ignore(10000, '\n');
    return pipe.id > 0 && pipe.len > 0 && pipe.d > 0;
}

bool loadCS(ifstream& file, CS& cs) {
    if (!(file >> cs.id)) return false;
    file.ignore(10000, '\n');
    if (!getline(file, cs.name) || cs.name.empty()) return false;
    if (!(file >> cs.squant >> cs.wsquant >> cs.type)) return false;
    file.ignore(10000, '\n');
    return cs.id > 0 && cs.squant > 0 && cs.wsquant >= 0 && cs.wsquant <= cs.squant;
}

bool loadCount(ifstream& file, string label, int& count) {
    string text;
    if (!getline(file, text) || text != label) return false;
    if (!(file >> count) || count < 0) return false;
    file.ignore(10000, '\n');
    return true;
}

bool loadPipes(ifstream& file, unordered_map<int, Pipe>& pipes, int count) {
    for (int i = 0; i < count; i++) {
        Pipe pipe{};
        if (!loadPipe(file, pipe)) return false;
        if (pipes.find(pipe.id) != pipes.end()) return false;
        pipes[pipe.id] = pipe;
    }
    return true;
}

bool loadStations(ifstream& file, unordered_map<int, CS>& stations, int count) {
    for (int i = 0; i < count; i++) {
        CS cs{};
        if (!loadCS(file, cs)) return false;
        if (stations.find(cs.id) != stations.end()) return false;
        stations[cs.id] = cs;
    }
    return true;
}

bool validPipeIDs(const unordered_map<int, Pipe>& pipes, int nextPipeId) {
    if (nextPipeId < 1) return false;
    for (const auto& item : pipes) {
        int id = item.first;
        if (id != item.second.id) return false;
    }
    return true;
}

bool validCSIDs(const unordered_map<int, CS>& stations, int nextCSId) {
    if (nextCSId < 1) return false;
    for (const auto& item : stations) {
        int id = item.first;
        if (id < 1 || id >= nextCSId) return false;
        if (id != item.second.id) return false;
    }
    return true;
}

bool loadData(ifstream& file, unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations, int& nextPipeId, int& nextCSId) {
    int pipeCount, stationCount;
    string label;
    if (!loadCount(file, "PIPES", pipeCount)) return false;
    if (!loadPipes(file, pipes, pipeCount)) return false;
    if (!loadCount(file, "CS", stationCount)) return false;
    if (!loadStations(file, stations, stationCount)) return false;
    if (!getline(file, label) || label != "NEXT_PIPE_ID") return false;
    if (!(file >> nextPipeId)) return false;
    file.ignore(10000, '\n');
    if (!getline(file, label) || label != "NEXT_CS_ID") return false;
    if (!(file >> nextCSId)) return false;
    return validPipeIDs(pipes, nextPipeId) && validCSIDs(stations, nextCSId);
}

void Load(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations, int& nextPipeId, int& nextCSId) {
    ifstream file(inputString("enter file name to load: "));
    if (!file) { 
        cout << "\nfile not found\n"; return; 
    }
    unordered_map<int, Pipe> newPipes;
    unordered_map<int, CS> newStations;
    int loadedPipeId = 1;
    int loadedCSId = 1;

    if (!loadData(file, newPipes, newStations, loadedPipeId, loadedCSId)) {
        cout << "\nfile data error\n";
        return;
    }

    pipes = newPipes;
    stations = newStations;
    nextPipeId = loadedPipeId;
    nextCSId = loadedCSId;
    cout << "\ndata was loaded\n";
}

void fileMenu(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations, int& nextPipeId, int& nextCSId) {
    cout << "\n1. Save\n";
    cout << "\n2. Load\n";
    cout << "\n0. Back\n";
    int act = inputInt("please, choose: ", 0, 2);

    if (act == 1) Save(pipes, stations, nextPipeId, nextCSId);
    if (act == 2) Load(pipes, stations, nextPipeId, nextCSId);
}
