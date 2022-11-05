#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <ctime>       /* time_t, struct tm, time, gmtime */
#include <locale>
#include <iomanip>
#include <string>
#include <windows.h>
#include "design.h"
#define RED "\033[31m"
#define WHITE"\033[37m"
#define WHTBG "\033[107m"

using namespace std;

void gotoxy(int x,int y);
HANDLE d= GetStdHandle(STD_OUTPUT_HANDLE);  //d ang pag-change color sa main

design:: secondBorder()
{
    system("COLOR");
    SetConsoleTextAttribute(d,4);

     gotoxy(9,4);cout<<RED"     ________________________________________________________________________________________________________________________ ";
     gotoxy(9,5);cout<<RED" .'  ______________________________________________________________________________________________________________________   '.";
     gotoxy(9,6);cout<<RED": .'                                                                                                                        '. :";
     gotoxy(9,8);cout<<RED"| |";                                                                                                gotoxy(134,8);cout<<RED"| |";
     gotoxy(9,9);cout<<RED"| |";                                                                                                gotoxy(134,9);cout<<RED"| |";
     gotoxy(9,10);cout<<RED"| |";                                                                                                gotoxy(134,10);cout<<RED"| |";
     gotoxy(9,11);cout<<RED"| |";                                                                                                gotoxy(134,11);cout<<RED"| |";


     gotoxy(9,44);cout <<RED": '.______________________________________________________________________________________________________________________.'  :";
     gotoxy(9,45);cout <<RED" .__________________________________________________________________________________________________________________________. ";
    SetConsoleTextAttribute(d,15);
}

design:: homeTitle(){
    SetConsoleTextAttribute(d,15);


    gotoxy(55,10);cout <<"                _--_";
    gotoxy(55,11);cout <<"                /   -)";
    gotoxy(55,12);cout <<"            ___/___|___";
    gotoxy(55,13);cout <<"____-----=~~///|     ||||~~~==-----_____";

    gotoxy(43,15);cout<<"______  _   _  _____   _____  _____  ______   ___   _   _  _   __";
    gotoxy(43,16);cout<<"| ___ \\| | | ||_   _| |_   _||  _  | | ___ \\ / _ \\ | \\ | || | / /";
    gotoxy(43,17);cout<<"| |_/ /| | | |  | |     | |  | | | | | |_/ // /_\\ \\|  \\| || |/ / ";
    gotoxy(43,18);cout<<"|  __/ | | | |  | |     | |  | | | | | ___ \\|  _  || . ` ||    \\ ";
    gotoxy(43,19);cout<<"| |    | |_| |  | |     | |  \\ \\_/ / | |_/ /| | | || |\\  || |\\  \\";
    gotoxy(43,20);cout<<"\\_|     \\___/   \\_/     \\_/   \\___/  \\____/ \\_| |_/\\_| \\_/\\_| \\_/ MANILA";
    gotoxy(43,21);cout<<"____________________________________________________________________";
    gotoxy(43,22);cout<<"         T H E   B A N K   O F   T H E   G R E Y H A W K S  ";

     gotoxy(43,27);
}

design::usb(){
    SetConsoleTextAttribute(d,15);
    gotoxy(55,26); cout << R"(
                                                                    ________________________
                                                        __________.'                        '.
                                                       |          |     _____ _____ _____    |
                                                       |   [O] o  |    |  |  |   __| __  |   |
                                                       |          |    |  |  |__   | __ -|   |
                                                       |   [O] o  |    |_____|_____|_____|   |
                                                       |__________|                          |
                                                                  '._______________________.'

            )";
 }

design:: loadingBar(){

    system("COLOR");
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    // Initialize char for printing
    // loading bar
    char a=177;
    char l= 219;

    cout<<"\n";gotoxy(50,43);
    for (int i = 0; i < 50; i++)
        cout<<WHITE<<a;
    // Set the cursor again starting
    // point of loading bar
    //cout<<"\t\t\t\t";
    cout<<"\r";gotoxy(50,43);
    // Print loading bar progress
    for (int i = 0; i < 54; i++) {
         cout<<RED<<l;

        // Sleep for 1 second
        Sleep(10);
    //gotoxy(25,46);cout<<WHITE;system("pause");
    }
    SetConsoleTextAttribute(d,15);
}

