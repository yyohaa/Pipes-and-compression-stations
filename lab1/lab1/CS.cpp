#include "CS.h"
#include <iostream>

using namespace std;

void CS::view() const {
	if (name == " ") {
		cout << "\npipe has not been added\n";
		return;
	}
	cout << "\nCS\n";
	cout << "\nname: \n" << name << endl;
	cout << "\ntotal of workshops: \n" << squant << endl;
	cout << "\ntotal of working workshops: \n" << wsquant << endl;
	cout << "\ncalss: \n" << type << endl;
}
