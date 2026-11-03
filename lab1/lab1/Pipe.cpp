#include "Pipe.h"
#include <iostream>
#include "Input.h"
#include <vector>

using namespace std;

void Pipe::view() const {
	cout << "\npipe\n";
	cout << "ID: " << id << endl;
	cout << "name: " << name << endl;
	cout << "length: " << len << endl;
	cout << "diameter: " << d << endl;
	cout << "under repair? - " << (statePipe ? "yes" : "no") << endl;
}

void addPipe(Pipe& pipe) {
	cout << "add a pipe\n";
	pipe.name = inputString("enter name: ");
	pipe.len = plusDouble("enter length (km): ");
	pipe.d = plusInt("enter diameter (mm): ");
	pipe.statePipe = inputInt("is a pipe under repair (1-yes, 0-no): ", 0, 1);
}

void editPipe(Pipe& pipe) {
	pipe.view();
	bool newState = inputInt("is pipe under repair? (1-yes, 0-no): ", 0, 1);
	if (newState != pipe.statePipe) {
		pipe.statePipe = newState;
		cout << "pipe changed\n";
	}
	else {
		cout << "no changes were applied\n";
	}
}

void addNewPipe(unordered_map<int, Pipe>& pipes, int& nextPipeId) {
	Pipe pipe{};
	addPipe(pipe);
	pipe.id = nextPipeId++;
	pipes[pipe.id]=pipe;
	cout << "pipe added, ID:" << pipe.id << endl;
}

void viewPipes(const unordered_map<int, Pipe>& pipes) {
	if (pipes.empty()) {
		cout << "\nno pipes added\n";
		return;
	}
	for (const auto& item : pipes) {
		item.second.view();
	}
}

void editSelectedPipe(unordered_map<int, Pipe>& pipes) {
	if (pipes.empty()) {
		cout << "no pipes added\n";
		return;
	}
	viewPipes(pipes);
	int id = plusInt("enter pipe id: ");
	auto it = pipes.find(id);
	if (it == pipes.end()) {
		cout << "pipe not found\n";
		return;
	}
	editPipe(it->second);
}

void deleteSelectedPipe(unordered_map<int, Pipe>& pipes) {
	if (pipes.empty()) {
		cout << "no pipes added\n";
		return;
	}
	viewPipes(pipes);
	int id = plusInt("enter pipe id: ");
	if (pipes.erase(id) == 0) {
		cout << "pipe not found\n";
		return;
	}
	cout << "pipe deleted\n";
}

vector <int> findPipesByName(const unordered_map<int, Pipe>& pipes, string name) {
	vector <int> found;
	for (const auto& item : pipes) {
		if (item.second.name == name) {
			found.push_back(item.first);
		}
	}
	return found;
}

vector <int> findPipesByState(const unordered_map<int, Pipe>& pipes, bool state) {
	vector <int> found;
	for (const auto& item : pipes) {
		if (item.second.statePipe == state) {
			found.push_back(item.first);
		}
	}
	return found;
}

void viewFoundPipes(const unordered_map<int, Pipe>& pipes, const vector<int>& found) {
	if (found.empty()) {
		cout << "no pipes found\n";
		return;
	}
	for (int id : found) {
		auto it = pipes.find(id);
		if (it != pipes.end()) {
			it->second.view();
		}
	}
}

bool hasId(const vector<int>& ids, int id) {
	for (int number : ids) {
		if (number == id) {
			return true;
		}
	}
	return false;
}

vector<int> selectPipeIds(const vector<int>& found) {
	vector<int> selected;
	int count = inputInt("how many pipes? (0-cancel): ", 0, (int)found.size());
	while ((int)selected.size() < count) {
		int id = plusInt("enter ID from results: ");
		if (!hasId(found, id) || hasId(selected, id)) {
			cout << "wrong ID\n";
			continue;
		}
		selected.push_back(id);
	}
	return selected;
}

void editManyPipes(unordered_map<int, Pipe>& pipes, const vector<int>& ids) {
	if (ids.empty()) return;
	bool state = inputInt("new repair status (1-yes, 0-no): ", 0, 1);
	for (int id : ids) {
		auto it = pipes.find(id);
		if (it != pipes.end()) {
			it->second.statePipe = state;
		}
	}
	cout << "pipes updated\n";
}

void deleteManyPipes(unordered_map<int, Pipe>& pipes, const vector<int>& ids) {
	if (ids.empty()) return;
	for (int id : ids) {
		pipes.erase(id);
	}
	cout << "pipes deleted\n";
}

void batchPipeMenu(unordered_map<int, Pipe>& pipes, const vector<int>& found) {
	cout << "\n1. Edit all found\n";
	cout << "2. Edit selected\n";
	cout << "3. Delete all found\n";
	cout << "4. Delete selected\n";
	cout << "0. Back\n";
	int act = inputInt("choose: ", 0, 4);
	if (act == 0) return;
	vector<int> selected = found;
	if (act == 2 || act == 4) {
		selected = selectPipeIds(found);
	}
	if (act == 1 || act == 2) editManyPipes(pipes, selected);
	else deleteManyPipes(pipes, selected);
}

void searchPipes(unordered_map<int, Pipe>& pipes) {
	if (pipes.empty()) {
		cout << "no pipes added\n";
		return;
	}
	cout << "\n1. Search by name\n";
	cout << "2. Search by repair\n";
	int filter = inputInt("choose filter: ", 1, 2);
	vector<int> found;
	if (filter == 1)
		found = findPipesByName(pipes, inputString("enter name: "));
	else
		found = findPipesByState(pipes, inputInt("in repair (1/0): ", 0, 1));
	viewFoundPipes(pipes, found);
	if (!found.empty()) batchPipeMenu(pipes, found);
}

void pipeMenu(unordered_map<int, Pipe>& pipes) {
	cout << "\n1. edit a pipe\n";
	cout << "\n2. delete a pipe\n";
	cout << "\n3. search pipes\n";
	cout << "\n4. back\n";
	int act = inputInt("please, choose: ", 0, 3);
	if (act == 1) editSelectedPipe(pipes);
	if (act == 2) deleteSelectedPipe(pipes);
	if (act == 3) searchPipes(pipes);
}