design:: eagle(){
int i;


 gotoxy(51,26);cout<<"           ___----------___";
 gotoxy(51,27);cout<<"        _--                ----__";
 gotoxy(51,28);cout<<"       -                         ---_";
 gotoxy(51,29);cout<<"      -___    ____---_              --_";
 gotoxy(51,30);cout<<"  __---_ .-_--   _ O _-                -";
 gotoxy(51,31);cout<<" -      -_-       ---                   -";
 gotoxy(51,32);cout<<"-   __---------___                       -";
 gotoxy(51,33);cout<<"- _----                                  -";
 gotoxy(51,34);cout<<" -     -_                                 _";
 gotoxy(51,35);cout<<" `      _-                                 _";
 gotoxy(51,36);cout<<"       _                           _-_  _-_ _";
 gotoxy(51,37);cout<<"      _-                   ____    -_  -   --";
 gotoxy(51,38);cout<<"      -   _-__   _    __---    -------       -";
 gotoxy(51,39);cout<<"     _- _-   -_-- -_--                        _";
 gotoxy(51,40);cout<<"     -_-                                       _";
 gotoxy(51,41);cout<<"    _-                                          _";
 gotoxy(51,42);cout<<" L     O       A       D       I       N       G";



}

design::eagleLogo(){

    gotoxy(55,7);cout <<"                _--_";
    gotoxy(55,8);cout <<"                /   -)";
    gotoxy(55,9);cout <<"            ___/___|___";
    gotoxy(55,10);cout <<"____-----=~~///|     ||||~~~==-----_____";

}

design:: registration(){
    eagleLogo();
     gotoxy(40,11);cout<<" ___  ___  ___  ___  ___  _____  ___    _  _____  ___  ___   _  _ ";
     gotoxy(40,12);cout<<"| _ \\| __|/ __||_ _|/ __||_   _|| _ \\  /_\\|_   _||_ _|/ _ \\ | \\| |";
     gotoxy(40,13);cout<<"|   /| _|| (_ | | | \\__ \\  | |  |   / / _ \\ | |   | || (_) || .` |";
     gotoxy(40,14);cout<<"|_|_\\|___|\\___||___||___/  |_|  |_|_\\/_/ \\_\\|_|  |___|\\___/ |_|\\_|";

}

design:: balInquiry(){
    eagleLogo();
    gotoxy(55,11); cout << R"(
                                 ___    _    _       _    _  _   ___  ___   ___  _  _   ___   _   _  ___  ___ __   __
                                | _ )  /_\  | |     /_\  | \| | / __|| __| |_ _|| \| | / _ \ | | | ||_ _|| _ \\ \ / /
                                | _ \ / _ \ | |__  / _ \ | .` || (__ | _|   | | | .` || (_) || |_| | | | |   / \ V /
                                |___//_/ \_\|____|/_/ \_\|_|\_| \___||___| |___||_|\_| \__\_\ \___/ |___||_|_\  |_|

        )";


}

design:: withdrawal(){
    eagleLogo();
    gotoxy(55,11); cout << R"(
                                            __      __ ___  _____  _  _  ___   ___    _ __      __ _    _
                                            \ \    / /|_ _||_   _|| || ||   \ | _ \  /_\\ \    / //_\  | |
                                             \ \/\/ /  | |   | |  | __ || |) ||   / / _ \\ \/\/ // _ \ | |__
                                              \_/\_/  |___|  |_|  |_||_||___/ |_|_\/_/ \_\\_/\_//_/ \_\|____|

        )";
}

design:: deposit(){
    eagleLogo();
    gotoxy(55,11); cout << R"(
                                             ___    _    ___  _  _   ___   ___  ___   ___   ___  ___  _____
                                            / __|  /_\  / __|| || | |   \ | __|| _ \ / _ \ / __||_ _||_   _|
                                           | (__  / _ \ \__ \| __ | | |) || _| |  _/| (_) |\__ \ | |   | |
                                            \___|/_/ \_\|___/|_||_| |___/ |___||_|   \___/ |___/|___|  |_|

        )";
}

design:: fundTransfer(){
    eagleLogo();
    gotoxy(55,11); cout << R"(
                                             ___  _   _  _  _  ___    _____  ___    _    _  _  ___  ___  ___  ___
                                            | __|| | | || \| ||   \  |_   _|| _ \  /_\  | \| |/ __|| __|| __|| _ \
                                            | _| | |_| || .` || |) |   | |  |   / / _ \ | .` |\__ \| _| | _| |   /
                                            |_|   \___/ |_|\_||___/    |_|  |_|_\/_/ \_\|_|\_||___/|_|  |___||_|_\

        )";
}

