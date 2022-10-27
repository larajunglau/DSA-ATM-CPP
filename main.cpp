#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <string.h>

using namespace std;

typedef struct allAcc{
    string name;
    int accNum, balance;
    struct allAcc *nxt;
}ALLACC;

typedef struct regInfo{
    string name, birthday, number;
    int age;
}REGINFO;

class ATM{
private:
    REGINFO regInfo;
    ALLACC *head, *n;
    char pin[7];
    float amount, balance;
    int accNum;
    void saveRegistration();
    void encrypt();
    void savePincode();
    void retrievePincode();
    void addAccount();
    void saveAllAccounts();
    void decrypt();

public:
    void registration();
    void pincode();
    void makeNull();
    void insertCard();
    void removeCard();

};

//int head=NULL;
int main()
{
    ATM atm;
    atm.makeNull();
    atm.insertCard();

}

void ATM:: insertCard(){            //dinede-tect niya kung registered na ang card
fstream pinFP;                      //tsaka sinasabi kay user na mag-insert na ng card
string c, enteredPin;
int ch, tries=0;

    do{system("cls");              //hanggang di pa na-insert card, sasabihin na i-insert na.
        cout <<"Please insert card...\n";
        pinFP.open("pincode.txt", ios::in);
    } while(!pinFP);

    //kapag na-insert na card
    system("cls");

    getline(pinFP, c);     //kukuha ng strring from fp
    if(c.empty()){  //empty()- iche-check kung ang string ay empty. 1- true 0-false
        cout <<"\nYour ATM Card is not yet registered.";
        cout <<"\nDo you want to register?";
        cout <<"\n(1) REGISTER";
        cout <<"\n(2) EXIT";
        cout <<"\nEnter your choice: ";
        cin >> ch;
        if(ch==1){system("cls");    //Kapag walang laman or di pa registered
            registration();
            saveRegistration();
            encrypt();
            savePincode();
            addAccount();
            saveAllAccounts();
        }
        //di pa nagana
        else{removeCard(); exit(0);}
    }

    else{       //kung may laman na or registered na card
        cout <<"Card is registered";
        while(enteredPin!=pin && tries<3){        //hanggang di pa correct pin at di pa blocked
            cout <<"\nEnter pin: ";
            pincode();
            enteredPin=pin;
            retrievePincode();
            decrypt();
            if(enteredPin!=pin){                //kapag mali ang pin
                cout <<"\nIncorrect pin!";
                tries++;                        //madadagdagan ang number of tries
            }
        }

        if(tries==3){       //kapag na-block na
            cout <<"\nYour account was blocked!";
            //balik sa homepage.
        }

        else{              //kapag nakapasok sa menu
            //menu();
            cout <<"\nPIN MATCH";
        }
    }

}

void ATM:: removeCard(){             //hanggang di pa tinatanggal card, sasabihin na tanggalin na.
fstream pinFP;

    //di pa niya nade-detect kung natanggal na
    do{ system("cls");
        cout <<"Please remove card...";
        pinFP.open("pincode.txt",ios::in);
    }while(pinFP);

    pinFP.close();
    cout <<"Thank you for banking with MYLUGI BANK ";
}

