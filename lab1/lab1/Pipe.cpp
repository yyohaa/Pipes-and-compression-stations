#include "Pipe.h"
#include <iostream>

using namespace std;

void Pipe::view() const {
	if (name == " ") {
		cout << "\npipe has not been added\n";
		return;
	}
	cout << "\npipe\n";
	cout << "\name: \n" << name << endl;
	cout << "\nlength: \n" << len << endl;
	cout << "\ndiameter: \n" << d << endl;
	cout << "\nunder repair? - \n" << (statePipe ? "yes" : "no") << endl;
}