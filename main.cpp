#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <ctime>       /* time_t, struct tm, time, gmtime */
#define UTC (+8) /define UTC +8 para sa timezone ng ph

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
    ALLACC *head, *n, *p;
    //int index;
    char pin[7];
    string type;
    float amount, balance;
    int accNum, option;
    void saveRegistration();
    void encrypt();
    void savePincode();
    void retrievePincode();
    void addAccount();
    void addRetrieve();
    void saveAllAccounts();
    void saveReceipt();
    void decrypt();
    //void findAccount();

public:
    int accountNumber;
    void retrieveAllAccounts();
    void findAccount();
    void registration();
    void pincode();
    void makeNull();
    void insertCard();
    void removeCard();
    void balInquiry();
    int menu();

};
void Date();
char* dateTime;
//int head=NULL;
int main()
{
    ATM atm;
    atm.makeNull();
    atm.retrieveAllAccounts();
    atm.insertCard();
    atm.findAccount();
    switch(atm.menu()){
        system("cls");
        case 1: system("cls"); atm.balInquiry();break;
        case 8: system("cls"); atm.removeCard(); break;
    }

return 0;
}

void ATM:: insertCard(){            //dinede-tect niya kung registered na ang card
fstream pinFP;                      //tsaka sinasabi kay user na mag-insert na ng card
string c, enteredPin;
int ch, tries=0;

    do{system("cls");              //hanggang di pa na-insert card, sasabihin na i-insert na.
        cout <<"Please insert card...\n";
        pinFP.open("D:pincode.txt", ios::in);
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
            removeCard(); system("pause");

        }
        //di pa nagana
        else{removeCard(); exit(0);}
    }

    else{       //kung may laman na or registered na card
        while(enteredPin!=pin && tries<3){        //hanggang di pa correct pin at di pa blocked
            system("cls");
            cout <<"\nEnter 6-digit pin: ";
            pincode();
            enteredPin=pin;
            retrievePincode();
            decrypt();
            if(enteredPin!=pin){                //kapag mali ang pin
                cout <<"\nIncorrect pin!\n";
                tries++; system("pause");                       //madadagdagan ang number of tries

            }
        }

        if(tries==3){       //kapag na-block na
            cout <<"\nYour account was blocked!";
            removeCard();
            //balik sa homepage.
        }
    }
}

void ATM:: balInquiry(){
    int choice;
    type ="Balance Inquiry";
    cout <<"\tBALANCE INQUIRY";
    cout<< "\n\n(1) Show balance on screen";
    cout<< "\n(2) Print receipt";
    cout<< "\n\nPlease Enter your choice (1-2): ";
    cin>> choice;
        if(choice==1){
                system("cls");
                cout<< "Date: "; Date();
                cout<< "Transcaction Type: " <<type <<"\n" ;
                cout<< "Account Number: " << p->accNum <<"\n" ;
                cout<< "Account Balance: " << p->balance <<"\n";
                system("pause");
        }
        else{
            saveReceipt();
            //bukas receipt.txt
        }
}

void ATM:: saveReceipt(){
fstream receiptFP;
receiptFP.open("D:receipt.txt", ios::out);   //out kapag magpi-print sa file

    if(!receiptFP){
        cout <<"receipt.txt do not exist!\n";;
        system("pause");
    }

    Date();

    receiptFP <<"\tTITLE NG BANK\n";
    receiptFP <<dateTime;
    receiptFP <<"Transaction Type: " <<type <<"\n";
    receiptFP <<"Account Number: " <<p->accNum <<"\n";
    receiptFP <<"Account Balance: " <<p->balance <<"\n";

    if(option==4){
        receiptFP <<"Amount transferred: " <<amount <<"\n";
        receiptFP <<"Recipient: " <<"\n";

    }

    receiptFP <<"\nThank you!";

receiptFP.close();
}


/*void ATM:: removeCard(){             //hanggang di pa tinatanggal card, sasabihin na tanggalin na.
fstream pinFP;
pinFP.open("D:\pincode.txt",ios::in);
    //di pa niya nade-detect kung natanggal na
    do{
        system("cls");
        cout <<"Please remove card...";
    }while(pinFP);

    pinFP.close();
    cout <<"Thank you for banking with MYLUGI BANK ";
    exit(0);
}*/

void ATM:: removeCard(){      //in C   //hanggang di pa tinatanggal card, sasabihin na tanggalin na.
FILE *pinFP;
    do{ system("cls");
        printf("Please remove card...");
        pinFP=fopen("D:\pincode.txt","r");
    } while(pinFP!=NULL);
    fclose(pinFP);
    printf("\nThank you for banking with MYLUGI BANK ");
    exit(0);
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
        cout <<"\nEnter 6-digit PIN: ";
        pincode();  //mag-enter ng PIN
            /*while(index <5){
                cout <<"\nEnter 6-digit PIN: ";
                pincode();
            }*/
        initialPin=pin;                 //sinalin si pin sa initialPin na string.
        cout <<"\nRe-enter 6-digit PIN :";
        pincode();
        //*LAGAY NG COMMENT KAPAG DI NAG-MATCH
    }

    //*LAGAY CONDITIONS: IF MUTILPLES OF 100
    while(amount < 1000){               //hanggat mas mababa sa 5000
        system("cls");
        cout <<"\nInitial deposit must be at least 1000";
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

    if (index <5){
        system("cls");
        cout <<"\nEnter 6-digit pin: ";
        pincode();
    }
}