design:: history(){
    eagleLogo();
    gotoxy(55,11); cout << R"(
                                          _____  ___    _    _  _  ___    _    ___  _____  ___  ___   _  _
                                         |_   _|| _ \  /_\  | \| |/ __|  /_\  / __||_   _||_ _|/ _ \ | \| |
                                           | |  |   / / _ \ | .` |\__ \ / _ \| (__   | |   | || (_) || .` |
                                           |_|  |_|_\/_/ \_\|_|\_||___//_/ \_\\___|  |_|  |___|\___/ |_|\_|
                                                     _  _  ___  ___  _____  ___   ___ __   __
                                                    | || ||_ _|/ __||_   _|/ _ \ | _ \\ \ / /
                                                    | __ | | | \__ \  | | | (_) ||   / \ V /
                                                    |_||_||___||___/  |_|  \___/ |_|_\  |_|
        )";
}

design:: changePin(){
    eagleLogo();
    gotoxy(55,11); cout << R"(
                                                 ___  _  _    _    _  _   ___  ___   ___  ___  _  _
                                                / __|| || |  /_\  | \| | / __|| __| | _ \|_ _|| \| |
                                               | (__ | __ | / _ \ | .` || (_ || _|  |  _/ | | | .` |
                                                \___||_||_|/_/ \_\|_|\_| \___||___| |_|  |___||_|\_|

        )";
}

design :: accDetails(){
    gotoxy(35,27);cout<<"          _   ___ ___ ___  _   _ _  _ _____   ___  ___ _____ _   ___ _    ___  ";
    gotoxy(35,28);cout<<"          /_\\ / __/ __/ _ \\| | | | \\| |_   _| |   \\| __|_   _/_\\ |_ _| |  / __| ";
    gotoxy(35,29);cout<<"         / _ \\ (_| (_| (_) | |_| | .` | | |   | |) | _|  | |/ _ \\ | || |__\\__ \\ ";
    gotoxy(35,30);cout<<"        /_/ \\_\\___\\___\\___/ \\___/|_|\\_| |_|   |___/|___| |_/_/ \\_\\___|____|___/ ";

}

design:: menuScreen(){ // sa may menu

       gotoxy(13,16);cout <<WHITE"  _________________________________________________________________________________________________________________";
    gotoxy(13,17);cout <<RED" .:__________________________________________________________________________________________________________________:.";
    gotoxy(13,18);cout <<RED"|";                                                                                        gotoxy(132,18);cout <<RED"|";
    gotoxy(13,19);cout <<RED"|";                                                                                        gotoxy(132,19);cout <<RED"|";
    gotoxy(13,20);cout <<RED"|";                                                                                        gotoxy(132,20);cout <<RED"|";
    gotoxy(13,21);cout <<RED"|";                                                                                        gotoxy(132,21);cout <<RED"|";
    gotoxy(13,22);cout <<RED"|";                                                                                        gotoxy(132,22);cout <<RED"|";
    gotoxy(13,23);cout <<RED"|";                                                                                        gotoxy(132,23);cout <<RED"|";
    gotoxy(13,24);cout <<RED"|";                                                                                        gotoxy(132,24);cout <<RED"|";
    gotoxy(13,25);cout <<RED"|";                                                                                        gotoxy(132,25);cout <<RED"|";
    gotoxy(13,26);cout <<RED"|";                                                                                        gotoxy(132,26);cout <<RED"|";
    gotoxy(13,27);cout <<RED"|";                                                                                        gotoxy(132,27);cout <<RED"|";
    gotoxy(13,28);cout <<RED"|";                                                                                        gotoxy(132,28);cout <<RED"|";
    gotoxy(13,29);cout <<RED"|";                                                                                        gotoxy(132,29);cout <<RED"|";
    gotoxy(13,30);cout <<RED"|";                                                                                        gotoxy(132,30);cout <<RED"|";
    gotoxy(13,31);cout <<RED"|";                                                                                        gotoxy(132,31);cout <<RED"|";
    gotoxy(13,32);cout <<RED"|";                                                                                        gotoxy(132,32);cout <<RED"|";
    gotoxy(13,33);cout <<RED"|";                                                                                        gotoxy(132,33);cout <<RED"|";
    gotoxy(13,34);cout <<RED"|";                                                                                        gotoxy(132,34);cout <<RED"|";
    gotoxy(13,35);cout <<RED"|";                                                                                        gotoxy(132,35);cout <<RED"|";
    gotoxy(13,36);cout <<RED"|";                                                                                        gotoxy(132,36);cout <<RED"|";
    gotoxy(13,37);cout <<RED"|";                                                                                        gotoxy(132,37);cout <<RED"|";
    gotoxy(13,38);cout <<RED"|";                                                                                        gotoxy(132,38);cout <<RED"|";
    gotoxy(13,39);cout <<RED"| __________________________________________________________________________________________________________________ |";
    gotoxy(13,40);cout <<WHITE"         |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | |  |  |  |  |  |  | |";
    gotoxy(13,41);cout <<" '.___________|__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|___|__|__|__|__|__|__|__|__|__|__|__|__|__|__|_________.'";
}

