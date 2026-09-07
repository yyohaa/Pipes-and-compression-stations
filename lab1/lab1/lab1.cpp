// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
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




int main()
{

    Pipe pipe;
    CS compStation;

    bool statePipe = false;
    bool stateCS = false;

    while (true) {
        std::cout << "Hello, user <3! please, choose: \n";
        std::cout << "1. Add a pipe\n";
        std::cout << "2. Add a compression station (CS)\n";
        std::cout << "3. View all\n";
        std::cout << "4. Edit: pipe\n";
        std::cout << "5. Edit: compression station\n";
        std::cout << "6. Save changes\n";
        std::cout << "7. Upload (file)\n";
        std::cout << "0. Exit\n";

    }

    int choice;
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "wrong!( try again with a number..\n" << endl;
    }

    if (choice == 1) {
        cout << "\nADD PIPE\n";
        cout << "Enter start point (km): ";
        cin >> pipe.name;
        cout << "Enter length (km): ";
        cin >> pipe.len;
        cout << "Enter diameter (mm): ";
        cin >> pipe.d;
        pipe.statePipe = false;
        statePipe = true;
        cout << "Pipe added!\n";
    }
    else if (choice == 2) {
        cout << "\nADD CS\n";
        cout << "Enter station name: ";
        cin >> compStation.name;
        cout << "Enter total workshops: ";
        cin >> compStation.squant;
        cout << "Enter class (A, B or C): ";
        cin >> compStation.type;
        compStation.wsquant = compStation.squant;
        stateCS = true;
        cout << "CS added!\n";
    }

}

    




