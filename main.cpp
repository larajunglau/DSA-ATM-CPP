#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>

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
    char pin[7];
    float amount, balance;
    int accNum;
    ALLACC *head, *n;

public:
    void registration();
    void pincode();
    void saveRegistration();
    void encrypt();
    void savePincode();
    void addAccount();
    void makeNull();
    void saveAllAccounts();


};

//int head=NULL;
int main()
{
    ATM atm;
    atm.makeNull();
    atm.registration();
    atm.saveRegistration();
    atm.encrypt();
    atm.savePincode();
    atm.addAccount();
    atm.saveAllAccounts();
}

void ATM:: registration(){
string initialPin;

    //*Lagay statement of agreement
    cout <<"\tREGISTRATION\n";
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
    cout <<"\nAlways keep your account details.";
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

void ATM:: saveAllAccounts(){
fstream allAccFP;
allAccFP.open("allAccounts.txt", ios::out);   //out kapag magpi-print sa file

    allAccFP <<n->accNum <<"\n" <<n->name <<"\n" <<n->balance <<"\n";
    allAccFP.close();
}

void ATM:: addAccount(){    //sine-save yung new account sa linkedlist

    n=head; //set lahat sa head
    n= new ALLACC; //allocates memory to n
    n->name=regInfo.name; n->accNum=accNum; n->balance=balance;
    n->nxt=NULL;

    if(head==NULL){         //
        head=n;
    }

    else{
        n->nxt=head;
        head=n;
    }

}

void ATM:: encrypt(){

int i=0;

    while(pin[i]!='\0'){        //habang di pa NULL
    pin[i]=pin[i] + 123;       //add code each character
    i++;
    }
}

void ATM::makeNull(){
    head==NULL;
}
