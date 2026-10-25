#include "Pipe.h"
#include <vector>
#include <iostream>
#include "Input.h"

using namespace std;

void Pipe::view() const {
	if (name.empty()) {
		cout << "\npipe has not been added\n";
		return;
	}
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

void addNewPipe(vector<Pipe>& pipes, int& nextId) {
	Pipe pipe{};
	addPipe(pipe);
	pipe.id = nextId++;
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

void pipeMenu(vector<Pipe>& pipes) {
	cout << "\n1. edit a pipe\n";
	cout << "\n2. delete a pipe\n";
	cout << "\n3. back\n";

	int act = inputInt("please, choose: ", 0, 2);
	if (act == 1) editSelectedPipe(pipes);
	if (act == 2) deleteSelectedPipe(pipes);
}