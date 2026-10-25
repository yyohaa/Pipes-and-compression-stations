// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Pipe.h"
#include "CS.h"
#include "Input.h"
#include "FileO.h"

using namespace std;

int main()
{
    vector <Pipe> pipes;
    vector <CS> stations;
    int nextId = 1;
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
            addNewPipe(pipes, nextId);
            break;
        case 2:
            addNewCS(stations, nextId);
            break;
        case 3:
            viewPipes(pipes);
            viewStations(stations);
            break;
        case 4:
            editSelectedPipe(pipes);
            break;
        case 5:
            editSelectedCS(stations);
            break;
        case 6:
            fileMenu(pipes, stations, nextId);
            break;
        case 0:
            return 0;
        default:
            cout << "sorry((( wrong choice(((\n" << endl;
            break;
        }
    }
}

