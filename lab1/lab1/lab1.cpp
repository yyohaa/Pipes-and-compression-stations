// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;



struct Pipe {
    string name;
    double len;
    int d;
    bool statePipe;
};

struct CS {
    string name;
    int squant;
    int wsquant;
    char type;
    bool stateCS;
};


void addPipe(Pipe& pipe){
    cout << "add a pipe\n";
    cout << "enter a name: ";
    cin >> pipe.name;
    cout << "enter lenght(km): ";
    cin >> pipe.len;
    cout << "enter diameter (mm): ";
    cin >> pipe.d;
    cout << "is a pipe under repair(construction)(1-yes, 0-no): \n";
    cin >> pipe.statePipe;
    }
void addCS(CS& cs) {
    cout << "add a compression station\n";
    cout << "enter a name: ";
    cin >> cs.name;
    cout << "enter total: ";
    cin >> cs.squant;
    cout << "enter working total: ";
    cin >> cs.wsquant;
    cout << "enter class: ";
    cin >> cs.type;
    cout << "is a CS working(1-yes, 0-no): \n";
    cin >> cs.stateCS;
}
void viewPipe(Pipe & pipe) {
    if (pipe.name == "") {
        cout << "\npipe has not been added\n";
        return;
    }
    cout << "\npipe\n";
    cout << "name: " << pipe.name << endl;
    cout << "lenght: " << pipe.len << endl;
    cout << "diameter: " << pipe.d << endl;

    if (pipe.statePipe)
        cout << "under repair^ yes\n";
    else
        cout << "under repair^ no\n";
}
void viewCS(CS& cs) {
    if (cs.name == "") {
        cout << "\ncompression station has not been added\n";
        return;
    }
    cout << "\nCS\n";
    cout << "name: " << cs.name << endl;
    cout << "total stations: " << cs.squant << endl;
    cout << "total working stations: " << cs.wsquant << endl;
    cout << "calss: " << cs.type << endl;

    if (cs.stateCS)
        cout << "cs is working^ yes\n";
    else
        cout << "cs is not working^ no\n";
}
void editPipe(Pipe& pipe) {
    if (pipe.name == "") {
        cout << "\npipe has not been added\n";
        return;
    }
    cout << "\nis pipe under repair? (1-yes, 0-no): ";
    cin >> pipe.statePipe;
    cout << "pipe changed\n";
}
void editCS(CS& cs) {
    if (cs.name == "") {
        cout << "\ncompression station has not been added\n";
        return;
    }
    int act;
    cout << "\n1.start station\n";
    cout << "\n2.stop station\n";
    cout << "\nplease, choose: \n";
    cin >> act;
    if (act == 1) {
        if (cs.wsquant < cs.squant) {
            cs.wsquant++;
            cs.stateCS = true;
            cout << "station started\n";
        }
        else {
            cout << "all stations are already working\n";
        }
    }
    else if (act == 2) {
        if (cs.wsquant > 0) {
            cs.wsquant--;
            if (cs.wsquant == 0)
                cs.stateCS = false;
            cout << "station stopped\n";
        }
        else {
            cout << "there are no working stations(((\n";
        }
    }
    else {
        cout << "sorry, wrong choice(((";
    }
}
void Save(Pipe& pipe, CS& cs) {
    ofstream file("labaodin.txt");
    if (!file) {
        cout << "file error";
        return;
    }
    file << pipe.name << endl;
    file << pipe.len << endl;
    file << pipe.d << endl;
    file << pipe.statePipe << endl;
    file << cs.name << endl;
    file << cs.squant << endl;
    file << cs.wsquant << endl;
    file << cs.type << endl;
    file << cs.stateCS << endl;

    file.close();
    cout << "\ndata was saved\n";
}
void Load(Pipe& pipe, CS& cs) {
    ifstream file("labaodin.txt");
    if (!file) {
        cout << "\nfile not found\n";
        return;
    }
    file >> pipe.name;
    file >> pipe.len;
    file >> pipe.d;
    file >> pipe.statePipe;
    file >>cs.name;
    file >> cs.squant;
    file >> cs.wsquant;
    file >> cs.type;
    file >> cs.stateCS;

    file.close();
    cout << "\ndata was loaded\n";
}

int main()
{

    Pipe pipe;
    CS compStation;
    
    int mem;

    for (;;) {
        std::cout << "Hello, user<3! please, choose: " << endl;
        std::cout << "1. Add a pipe" << endl;
        std::cout << "2. Add a compression station (CS)" << endl;
        std::cout << "3. View all" << endl;
        std::cout << "4. Edit: pipe" << endl;
        std::cout << "5. Edit: compression station" << endl;
        std::cout << "6. Save changes" << endl;
        std::cout << "7. Upload (file)" << endl;
        std::cout << "0. Exit" << endl;
        cin >> mem;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "wrong!( try again with a number..\n" << endl;
        }
        switch (mem) {
        case 1:
            addPipe(pipe);
            break;
        case 2:
            addCS(compStation);
            break;
        case 3:
            viewPipe(pipe);
            viewCS(compStation);
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
            _getch();
            return 0;
            break;
        default:
            std::cout << "sorry((( wrong choice(((\n" << endl;
            _getch();
            break;
        }
    }
}

    




