// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
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

        switch (mem) {
        case 1:
            std::cout << "1. Add a pipe\n" << endl;
            break;
        case 2:
            std::cout << "2. Add a compression station (CS)\n" << endl;
            
            break;
        case 3:
            std::cout << "3. View all\n" << endl;
            
            break;
        case 4:
            std::cout << "4. Edit: pipe\n" << endl;
            
            break;
        case 5:
            std::cout << "5. Edit: compression station\n" << endl;
            
            break;
        case 6:
            std::cout << "6. Save changes\n" << endl;
            
            break;
        case 7:
            std::cout << "7. Upload (file)\n" << endl;
           
            break;
        case 0:
            std::cout << "0. Exit\n" << endl;
            _getch;
            return 0;
            break;
        default:
            std::cout << "Hello, user<3! please, choose: \n" << endl;
            _getch;
            break;
        }
    }
    

    if (cin.fail()) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "wrong!( try again with a number..\n" << endl;
    }

    

}

    




