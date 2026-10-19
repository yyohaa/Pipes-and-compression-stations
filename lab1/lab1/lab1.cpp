// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Pipe.h"
#include "CS.h"

using namespace std;



int inputInt(string text, int min, int max) {
    while (true) {
        cout << text;
        string line;
        getline(cin, line);

        stringstream ss(line);
        int val;

        if (ss >> val) {
            ss >> ws;
            if (ss.eof() && val >= min && val <= max) {
                return val;
            }
        }
        cout << "wrong input, try again :)\n";
    }
}
int plusInt(string text) {
    while (true) {
        cout << text;
        string line;
        getline(cin, line);

        stringstream ss(line);
        int val;

        if (ss >> val) {
            ss >> ws;
            if (ss.eof() && val >0) {
                return val;
            }
        }
        cout << "wrong input, try again with a positive number :)\n";
    }

}
double plusDouble(string text) {
    while (true) {
        cout << text;
        string line;
        getline(cin, line);

        stringstream ss(line);
        double val;

        if (ss >> val) {
            ss >> ws;
            if (ss.eof() && val > 0) {
                return val;
            }
        }
        cout << "wrong input, try again with a positive number :)\n";
    }
}
string inputString(string text) {
    while (true) {
        cout << text;
        string val;
        getline(cin, val);

        if (!val.empty() && val.find_first_not_of(" \t") != string::npos) {
            return val;
        }
        cout << "wrong input, try again, name cannot be empty :)\n";
    }
}

void addPipe(Pipe& pipe){
    cout << "add a pipe\n";
    pipe.name = inputString("enter name: ");
    pipe.len = plusDouble("enter lenght(km): ");
    pipe.d = plusInt("enter diameter (mm): ");
    pipe.statePipe = inputInt("is a pipe under construction (1-yes, 0-no): \n", 0, 1);
    }
void addCS(CS& cs) {
    cout << "add a compression station\n";
    cs.name = inputString("enter a name: ");
    cs.squant = plusInt("enter total number of workshops: ");
    cs.wsquant = inputInt("enter working total of workshops: ", 0, cs.squant);

    cout << "enter class: ";
    cin >> cs.type;

    cin.ignore(10000, '\n');
}
void editPipe(Pipe& pipe) {
    if (pipe.name == "") {
        cout << "\npipe has not been added\n";
        return;
    }

    pipe.view();
    bool newState = inputInt("\nis pipe under repair? (1-yes, 0-no): ", 0, 1);
    if (newState != pipe.statePipe) {
        pipe.statePipe = newState;
        cout<< "pipe changed\n";
    }
    else {
        cout << "no changes were applied\n";
    }
}
void editCS(CS& cs) {
    if (cs.name == "") {
        cout << "\nworkshop has not been added\n\n";
        return;
    }
    cs.view();
    cout << "\n1.start workshop\n";
    cout << "\n2.stop workshop\n";
    int act = inputInt("please, choose: ",1,2);
    if (act == 1) {
        if (cs.wsquant < cs.squant) {
            cs.wsquant++;
            cout << "workshop started\n";
        }
        else {
            cout << "all workshops are already working\n";
        }
    }
    else if (act == 2) {
        if (cs.wsquant > 0) {
            cs.wsquant--;
            cout << "workshop stopped\n";
        }
        else {
            cout << "there are no working workshops(((\n";
        }
    
    }
}
void savePipe(const Pipe& pipe, ofstream& file) {
    file << "PIPE" << endl;
    if (pipe.name != "") {
        file << 1 << endl;
        file << pipe.name << endl;
        file << pipe.len << endl;
        file << pipe.d << endl;
        file << pipe.statePipe << endl;
    }
    else {
        file << 0 << endl;
    }
}

void saveCS(const CS& cs, ofstream& file) {
    file << "CS" << endl;
    if (cs.name != "") {
        file << 1 << endl;
        file << cs.name << endl;
        file << cs.squant << endl;
        file << cs.wsquant << endl;
        file << cs.type << endl;
    }
    else {
        file << 0 << endl;
    }
}

void Save(const Pipe&pipe, const CS&cs) {
    ofstream file("labaodin.txt");
    if (!file) {
        cout << "\nfile error\n";
        return;
    }
    savePipe(pipe, file);
    saveCS(cs, file);
        file.close();
        cout<< "\ndata was saved\n";
}

bool loadPipe(ifstream& file, Pipe& pipe) {
    string objType;
    int exists;

    getline(file, objType);

    if (objType != "PIPE") {
        cout << "\nfile error: pipe data not found\n";
        return false;
    }

    file >> exists;
    file.ignore(10000, '\n');

    if (exists == 1) {
        getline(file, pipe.name);
        file >> pipe.len;
        file >> pipe.d;
        file >> pipe.statePipe;

        file.ignore(10000, '\n');
    }
    else {
        pipe = Pipe{};
    }

    return true;
}


bool loadCS(ifstream& file, CS& cs) {
    string objType;
    int exists;

    getline(file, objType);

    if (objType != "CS") {
        cout << "\nfile error: CS data not found\n";
        return false;
    }

    file >> exists;
    file.ignore(10000, '\n');

    if (exists == 1) {
        getline(file, cs.name);
        file >> cs.squant;
        file >> cs.wsquant;
        file >> cs.type;

        file.ignore(10000, '\n');
    }
    else {
        cs = CS{};
    }

    return true;
}


void Load(Pipe& pipe, CS& cs) {
    ifstream file("labaodin.txt");

    if (!file) {
        cout << "\nfile not found\n";
        return;
    }
    if (!loadPipe(file, pipe)) {
        return;
    }
    if (!loadCS(file, cs)) {
        return;
    }
    file.close();
    cout << "\ndata was loaded\n";
}


int main()
{
    Pipe pipe;
    CS compStation;
    
    int mem;
    for (;;) {
        cout << "\n\nHello, user<3! please, choose: " << endl;
        cout << "1. Add a pipe" << endl;
        cout << "2. Add a compression station (CS)" << endl;
        cout << "3. View all" << endl;
        cout << "4. Edit: pipe" << endl;
        cout << "5. Edit: compression station" << endl;
        cout << "6. Save changes" << endl;
        cout << "7. Upload (file)" << endl;
        cout << "0. Exit" << endl;

        mem = inputInt("please, choose: ", 0, 7);

        switch (mem) {
        case 1:
            addPipe(pipe);
            break;
        case 2:
            addCS(compStation);
            break;
        case 3:
            pipe.view();
            compStation.view();
            break;
        case 4:
            editPipe(pipe);
            break;
        case 5:
            editCS(compStation);
            break;
        case 6:
            Save(pipe, compStation);
            break;
        case 7:
            Load(pipe, compStation);
            break;
        case 0:
            return 0;
        default:
            cout << "sorry((( wrong choice(((\n" << endl;
            break;
        }
    }
}

