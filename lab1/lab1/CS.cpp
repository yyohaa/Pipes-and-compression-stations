#include "CS.h"
#include <iostream>
#include <vector>
#include "Input.h"

using namespace std;

void CS::view() const {
	cout << "\nCS\n";
	cout << "ID: " << id << endl;
	cout << "name: " << name << endl;
	cout << "total of workshops: " << squant << endl;
	cout << "total of working workshops: " << wsquant << endl;
	cout << "calss: " << type << endl;
}

void addNewCS(vector<CS>& stations, int& nextId) {
	CS cs{};
	addCS(cs);
	cs.id = nextId++;
	stations.push_back(cs);
	cout << "CS added, ID:" << cs.id << endl;
}


void addCS(CS& cs) {
	cout << "add a compression station\n";
	cs.name = inputString("enter a name: ");
	cs.squant = plusInt("enter total number of workshops: ");
	cs.wsquant = inputInt("enter working total of workshops: ", 0, cs.squant);
	string className = inputString("enter class: ");
	cs.type = className[0];
}

void viewStations(const vector<CS>& stations) {
	if (stations.empty()) {
		cout << "\nno stations added\n";
		return;
	}
	for (const CS& cs : stations) {
		cs.view();
	}
}

void editCS(CS& cs) {
	cs.view();
	cout << "\n1.start workshop\n";
	cout << "2.stop workshop\n";
	int act = inputInt("please, choose: ", 1, 2);
	if (act == 1) {
		if (cs.wsquant < cs.squant) {
			cs.wsquant++;
			cout << "workshop started\n";
		}
		else cout << "all workshops are already working\n";
	}
	else {
		if (cs.wsquant > 0) {
			cs.wsquant--;
			cout << "workshop stopped\n";
		}
		else cout << "there are no working workshops\n";
	}
}

int findCS(const vector<CS>& stations, int id) {
	for (int i = 0; i < (int)stations.size(); i++) {
		if (stations[i].id == id) {
			return i;
		}
	}
	return -1;
}

void editSelectedCS(vector<CS>& stations) {
	if (stations.empty()) {
		cout << "no stations added\n";
		return;
	}
	viewStations(stations);
	int id = plusInt("enter CS ID: ");
	int index = findCS(stations, id);
	if (index == -1) {
		cout << "CS not found\n";
		return;
	}
	editCS(stations[index]);
}

void deleteSelectedCS(vector<CS>& stations) {
	if (stations.empty()) {
		cout << "no stations added\n";
		return;
	}
	viewStations(stations);
	int id = plusInt("enter CS ID to delete: ");
	int index = findCS(stations, id);
	if (index == -1) {
		cout << "CS not found\n";
		return;
	}
	stations.erase(stations.begin() + index);
	cout << "CS deleted\n";
}

void findStationsByName(const vector<CS>& stations) {
	string name = inputString("enter name: ");
	int found = 0;
	for (const CS& cs : stations) {
		if (cs.name == name) {
			cs.view();
			found++;
		}
	}
	if (found == 0) cout << "no stations found\n";
}

void findStationsByPercent(const vector<CS>& stations) {
	int percent = inputInt("unused percent (0-100): ", 0, 100);
	int found = 0;
	for (const CS& cs : stations) {
		if (unusedPercent(cs) == percent) {
			cs.view();
			found++;
		}
	}
	if (found == 0) cout << "no stations found\n";
}

void searchStations(const vector<CS>& stations) {
	if (stations.empty()) {
		cout << "no stations added\n";
		return;
	}
	cout << "\n1. Search by name\n";
	cout << "2. Search by unused percent\n";
	int act = inputInt("choose filter: ", 1, 2);

	if (act == 1) findStationsByName(stations);
	else findStationsByPercent(stations);
}

void stationMenu(vector<CS>& stations) {
	cout << "\n1. Edit a CS\n";
	cout << "2. Delete a CS\n";
	cout << "3. search stations\n";
	cout << "0. Back\n";
	int act = inputInt("please, choose: ", 0, 3);
	if (act == 1) editSelectedCS(stations);
	if (act == 2) deleteSelectedCS(stations);
	if (act == 3) searchStations(stations);
}
