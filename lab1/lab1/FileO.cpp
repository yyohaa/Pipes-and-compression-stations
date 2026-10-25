
#include "FileO.h"
#include "Input.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

void Save(const vector<Pipe>& pipes, const vector<CS>& stations, int nextId) {
    ofstream file(inputString("enter file name to save: "));
    if (!file) { cout << "\nfile error\n"; return; }

    file << "PIPES\n" << pipes.size() << '\n';
    for (const Pipe& pipe : pipes) savePipe(pipe, file);

    file << "CS\n" << stations.size() << '\n';
    for (const CS& cs : stations) saveCS(cs, file);

    file << "NEXT_ID\n" << nextId << '\n';
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

bool loadPipes(ifstream& file, vector<Pipe>& pipes, int count) {
    for (int i = 0; i < count; i++) {
        Pipe pipe{};
        if (!loadPipe(file, pipe)) return false;
        pipes.push_back(pipe);
    }
    return true;
}

bool loadStations(ifstream& file, vector<CS>& stations, int count) {
    for (int i = 0; i < count; i++) {
        CS cs{};
        if (!loadCS(file, cs)) return false;
        stations.push_back(cs);
    }
    return true;
}

bool validIDs(const vector<Pipe>& pipes, const vector<CS>& stations, int nextId) {
    vector<int> ids;
    for (const Pipe& pipe : pipes) ids.push_back(pipe.id);
    for (const CS& cs : stations) ids.push_back(cs.id);

    for (int i = 0; i < (int)ids.size(); i++) {
        if (ids[i] <= 0 || ids[i] >= nextId) return false;
        for (int j = 0; j < i; j++)
            if (ids[i] == ids[j]) return false;
    }
    return true;
}

bool loadData(ifstream& file, vector<Pipe>& pipes,
    vector<CS>& stations, int& nextId) {
    int pipeCount, stationCount;
    string label;

    if (!loadCount(file, "PIPES", pipeCount) || !loadPipes(file, pipes, pipeCount)) return false;
    if (!loadCount(file, "CS", stationCount) || !loadStations(file, stations, stationCount)) return false;
    if (!getline(file, label) || label != "NEXT_ID") return false;
    if (!(file >> nextId) || nextId < 1) return false;

    return validIDs(pipes, stations, nextId);
}

void Load(vector<Pipe>& pipes, vector<CS>& stations, int& nextId) {
    ifstream file(inputString("enter file name to load: "));
    if (!file) { cout << "\nfile not found\n"; return; }

    vector<Pipe> newPipes;
    vector<CS> newStations;
    int loadedNextId = 1;

    if (!loadData(file, newPipes, newStations, loadedNextId)) {
        cout << "\nfile data error\n";
        return;
    }

    pipes = newPipes;
    stations = newStations;
    nextId = loadedNextId;
    cout << "\ndata was loaded\n";
}

void fileMenu(vector<Pipe>& pipes, vector<CS>& stations, int& nextId) {
    cout << "\n1. Save\n2. Load\n0. Back\n";
    int act = inputInt("please, choose: ", 0, 2);

    if (act == 1) Save(pipes, stations, nextId);
    if (act == 2) Load(pipes, stations, nextId);
}
