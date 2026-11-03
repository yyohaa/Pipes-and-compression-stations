#include "CS.h"
#include <iostream>
#include <unordered_map>
#include "Input.h"

using namespace std;
void addCS(CS& cs);
int unusedPercent(const CS& cs);

void CS::view() const {
	cout << "\nCS\n";
	cout << "ID: " << id << endl;
	cout << "name: " << name << endl;
	cout << "total of workshops: " << squant << endl;
	cout << "total of working workshops: " << wsquant << endl;
	cout << "calss: " << type << endl;
}

void addCS(CS& cs) {
	cout << "add a compression station\n";
	cs.name = inputString("enter a name: ");
	cs.squant = plusInt("enter total number of workshops: ");
	cs.wsquant = inputInt("enter working total of workshops: ", 0, cs.squant);
	string className = inputString("enter class: ");
	cs.type = className[0];
}

void addNewCS(unordered_map<int,CS>& stations, int& nextId) {
	CS cs{};
	addCS(cs);
	cs.id = nextId++;
	stations[cs.id]=cs;
	cout << "CS added, ID:" << cs.id << endl;
}

void viewStations(const unordered_map<int, CS>& stations) {
	if (stations.empty()) {
		cout << "\nno stations added\n";
		return;
	}
	for (const auto& item : stations) {
		item.second.view();
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

void editSelectedCS(unordered_map<int,CS>& stations) {
	if (stations.empty()) {
		cout << "no stations added\n";
		return;
	}
	viewStations(stations);
	int id = plusInt("enter CS ID: ");
	auto it = stations.find(id);
	if (it == stations.end()) {
		cout << "CS not found\n";
		return;
	}
	editCS(it -> second);
}

void deleteSelectedCS(unordered_map<int, CS>& stations) {
	if (stations.empty()) {
		cout << "no stations added\n";
		return;
	}
	viewStations(stations);
	int id = plusInt("enter CS ID to delete: ");
	if (stations.find(id) == stations.end()) {
		cout << "CS not found\n";
		return;
	}
	stations.erase(id);
	cout << "CS deleted\n";
}

void findStationsByName(const unordered_map<int, CS>& stations) {
	string name = inputString("enter name: ");
	int found = 0;
	for (const auto& item : stations) {
		const CS& cs = item.second;
		if (cs.name == name) {
			cs.view();
			found++;
		}
	}
	if (found == 0) cout << "no stations found\n";
}

int unusedPercent(const CS& cs) {
	if (cs.squant == 0) return 0;
	return (cs.squant - cs.wsquant) * 100 / cs.squant;
}

void findStationsByPercent(const unordered_map<int, CS>& stations) {
	int percent = inputInt("unused percent (0-100): ", 0, 100);
	int found = 0;
	for (const auto& item : stations) {
		const CS& cs = item.second;
		if (unusedPercent(cs) == percent) {
			cs.view();
			found++;
		}
	}
	if (found == 0) cout << "no stations found\n";
}

void searchStations(const unordered_map<int, CS>& stations) {
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

void stationMenu(unordered_map<int, CS>& stations) {
	cout << "\n1. Edit a CS\n";
	cout << "2. Delete a CS\n";
	cout << "3. search stations\n";
	cout << "0. Back\n";
	int act = inputInt("please, choose: ", 0, 3);
	if (act == 1) editSelectedCS(stations);
	if (act == 2) deleteSelectedCS(stations);
	if (act == 3) searchStations(stations);
}