void ATM:: saveRegistration(){
fstream regFP;
regFP.open("D:registration.txt", ios::out);   //out kapag magpi-print sa file

    if(!regFP){
        cout <<"registration.txt do not exist!\n";;
        system("pause");
    }
    regFP <<regInfo.name <<"\n";            //Save registration info sa registration.txt
    regFP <<regInfo.age <<"\n";
    regFP <<regInfo.birthday <<"\n";
    regFP <<regInfo.number <<"\n";
    regFP.close();
}

void ATM:: savePincode(){
fstream pinFP;
pinFP.open("D:\pincode.txt", ios::out);   //out kapag magpi-print sa file

    pinFP <<pin <<"\n";
    pinFP <<accNum;
    pinFP.close();

}

void ATM:: retrievePincode(){
fstream pinFP;
pinFP.open("D:\pincode.txt", ios::in);  //in kapag mag retrieve from file

    if(!pinFP){
        cout <<"pincode.txt do not exist!\n";;
        system("pause");
    }

    while(!pinFP.eof()){
        pinFP >>pin;
        pinFP >>accNum;
    }

pinFP.close();
}

void ATM:: findAccount(){           //hinahanap yung account info ng current user.

    p=head;

    retrievePincode();
    while(p!=NULL && p->accNum != accNum){
        p=p->nxt;
    }
}

void ATM::saveAllAccounts(){        //pini-print sa text file ang lahat ng accounts
fstream allAccFP;
allAccFP.open("allAccounts.txt", ios::out);

ALLACC *p;

    p=head;
    if(!allAccFP){
        cout <<"allAccounts.txt do not exist!\n";;
        system("pause");
    }
    else{
        while(p!=NULL){                         //hanggat di pa dulo
            allAccFP <<p->accNum <<"\n";
            allAccFP <<p->name <<"\n";
            allAccFP <<p->balance <<"\n\n";
            p=p->nxt;                           //usod sa next account
        }
        cout <<"\nRecords saved successfully.\n";
        system("pause");
    }
    allAccFP.close();
}

void ATM::retrieveAllAccounts(){            //kukunin yung mga accounts mula sa allAccounts.txt at isasalin sa linkedlist
fstream allAccFP;
allAccFP.open("allAccounts.txt", ios::in);

    if(!allAccFP){
        cout<< "File error!\n";
        system("pause");
    }

    else{
        while(1){
            allAccFP >>accNum;
            allAccFP.ignore();                 //flushes the file
            getline(allAccFP, regInfo.name);
            allAccFP >>balance;

            if(!allAccFP.eof()){
                addRetrieve();
            }
            else{break;}
        }
    }
    allAccFP.close();
}

void ATM:: addAccount(){    //sine-save yung new account sa linkedlist

    n= new ALLACC; //allocates memory to n
    n->name=regInfo.name; n->accNum=accNum; n->balance=balance; //Lagay info sa n
    n->nxt=head;    //value ng head ay ilagay sa second node
    head=n;         //value ng n ay ilagay sa head
}

void ATM:: addRetrieve(){   //sine-save yung lahat ng accounts mulsa sa file sa LinkedList
ALLACC *q, *p, *n;

    n= new ALLACC; //allocates memory to n
    n->name=regInfo.name; n->accNum=accNum; n->balance=balance;
    p=q=head; //set lahat sa head
    while(p!=NULL){
        q=p;
        p=p->nxt;
    }
    cout <<"while";

    if(p==head){ //If wala pang laman
        head=n;
    }
    else{q->nxt=n;} //if may laman na

    n->nxt=p; //lagay NULL sa dulo which is p.

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
    head=NULL;
}

int ATM:: menu(){

    system("cls");
    cout <<"\t\tMENU\n";
    cout <<"1. Balance Inquiry\n";
    cout <<"2. Withdrawal\n";
    cout <<"3. Deposit\n";
    cout <<"4. Fund Transfer\n";
    cout <<"5. Change Pincode\n";
    cout <<"6. Transfer history\n";
    cout <<"7. Other Transactions\n";
    cout <<"8. Exit\n";
    cout <<"Enter option (1-8): ";
    cin >> option;
    return option;
}

void Date() // 24 hr format
{
time_t ttime = time(0); // currrent time
dateTime = ctime(&ttime); //ctime gagawin niya yung dateTime na string in weekday month date hours:minutes:seconds year.

tm *gmt_time = gmtime(&ttime); //Returns pointer to the tm structure in the Coordinated Universal Time (UTC) format which is essentially Greenwich Mean Time (GMT).
//define na yung utc +8 para time zone ng philippines
cout << dateTime << endl; //print dateTime
dateTime = asctime(gmt_time); //print yung current time ng Philippines
}
