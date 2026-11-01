#include "Pipe.h"
#include <iostream>
#include "Input.h"

using namespace std;

void Pipe::view() const {
	cout << "\npipe\n";
	cout << "ID: " << id << endl;
	cout << "name: " << name << endl;
	cout << "length: " << len << endl;
	cout << "diameter: " << d << endl;
	cout << "under repair? - " << (statePipe ? "yes" : "no") << endl;
}

int findPipe(const vector<Pipe>& pipes, int id) {
	for (int i = 0; i < (int)pipes.size(); i++) {
		if (pipes[i].id == id) {
			return i;
		}
	}
	return -1;
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

void addNewPipe(vector<Pipe>& pipes, int& nextPipeId) {
	Pipe pipe{};
	addPipe(pipe);
	pipe.id = nextPipeId++;
	pipes.push_back(pipe);
	cout << "pipe added, ID:" << pipe.id << endl;
}

void viewPipes(const vector<Pipe>& pipes) {
	if (pipes.empty()) {
		cout << "\nno pipes added\n";
		return;
	}
	for (const Pipe& pipe : pipes) {
		pipe.view();
	}
}

void editSelectedPipe(vector<Pipe>& pipes) {
	if (pipes.empty()) {
		cout << "no pipes added\n";
		return;
	}
	viewPipes(pipes);
	int id = plusInt("enter pipe id: ");
	int index = findPipe(pipes, id);
	if (index == -1) {
		cout << "pipe not found\n";
		return;
	}
	editPipe(pipes[index]);
}

void deleteSelectedPipe(vector<Pipe>& pipes) {
	if (pipes.empty()) {
		cout << "no pipes added\n";
		return;
	}
	viewPipes(pipes);
	int id = plusInt("enter pipe id: ");
	int index = findPipe(pipes, id);
	if (index == -1) {
		cout << "pipe not found\n";
		return;
	}
	pipes.erase(pipes.begin() + index);
	cout << "pipe deleted\n";
}

vector <int> findPipesByName(const vector<Pipe>& pipes, string name) {
	vector <int> found;
	for (const Pipe& pipe : pipes) {
		if (pipe.name == name) {
			found.push_back(pipe.id);
		}
	}
	return found;
}

vector <int> findPipesByState(const vector<Pipe>& pipes, bool state) {
	vector <int> found;
	for (const Pipe& pipe : pipes) {
		if (pipe.statePipe == state) {
			found.push_back(pipe.id);
		}
	}
	return found;
}

void viewFoundPipes(const vector<Pipe>& pipes, const vector<int>& found) {
	if (found.empty()) {
		cout << "no pipes found\n";
		return;
	}
	for (int id : found) {
		int index = findPipe(pipes, id);
		if (index != -1) {
			pipes[index].view();
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

void editManyPipes(vector<Pipe>& pipes, const vector<int>& ids) {
	if (ids.empty()) return;
	bool state = inputInt("new repair status (1-yes, 0-no): ", 0, 1);
	for (int id : ids) {
		int index = findPipe(pipes, id);
		if (index != -1) {
			pipes[index].statePipe = state;
		}
	}
	cout << "pipes updated\n";
}

void deleteManyPipes(vector<Pipe>& pipes, const vector<int>& ids) {
	if (ids.empty()) return;
	for (int id : ids) {
		int index = findPipe(pipes, id);
		if (index != -1) {
			pipes.erase(pipes.begin() + index);
		}
	}
	cout << "pipes deleted\n";
}

void batchPipeMenu(vector<Pipe>& pipes, const vector<int>& found) {
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

void searchPipes(vector<Pipe>& pipes) {
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


void pipeMenu(vector<Pipe>& pipes) {
	cout << "\n1. edit a pipe\n";
	cout << "\n2. delete a pipe\n";
	cout << "\n3. search pipes\n";
	cout << "\n4. back\n";

	int act = inputInt("please, choose: ", 0, 3);
	if (act == 1) editSelectedPipe(pipes);
	if (act == 2) deleteSelectedPipe(pipes);
	if (act == 3) searchPipes(pipes);
}