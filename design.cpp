#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <ctime>       /* time_t, struct tm, time, gmtime */
#include <locale>
#include <iomanip>
#include <string>
#include "design.h"

using namespace std;
#include "design.h"

design::border()
{
    cout <<"Border";
    system("pause");
}

design::putToBank(){

    cout <<" __      __ ___  _____  _  _  ___   ___    _ __      __ _    _    ";
    cout <<" \ \    / /|_ _||_   _|| || ||   \ | _ \  /_\\ \    / //_\  | |   ";
    cout <<"  \ \/\/ /  | |   | |  | __ || |) ||   / / _ \\ \/\/ // _ \ | |__ ";
    cout <<"   \_/\_/  |___|  |_|  |_||_||___/ |_|_\/_/ \_\\_/\_//_/ \_\|____|";
    system("pause");

}