design:: otherScreen(){ // ask receipt tas go back kineme
gotoxy(13,24);cout <<WHITE"  _________________________________________________________________________________________________________________";
    gotoxy(13,25);cout <<RED" .:__________________________________________________________________________________________________________________:.";
    gotoxy(13,26);cout <<RED"|";                                                                                        gotoxy(132,26);cout <<RED"|";
    gotoxy(13,27);cout <<RED"|";                                                                                        gotoxy(132,27);cout <<RED"|";
    gotoxy(13,28);cout <<RED"|";                                                                                        gotoxy(132,28);cout <<RED"|";
    gotoxy(13,29);cout <<RED"|";                                                                                        gotoxy(132,29);cout <<RED"|";
    gotoxy(13,30);cout <<RED"|";                                                                                        gotoxy(132,30);cout <<RED"|";
    gotoxy(13,31);cout <<RED"|";                                                                                        gotoxy(132,31);cout <<RED"|";
    gotoxy(13,32);cout <<RED"|";                                                                                        gotoxy(132,32);cout <<RED"|";
    gotoxy(13,33);cout <<RED"|";                                                                                        gotoxy(132,33);cout <<RED"|";
    gotoxy(13,34);cout <<RED"|";                                                                                        gotoxy(132,34);cout <<RED"|";
    gotoxy(13,35);cout <<RED"|";                                                                                        gotoxy(132,35);cout <<RED"|";
    gotoxy(13,36);cout <<RED"|";                                                                                        gotoxy(132,36);cout <<RED"|";
    gotoxy(13,37);cout <<RED"|";                                                                                        gotoxy(132,37);cout <<RED"|";
    gotoxy(13,38);cout <<RED"|";                                                                                        gotoxy(132,38);cout <<RED"|";
    gotoxy(13,39);cout <<RED"| __________________________________________________________________________________________________________________ |";
    gotoxy(13,40);cout <<WHITE"         |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | |  |  |  |  |  |  | |";
    gotoxy(13,41);cout <<" '.___________|__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|___|__|__|__|__|__|__|__|__|__|__|__|__|__|__|_________.'";

}

design:: boxes(){ //kasya sa other screen

     gotoxy(29,31);cout <<WHTBG" -------------------- ";          gotoxy(90,31);cout <<WHTBG" -------------------- ";
     gotoxy(29,32);cout <<WHTBG"|                    |";          gotoxy(90,32);cout <<WHTBG"|                    |";
     gotoxy(29,33);cout <<WHTBG" -------------------- ";          gotoxy(90,33);cout <<WHTBG" -------------------- ";

     gotoxy(55,35);cout <<WHTBG" --------------------------- ";
     gotoxy(55,36);cout <<WHTBG"|                           |";
     gotoxy(55,37);cout <<WHTBG" --------------------------- ";
}

design:: statement(){

    gotoxy(35,19); cout <<R"(

                            Terms of Use and Privacy Statement

                            I hereby declare that the information provided is true and correct. I also understand that any
                            willful dishonesty may render for termination of this bank account.

                            I authorize Put To Bank - Manila to keep this information in my personal file, and the
                            management’s database for the sole purpose of bank transactions.

                            I also understand I am entitled to update and correct the above information and agree that
                            this information could be held for 3 months from the date of enrollment and used for future
                            assessment of the bank.
                             __
                            |__| I certify that I have read and accept the Terms of Use and Privacy Statement and I have
                                read and understand the legal rules and regulations of the bank.

    )";

}