void ATM:: registration(){
string initialPin;

    //*Lagay statement of agreement
    cout <<"\tREGISTRATION\n";
    cin.ignore();
    cout <<"\nEnter your full name (EX: JUAN DELA CRUZ): ";
    //*Lagay if hindi Uppercase
    getline(cin, regInfo.name);
    cout <<"\nEnter your Age: ";
    cin >>regInfo.age;
    //*IF BELOW 18
    cout <<"\nEnter your Birthday (EX: MARCH 29, 1999): ";
    //*Lagay if hindi Uppercase
    cin.ignore();
    getline(cin, regInfo.birthday);
    cout <<"\nEnter your Cellphone number: ";
    cin >>regInfo.number;

    initialPin= " ";                    //pang-reset ng value ng initialPin
    while(initialPin!=pin){             //hanggat hindi nag-match, ulit sa ask pincode.
        system("cls");
        cout <<"\nEnter your PIN: ";
        pincode();  //mag-enter ng PIN
        initialPin=pin;                 //sinalin si pin sa initialPin na string.
        cout <<"\nRe-enter PIN :";
        pincode();
        //*LAGAY NG COMMENT KAPAG DI NAG-MATCH
    }

    //*LAGAY CONDITIONS: IF MUTILPLES OF 100
    while(amount < 5000){               //hanggat mas mababa sa 5000
        system("cls");
        cout <<"\nInitial deposit must be at least 5000";
        cout <<"\nEnter amount of initial deposit: ";
        cin >>amount;
    }

    balance= amount;
    srand(time(NULL));
    accNum= rand() %99999999 +10000000;
    system("cls");
    cout <<"\n\tYOUR ACCOUNT DETAILS\n";
    cout <<"\nAccount number: " <<accNum <<"\nName: " <<regInfo.name <<"\nBalnce: " <<balance;
    cout <<"\n\nAccount successfully registered!";
    cout <<"\nAlways keep your account details.\n";
    system("pause");
}

void ATM:: pincode(){       //ginagawa niyang asterisk yung PIN
int index =0;
char ch;

    while((ch=getch())!=13 && index<5){ //habang hindi pa 6 ang digit at hindi pa nag-backspace
        if (index<0){
            index=0;
        }
        if(ch==8){//backspace ascii is 8 //nagbackspace
            putch('\b');    //babalik yung cursor backward
            putch(' ');     //print space
            putch('\b');    //babalik cursor backward
            index--;        //minus digit
            continue;       //break na if statement.
        }
        if(isdigit(ch)){    //kapag nag-enter ng digit
            pin[index++]=ch;
            putchar('*');
        }
    }

    if (index==5){      //kapag 6 digits na.
        pin[index++]=ch;
    }
    pin[index]='\0';    //kapag pag 7th digit na
}

void ATM:: saveRegistration(){
fstream regFP;
regFP.open("registration.txt", ios::out);   //out kapag magpi-print sa file

    regFP <<regInfo.name <<"\n";            //Save registration info sa registration.txt
    regFP <<regInfo.age <<"\n";
    regFP <<regInfo.birthday <<"\n";
    regFP <<regInfo.number <<"\n";
    regFP.close();
}

void ATM:: savePincode(){
fstream pinFP;
pinFP.open("pincode.txt", ios::out);   //out kapag magpi-print sa file

    pinFP <<pin <<"\n";
    pinFP <<accNum;
    pinFP.close();

}

void ATM:: retrievePincode(){
fstream pinFP;
pinFP.open("pincode.txt", ios::in);  //in kapag mag retrieve from file

    while(!pinFP.eof()){
        pinFP >>pin;
        pinFP >>accNum;
    }

pinFP.close();
}

void ATM:: saveAllAccounts(){
fstream allAccFP;
allAccFP.open("allAccounts.txt", ios::out);   //out kapag magpi-print sa file

    allAccFP <<n->accNum <<"\n" <<n->name <<"\n" <<n->balance <<"\n";
    allAccFP.close();
}

void ATM:: addAccount(){    //sine-save yung new account sa linkedlist

    n= new ALLACC; //allocates memory to n
    n->name=regInfo.name; n->accNum=accNum; n->balance=balance; //Lagay info sa n
    n->nxt=head;    //value ng head ay ilagay sa second node
    head=n;         //value ng n ay ilagay sa head

}

void ATM:: encrypt(){

int i=0;

    while(pin[i]!='\0'){        //habang di pa NULL
    pin[i]=pin[i] + 123;       //add code each character
    i++;
    }
}

void ATM:: decrypt(){     //from random symbol, papalabasin pin code para ma-check kung match inenter.
int i=0;

    while(pin[i]!='\0'){            //habang di pa NULL
        pin[i]=pin[i] - 123;       //minus code each character
        i++;
    }
}

void ATM::makeNull(){
    head==NULL;
}
