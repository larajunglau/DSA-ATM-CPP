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
#include <algorithm>
#include "design.h"
#define RED "\033[31m"
#define WHITE"\033[37m"
#define WHTBG "\033[107m"
#define RESET"\033[0m"

/*                          PUT TO BANK - Manila ATM Machine

        -The name of the bank is inspired from the AKAs of the TUPians which is 'PUTO'.
        -This ATM offers different transactions namely:
                1. Balance Inquiry
                2. Withdrawal
                3. Cash deposit
                4. Fund transfer
                5. Other transactions:
                        1. Transaction History
                        2. Change PIN

        -Language: C++
        -Data structure: Linked List
        -Text Files: allAccounts.txt (System), registration.txt (USB), receipt.txt(USB), history.txt(USB)


        Created by:
            Alcantara, John Paulo C.
            Ygot, Laica D.

        Year and Section: BSCS-NS-2AB
        Instructor: Sir. Renegado, Fernando L.
*/

using namespace std;

//Linked list for all accounts that will be stored in the allAccounts.txt
typedef struct allAcc{
    string name, accNum;
    int chR;
    float balance;
    struct allAcc *nxt;
}ALLACC;

//Linked list for transaction history that will be stored in history.txt
typedef struct history{
    string dateTime;
    string type, accNum, recipient;
    int amount;
    float balance;
    struct history *nxt;
}HISTORY;

//A struct to store the registration info of the user that will be stored in the registration.txt
typedef struct regInfo{
    string name, birthday, number;
    int age;
}REGINFO;

class ATM{
private:
    REGINFO regInfo;
    ALLACC *head, *n, *p, *r;
    HISTORY *headH;
    //int index;
    char pin[7];
    string type, accNum, recipient;
    float amount, balance;
    int option;
    void saveRegistration();
    void encrypt();
    void savePincode();
    void retrievePincode();
    void addAccount();
    void addHistory();
    void addRetrievedHistory();
    void addRetrieve();
    void saveAllAccounts();
    void saveHistory();
    void saveReceipt();
    void decrypt();
    void findRecipient();
    void askToExit();
    void askReceipt();

public:
    void retrieveAllAccounts();
    void retrieveHistory();
    void findAccount();
    void registration();
    void pincode();
    void makeNull();
    void insertCard();
    void removeCard();
    void withdrawal();
    void balInquiry();
    void deposit();
    void fundTransfer();
    void changePin();
    void displayHistory();
    void askPin();
    int menu();
};

//A class to put commas on amounts
class comma_numpunct : public std::numpunct<char>
{
  protected:
    virtual char do_thousands_sep() const
    {return ',';}

    virtual std::string do_grouping() const
    {return "\03";}
};

//GLOBAL VARIABLES AND PROTOTYPES
void setFontStyle(int FontSize);
void gotoxy(int x,int y);
HWND WINAPI GetConsoleWindowNT(void);
design design;
HANDLE m= GetStdHandle(STD_OUTPUT_HANDLE);

void putComma();
void Date();
string dt;
int chR;
char dateTime[100];
int main()
{
int choice;

    HWND hWnd=GetConsoleWindowNT();
    MoveWindow(hWnd,900,900,1200,900,TRUE);
    setFontStyle(13);

    ATM atm;                                        //creates an object for design class
    atm.makeNull();
    atm.retrieveAllAccounts();
    putComma();                                     //adds comma and decimal to money displays
    atm.insertCard();
    atm.findAccount();
    atm.retrieveHistory();
    while(1){
        switch(atm.menu()){
            system("cls");
            case 1:
                system("cls");
                atm.askPin();
                atm.balInquiry(); break;
            case 2:
                system("cls");
                atm.withdrawal(); exit(0); break;
            case 3:
                system("cls");
                atm.askPin(); system("cls");
                design.secondBorder(); design.deposit();design.menuScreen();
                atm.deposit(); break;
            case 4:
                system("cls");
                atm.askPin(); system("cls");
                design.secondBorder(); design.fundTransfer();design.menuScreen();
                atm.fundTransfer(); break;
            case 5: system("cls");
                design.secondBorder(); design.otherTransac();design.otherScreen();
                design.boxes();
                gotoxy(29,32);cout <<RED"(1) Transaction History";
                gotoxy(94,32);cout <<RED"(2) Change PIN";
                gotoxy(62,36);cout <<RED"Enter choice: ";
                cin >>choice;
                system(RESET);
                switch(choice){;
                    case 1:
                        system("cls");
                        atm.askPin(); system("cls");
                        atm.displayHistory(); break;
                    case 2:
                        system("cls");
                        atm.changePin(); break;
                    default: gotoxy(51,44);cout <<"Invalid Transaction: Enter only numbers from 1-2\n"; gotoxy(60,45);system("pause");
                }

                break;


            case 6: system("cls"); atm.removeCard(); exit(0); break;
            default: gotoxy (50, 46); cout <<RED <<"Invalid Transaction: Enter only numbers from 1-6\n" <<WHITE; gotoxy (50, 47);system("pause");
        }
    }
return 0;
}

//Detects the pincode.txt in the USB and scan if it's empty or registered.
//asks the user if they want to register
void ATM:: insertCard(){                                //dinede-tect niya kung registered na ang card
fstream pinFP;                                          //tsaka sinasabi kay user na mag-insert na ng card
string c;
int ch;

    design.secondBorder();
    design.homeTitle();
    design.usb();

    gotoxy(65,40); cout <<"Please insert card...";
    do{                                                 //hanggang di pa na-insert card, sasabihin na i-insert na.
        pinFP.open("D:pincode.txt", ios::in);
    } while(!pinFP);

    design.loadingBar();
    getline(pinFP, c);                                  //kukuha ng strring from fp
    if(c.empty()){                                      //empty()- iche-check kung ang string ay empty. 1- true 0-false
        system("cls");
        design.secondBorder();
        design.homeTitle();
        design.otherScreen();

        gotoxy(55,28);cout <<WHITE"Your ATM Card is not yet registered.";
        gotoxy(55,30);cout <<WHITE"      Do you want to register?      ";
        design.boxes();

        gotoxy(33,32);cout <<RED"(1) REGISTER";
        gotoxy(97,32);cout <<RED"(2) EXIT";
        gotoxy(59,36);cout <<RED"Enter your choice: ";
        cin >> ch;
        if(ch==1){gotoxy(39,41);system(RESET"pause");      //Kapag walang laman or di pa registered
            registration();
            saveRegistration();
            encrypt();
            savePincode();
            addAccount();
            saveAllAccounts();
            system("cls"); removeCard(); exit(0);

        }
        else if(ch==2){gotoxy(39,41);system(RESET"pause");removeCard(); exit(0);}
        else{
                gotoxy(50,42); cout<<RESET<<RED"Invalid Transaction: Enter only numbers from 1-2\n" <<WHITE;
                gotoxy(50,43); system("cls"); exit(0);
        }
    }
    else{                                        //kung may laman na or registered na card
        retrievePincode();                       //para before tawagin si findAccount, refreshed ang accNum.
    }
}

//Shows the user's current balance on screen
void ATM:: balInquiry(){
int choice;

    system("cls"); design.secondBorder(); design.homeTitle(); design.eagle(); design.loadingBar();
    system("cls"); design.secondBorder(); design.menuScreen(); design.balInquiry();
    type ="Balance Inquiry";
    gotoxy(33,32); cout<< "(1) Show balance on screen";

    gotoxy(97,32);cout<< "(2) Print receipt";
    gotoxy(59,36);cout<< "Please Enter your choice (1-2): ";
    cin>> choice;
        if(choice==1){
            system("cls"); design.secondBorder(); design.menuScreen(); design.balInquiry();
            gotoxy(50,24); cout <<"Date: "; Date(); cout <<dt;
            gotoxy(50,28); cout <<"Account Number: " << p->accNum;
            gotoxy(50,30); cout <<"Account Balance: "<< p->balance;
        }
        else if(choice==2){
            gotoxy(60, 43);saveReceipt();

        }
        else{gotoxy(50,43); cout <<RED <<"Invalid Transaction: Enter only numbers from 1-2" <<WHITE;}
        gotoxy(60,45); system("pause");

        askToExit();
}

//Asks the user of the amount to withdraw and deduct it from the user's current balance
//Amount should be multiples of 100, should be less than their balance, and must not exceed 20,000
void ATM:: withdrawal(){
int temp, ch, i;

    system("cls"); design.secondBorder(); design.homeTitle(); design.eagle(); design.loadingBar();
    type= "Withdrawal";
    while(temp %100!=0 || amount > (p->balance-500) || amount > 20000){
        system("cls"); design.secondBorder(); design.menuScreen(); design.withdrawal();

        gotoxy(40, 24); cout <<"This machine can only dispense 100, 200, 500, and 1000 bills";
        gotoxy(60, 28); cout <<"Enter amount: ";
        cin >> amount;
        temp=(int) amount;          //store sa int varabiale ang amount para magamit modulo.

        if(temp %100!=0){
            gotoxy(45,35); cout <<RED <<"This machine can only dispense 100, 500, and 1000 bills!" <<WHITE;
            gotoxy(60,45); system("pause");}
        else if(amount > (p->balance-500)){
            gotoxy(60,35); cout <<RED <<"Insufficient balance!\n" <<WHITE;
            gotoxy(60,45); system("pause");}
        else if(amount > 20000){
            gotoxy(60,35); cout <<RED <<"Amount must not exceed P20,000" <<WHITE;
            gotoxy(60,45);system("pause");}
    }
    system("cls"); askPin(); system("cls");

    p->balance-= amount;                                //ima-iminus yung amount sa balance
    recipient="N/A";

    system("cls"); design.secondBorder(); design.homeTitle(); design.eagle(); design.loadingBar();    //for all loadings
    askReceipt();

    removeCard();                                       //take ATM
    gotoxy(60,38); cout <<"Please take your cash.";     //take cash

    Date();
    if(chR==1){gotoxy(60,40); saveReceipt();}           //take receipt
    saveAllAccounts();
    addHistory();
    saveHistory();
}

//Asks the user to enter amount to deposit and adds it their current balance
//Amount must be multiples of 100, and must not exceed 50,000
void ATM:: deposit(){
int temp, ch, i;
float thou, fivehun, twohun, onehun;

    system("cls"); design.secondBorder(); design.homeTitle(); design.eagle(); design.loadingBar();
    type= "Deposit";

    system("cls");
    system("cls"); design.secondBorder(); design.deposit();design.menuScreen();

    gotoxy(45,22);cout <<"NOTE: This machine can only accept 100, 200, 500, and 1000 bills";
    gotoxy(47,26);cout <<"Enter number of pieces of your P1,000 bills: ";
    cin >>thou;
    gotoxy(47,28);cout <<"Enter number of pieces of your P500 bills: ";
    cin >>fivehun;
     gotoxy(47,30);cout <<"Enter number of pieces of your P200 bills: ";
    cin >>twohun;
     gotoxy(47,32);cout <<"Enter number of pieces of your P100 bills: ";
    cin >>onehun;
    amount=( (1000*thou)+(500*fivehun)+(200*twohun)+(100*onehun));

    do{
        system("cls");
        design.secondBorder(); design.deposit();design.menuScreen();
        gotoxy(63,23);cout <<"AMOUNT DENOMINATION\n";
        gotoxy(63,26);cout <<"1,000 x " <<std::setprecision(0) << std::fixed <<thou <<" = " <<std::setprecision(2) << std::fixed <<1000*thou;
        gotoxy(63,28);cout <<"500 x " <<std::setprecision(0) << std::fixed<<fivehun <<" = " <<std::setprecision(2) << std::fixed<<500*fivehun;
        gotoxy(63,30);cout <<"200 x " <<std::setprecision(0) << std::fixed<<twohun <<" = " <<std::setprecision(2) << std::fixed<<200*twohun;
        gotoxy(63,32);cout <<"100 x " <<std::setprecision(0) << std::fixed<<onehun <<" = " <<std::setprecision(2) << std::fixed<<100*onehun;
        gotoxy(53,34);cout <<"______________________________________";
        gotoxy(60,36);cout <<"TOTAL AMOUNT: " <<amount;
        gotoxy(60,45); system("pause");

        if(amount > 50000){
            gotoxy(60,40);cout <<"Deposit amounts larger than P50,000 must be proccessed over the counter";
            gotoxy(60,45);system("pause");
            deposit();}

        system("cls"); design.secondBorder(); design.deposit();design.otherScreen();
        design.boxes();
        gotoxy(33,32);cout <<RED"(1) CONFIRM";
        gotoxy(97,32);cout <<RED"(2) BACK";
        gotoxy(59,36);cout <<RED"Enter your choice: ";
        cin >>ch;
        gotoxy(60,45); system("pause"RESET);
        if(ch!=1 && ch!=2){
                gotoxy(51,43);cout <<"Invalid Transaction: Enter only a number from 1-2";gotoxy(60,45); system("pause");}
    }while(ch!=1 && ch!=2);

    if(ch==2){system("cls"); deposit();}
    else{
        system("cls");
        design.secondBorder(); design.deposit();design.menuScreen();
        gotoxy(45,27);cout <<"Amount of " << amount <<" will be deposited to your account." <<endl;gotoxy(60,45);system("pause");
        p->balance+= amount;                                               //ipa-plus yung amount sa balance
        recipient="N/A";
        askReceipt();

        system("cls"); design.secondBorder(); design.homeTitle(); design.eagle(); design.loadingBar();         //for all loadings

        system("cls");
        design.secondBorder(); design.deposit();design.menuScreen();
        gotoxy(60,28);cout <<"Cash deposited successfully.";
        gotoxy(57,30);cout <<"Please check your account balance.\n";  gotoxy(60,45);system("pause"); //take cash

        Date();
        if(chR==1){gotoxy(50,32); saveReceipt();}                          //take receipt
        saveAllAccounts();
        addHistory();
        saveHistory();
        askToExit();
    }
}

//Asks the user to enter the amount to transfer and the recipient.
//Deducts the amount to their current balance and adds it to the recipient's balance.
void ATM:: fundTransfer(){
int temp, ch, i;

    type= "Fund Transfer";
    do{

        gotoxy(55,27);cout<<"Enter recipient's Account number: ";
        cin >> accNum;
        findRecipient();
        if(r==NULL){
            gotoxy(58,29);cout <<RED"Account number does not exist."<<WHITE;
            gotoxy(60,45);system("pause");system("cls");
            design.secondBorder(); design.fundTransfer();design.menuScreen();
            fundTransfer();}
    }while(r==NULL);

    while(temp %100!=0 || amount > (p->balance-500)){
        system("cls");
        design.secondBorder(); design.fundTransfer();design.menuScreen();
        gotoxy(55,27);cout<<"Enter recipient's Account number: " <<accNum;
        gotoxy(55,29);cout <<"Enter amount: ";
        cin >> amount;
        temp=(int) amount;                                  //store sa int varabiale ang amount para magamit modulo.

        if(temp %100!=0){
             gotoxy(45,27);cout <<"This machine can only transfer 100, 500, and 1000 bills";
             gotoxy(60,45);system("pause");}
        else if(amount > (p->balance-500)){
            gotoxy(51,43);cout <<RED <<"Invalid Transaction: Insufficient balance!" <<WHITE;
             gotoxy(60,45);system("pause");}
    }

    do{
        system("cls");
        design.secondBorder(); design.fundTransfer();design.menuScreen();
        gotoxy(56,25);cout <<"Your account number: " <<p->accNum <<"\n";
        gotoxy(56,27);cout <<"Recipient's account number: " <<r->accNum <<"\n";
        gotoxy(56,29);cout <<"Recipient's name: " <<r->name <<"\n";
        gotoxy(56,31);cout <<"Amount to transfer: "; putComma(); cout <<amount <<"\n";
        gotoxy(60,45);system("pause");

        system("cls");
        design.secondBorder(); design.fundTransfer();design.otherScreen();
        design.boxes();
        gotoxy(33,32);cout <<RED"(1) CONFIRM";
        gotoxy(97,32);cout <<RED"(2) BACK";
        gotoxy(59,36);cout <<RED"Enter your choice: ";
        cin >>ch;
        gotoxy(60,45);system("pause"RESET);
        if(ch!=1 && ch!=2){ gotoxy(51,43); cout <<RED <<"\nInvalid Transaction: Enter only a number from 1-2" <<WHITE; gotoxy(60,45);system("pause");}
    }while(ch!=1 && ch!=2);

    if(ch==1){
        system("cls");
        p->balance-= amount;                            //ima-iminus yung amount sa balance ni sender
        r->balance+= amount;                            //ia-add yung amount sa balance ni recipient
        askReceipt();

        system("cls"); design.secondBorder(); design.homeTitle(); design.eagle(); design.loadingBar();         //for all loadings

        system("cls");
        design.secondBorder(); design.deposit();design.menuScreen();
        gotoxy(50,28);cout <<"Funds transferred successfully.";
        gotoxy(50,30);cout <<"Please check your account balance.";

        Date();
        if(chR==1){gotoxy(50,32); saveReceipt();}                      //take receipt
        saveAllAccounts();
        recipient=r->name;
        addHistory();
        saveHistory();
        askToExit();
    }

    else{return;}

}

//Asks the user to enter their current pin and their new PIN
//Replaces the old PIN to new PIN and and saves it in the pincode.txt
void ATM:: changePin(){
string pinEntered,newPin,reEnterPin;
int tries=0;

    system("cls"); design.secondBorder(); design.homeTitle(); design.eagle(); design.loadingBar();
    design.secondBorder(); design.changePin();design.menuScreen();

    while(pinEntered!=pin && tries<3){                          //hanggat di equal ang pinentered sa pin di pa less than 3 tries
            system("cls");
            design.secondBorder(); design.changePin();design.menuScreen();
            gotoxy(53,27);cout<<RED"ENTER CURRENT PIN CODE TO CHANGE PINCODE";
            gotoxy(58,29);cout<<WHITE"Enter your current PIN: ";
            pincode();
            pinEntered=pin;
            retrievePincode();
            decrypt();
            if(pinEntered!=pin){
                 gotoxy(65,31);cout<<RED"Incorrect PIN!" <<WHITE;
                 tries++;
                 gotoxy(60,45);system("pause");                 //madadagdagan ang number of tries
            }
            if(tries==3){                                       //kapag na-block na
            system("cls");
            design.secondBorder(); design.changePin();design.menuScreen();
            gotoxy(60,27);cout <<"Your account was blocked!";
            gotoxy(60,45);system("pause");
             removeCard();exit(0);
                                                                //balik sa homepage.
            }
    }
    do{
        system("cls");
        design.secondBorder(); design.changePin();design.menuScreen();                                 //gagawin ito hanggat hindi equal yung newPin at reEnterPin
        gotoxy(53,27);cout<<"Enter your new 6-digit PIN: ";         // enter new pin
        pincode();
        newPin=pin;                                                 //inistore yung pin sa variable newPin

        gotoxy(53,29);cout<<"Re-enter new 6-digit PIN: ";           //re- enter pin
        pincode();
        reEnterPin=pin;                                             //inistore yung pin sa variable reEnterPin
    }while(newPin!=reEnterPin);

    if(pin==newPin){
    encrypt();
    savePincode();
    gotoxy(50,32);cout<<WHITE "Pin code has been successfully changed.\n";
    gotoxy(60,45);system("pause");
    askToExit();
    }
}

//Displays all the transaction of the user
//with its date, transaction type, account number, amount, recipient (if any), and balance
void ATM::displayHistory(){
HISTORY *p;
int i=0, ctr, ch;

    system("cls"); design.secondBorder(); design.homeTitle(); design.eagle(); design.loadingBar();         //for all loadings
    system("cls"); design.secondBorder(); design.history();
    gotoxy(14,22);cout<<" _________________________________ _________________ ___________________ ___________ ______________________________________ ";
    gotoxy(14,23);cout<<"|             DATE                |       TYPE      |   ACCOUNT NUMBER  |   AMOUNT  |       RECIPIENT       |   BALANCE    |";
    gotoxy(14,24);cout<<"|_________________________________|_________________|___________________|___________|_______________________|______________|";
    p=headH;
    while(p!=NULL){
        gotoxy(15,26+i);cout <<p->dateTime;
        gotoxy(50,26+i);cout<<p->type;
        gotoxy(72,26+i);cout<<p->accNum;
        gotoxy(90,26+i);cout<<p->amount;
        gotoxy(102,26+i);cout<<p->recipient;
        gotoxy(125,26+i);cout<<p->balance;
        i+=2; ctr++;
        p=p->nxt;

        if((ctr%9)==0){
            gotoxy(50, 47); cout <<"Enter (1) to continue (2) to go back to menu: ";
            cin >>ch;
            if(ch!=1){return;}

            system("cls"); design.secondBorder(); design.history();
            i=0;
            gotoxy(14,22);cout<<" _________________________________ _________________ ___________________ ___________ ______________________________________ ";
            gotoxy(14,23);cout<<"|             DATE                |       TYPE      |   ACCOUNT NUMBER  |   AMOUNT  |       RECIPIENT       |   BALANCE    |";
            gotoxy(14,24);cout<<"|_________________________________|_________________|___________________|___________|_______________________|______________|";
        }


    }
    gotoxy(60,45);system("pause");
}

//Asks the user if they want to get receipt of their most recent transaction.
void ATM:: askReceipt(){
    do{
        system("cls");
        design.secondBorder();design.homeTitle();design.otherScreen();
         gotoxy(55,28);cout <<"Do you want a printed receipt?";
        design.boxes();
        gotoxy(33,32);cout <<RED"(1) YES";
        gotoxy(97,32);cout <<RED"(2) NO";
        gotoxy(59,36);cout <<RED"Enter your choice: ";
        cin >> chR;
        gotoxy(60,45); system("pause"RESET);
        if(chR!=1 && chR!=2){
                gotoxy(51,43);cout<<"Invalid Transaction: Enter only a number from 1-2"; gotoxy(60,45);system("pause");}
       }while(chR!=1 && chR!=2);
}

//Asks the user if they want to do another transaction or proceed to exit.
void ATM:: askToExit(){
int ch;
    do{
        system("cls");
        design.secondBorder();design.homeTitle();design.otherScreen();
        gotoxy(55,28);cout <<"Do you want to do another transaction?";
        design.boxes();
        gotoxy(33,32);cout <<RED"(1) YES";
        gotoxy(97,32);cout <<RED"(2) EXIT";
        gotoxy(59,36);cout <<RED"Enter your choice: ";
        cin >> ch;
        gotoxy(60,45); system("pause"RESET);
        if(ch!=1 && ch!=2){cout<<"Invalid Transaction: Enter only a number from 1-2";gotoxy(60,45);system("pause");}
    }while(ch!=1 && ch!=2);

    if(ch==1){return;}
    else if(ch==2){removeCard(); exit(0);}
}

//Prints the most recent transaction info of the user in the receipt.txt
void ATM:: saveReceipt(){
fstream receiptFP;
receiptFP.open("D:receipt.txt", ios::out);   //out kapag magpi-print sa file
char accNum[8];

    if(!receiptFP){
        gotoxy(60,40); cout <<"receipt.txt do not exist!\n";;
        system("pause");
    }

    receiptFP <<R"(
 __| |________________________________________________| |__
(__   ________________________________________________   __)
   | |                                                | |
                    PUT TO BANK - Manila
                The  Bank  of  the  Greyhawks
     Ayala Blvd.,San Marcelino St., Ermita, Manila 1000
    ====================================================
    )";

    receiptFP <<"\n\t" <<dt <<"\n";
    receiptFP <<"\n\tTransaction Type:\t\t" <<type;
    receiptFP <<"\n\tAccount Number:\t\t\t" <<p->accNum;

    if(option==2 ||option==3 ||option==4 ){
        receiptFP <<"\n\tAmount:\t\t\t\t" <<std::setprecision(2) << std::fixed <<amount <<"\n";
    }
    if(option==4){
        receiptFP <<"\tRecipient's account number:\t" <<r->accNum <<"\n";
    }

    receiptFP <<"\n\tAccount Balance:\t\t" ;
    receiptFP <<std::setprecision(2) << std::fixed <<p->balance <<"\n";


    receiptFP <<R"(
    ====================================================
      Thank you for banking with PUT TO BANK - Manila!
         Visit Us Online: www.puttobank.com or Call
          our Customer Service Line: 111-2445-345
                    Padayon mga PUTO!
 __| |________________________________________________| |__
(__   ________________________________________________   __)
   | |                                                | |
    )";
    gotoxy(60,47); cout <<"Check your receipt in receipt.txt.\n";
    gotoxy(60,45); system("pause");

receiptFP.close();
}

//Asks the user to remove their ATM Card until it removed.
void ATM:: removeCard(){                    //in C   //hanggang di pa tinatanggal card, sasabihin na tanggalin na.
FILE *pinFP;
     system("cls");
     design.secondBorder();design.homeTitle();design.usb();
     gotoxy(67,36);cout<<RED"Please remove card...";
    do{
        pinFP=fopen("D:\pincode.txt","r");
    } while(pinFP!=NULL);

    design.loadingBar();
    fclose(pinFP);
    gotoxy(63,40);cout <<"Thank you for banking with us!";
    gotoxy(60,45);system("pause");
    gotoxy(60,47);
}

//Asks the personal information of the user and saves it in the registration.txt in the USB
//Does not allow below 18 years old users
//Asks the 6-digit PIN twice and the initial deposit that must be atleast 1000
//Displays the registration details of the user to confirm.
void ATM:: registration(){
string initialPin;
int intAccNum;
char ch;

    system("cls");
    design.secondBorder();
    design.menuScreen();
    design.registration();

    cin.ignore();//gotoxy(57,22);
    gotoxy(47,23);cout <<"Enter your full name (EX: JUAN DELA CRUZ): ";
    getline(cin, regInfo.name);

    do{
        gotoxy(47,26);cout <<"Enter your Age: ";
        cin >>regInfo.age;
        if(regInfo.age<18){
            gotoxy(40,32); cout <<RED <<"Regular account users must be 18 years old and above.";
            gotoxy(40,33); cout <<WHITE "Enrollment for custodial or joint bank account must be processed in the main office.\n\n";
            gotoxy(60, 45);system("pause"); removeCard(); exit(0);
        }
    }while(regInfo.age<18);

    gotoxy(47,29);cout <<"Enter your Birthday (EX: MARCH 29, 1999): ";
    cin.ignore();
    getline(cin, regInfo.birthday);
    gotoxy(47,32);cout <<"Enter your Cellphone number: ";
    cin >>regInfo.number;

    initialPin= " ";                                        //pang-reset ng value ng initialPin
    while(initialPin!=pin){                                 //hanggat hindi nag-match, ulit sa ask pincode.
        system("cls");
        design.secondBorder(); design.menuScreen(); design.registration();
        gotoxy(53,27);cout <<WHITE"Enter 6-digit PIN: ";
        pincode();                                          //mag-enter ng PIN
        initialPin=pin;                                     //sinalin si pin sa initialPin na string.
        gotoxy(53,29);cout <<WHITE"Re-enter 6-digit PIN: ";
        pincode();
        if(initialPin!=pin){
            gotoxy(53,32);cout <<RED <<"PIN do not match!" WHITE; gotoxy(60,45);system("pause");
        }
    }

    while(amount < 1000){
        system("cls");
        design.secondBorder(); design.menuScreen(); design.registration();
        gotoxy(53,27);cout <<RED"NOTE: Initial deposit must be at least 1000";
        gotoxy(53,29);cout <<WHITE"Enter amount of initial deposit: ";
        cin >>amount;
    }

    system("cls"); design.secondBorder(); design.menuScreen(); design.registration();
    design.statement();
    gotoxy(50, 43); cout <<"Enter 'Y' to continue, otherwise press any key. ";
    gotoxy(30,33); cin >>ch;
    if(ch!='Y' && ch!='y'){removeCard(); exit(0);}

    balance= amount;
    srand(time(NULL));
    intAccNum= rand() %99999999 +10000000;
    accNum= to_string(intAccNum);
    system("cls");
    design.secondBorder(); design.homeTitle(); design.eagle(); design.loadingBar();         //for all loadings

    system("cls"); design.secondBorder(); design.homeTitle(); design.otherScreen(); design.accDetails();

    gotoxy(64,33);cout <<"Account number: " <<WHITE<<accNum;
    gotoxy(64,34);cout <<"Name: " <<WHITE<<regInfo.name;
    gotoxy(64,35);cout <<"Balance: " <<WHITE<<balance;
    gotoxy(40,38);cout <<"Account successfully registered! " <<"Always keep your account details.";
    gotoxy(60,45);system("pause");

}

//Scans each digit of the PIN of the user and displays asterisk after each input.
//Scans if backspaces is entered, and moves the cursor backwards.
void ATM:: pincode(){                                           //ginagawa niyang asterisk yung PIN
int index =0;
char ch;

    while((ch=getch())!=13 && index<5){                         //habang hindi pa 6 ang digit at hindi pa nag-backspace
        if (index<0){
            index=0;
        }
        if(ch==8){                                              //backspace ascii is 8 //nagbackspace
            putch('\b');                                        //babalik yung cursor backward
            putch(' ');                                         //print space
            putch('\b');                                        //babalik cursor backward
            index--;                                            //minus digit
            continue;                                           //break na if statement.
        }
        if(isdigit(ch)){                                        //kapag nag-enter ng digit
            pin[index++]=ch;
            putchar('*');
        }
    }

    if (index==5){                                              //kapag 6 digits na.
        pin[index++]=ch;
    }
    pin[index]='\0';                                            //kapag pag 7th digit na

    if (index <5){
        system("cls");
        design.secondBorder(); design.otherScreen(); design.homeTitle();
        gotoxy(60,32);cout <<"Enter 6-digit pin: ";
        pincode();
    }
}

//Saves the registration info of the user to the registration.txt
void ATM:: saveRegistration(){
fstream regFP;
regFP.open("D:registration.txt", ios::out);                       //out kapag magpi-print sa file

    if(!regFP){
        cout <<"registration.txt do not exist!\n";;
        system("pause");
    }
    regFP <<regInfo.name <<"\n";                                //Save registration info sa registration.txt
    regFP <<regInfo.age <<"\n";
    regFP <<regInfo.birthday <<"\n";
    regFP <<regInfo.number <<"\n";
    regFP.close();
}

//Saves the pincode and the account number of the user for easy access.
void ATM:: savePincode(){
fstream pinFP;
pinFP.open("D:pincode.txt", ios::out);

    pinFP <<pin <<"\n";
    pinFP <<accNum;
    pinFP.close();
}

//Retrieves the pincode and account number from the pincode.txt to use for the transacions to be made.
void ATM:: retrievePincode(){
fstream pinFP;
pinFP.open("D:pincode.txt", ios::in);

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

//Scans the All acocunts linked list and finds the node of the current user using its account number
void ATM:: findAccount(){

    p=head;

    while(p!=NULL && p->accNum != accNum){
        p=p->nxt;
    }
}

//Scans the All acocunts linked list and finds the node of the recipient using its account number
void ATM:: findRecipient(){

    r=head;

    while(r!=NULL && r->accNum != accNum){
        r=r->nxt;
    }
}

//Saves the all accounts linked list in the allAccounts.txt
void ATM::saveAllAccounts(){
fstream allAccFP;
allAccFP.open("allAccounts.txt", ios::out);

ALLACC *p;

    p=head;
    if(!allAccFP){
        cout <<"allAccounts.txt do not exist!\n";;
        system("pause");
    }
    else{
        while(p!=NULL){                                         //hanggat di pa dulo
            allAccFP <<p->accNum <<"\n";
            allAccFP <<p->name <<"\n";
            allAccFP <<p->balance <<"\n\n";
            p=p->nxt;                                           //usod sa next account
        }
    }
    allAccFP.close();
}

//Retrieves all accounts linked list from allAccounts.txt
//by storing each data in a variable and add it in the linked list
void ATM::retrieveAllAccounts(){
fstream allAccFP;
allAccFP.open("allAccounts.txt", ios::in);

    if(!allAccFP){
        cout<< "File error!\n";
        system("pause");
    }

    else{
        while(1){
            allAccFP >>accNum;
            allAccFP.ignore();                                  //flushes the file
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

//Adds the newly registered account to the head of the all accounts linkedlist
void ATM:: addAccount(){                                        //sine-save yung new account sa linkedlist

    n= new ALLACC;                                              //allocates memory to n
    n->name=regInfo.name; n->accNum=accNum; n->balance=balance; //Lagay info sa n
    n->nxt=head;                                                //value ng head ay ilagay sa second node
    head=n;                                                     //value ng n ay ilagay sa head
}

//Adds the currently retrieved account at the end of the all accounts linked list
//To keep the list in chronological order (based from the time they registered)
void ATM:: addRetrieve(){                                       //sine-save yung lahat ng accounts mulsa sa file sa LinkedList
ALLACC *q, *p, *n;

    n= new ALLACC;
    n->name=regInfo.name; n->accNum=accNum; n->balance=balance;
    p=q=head;
    while(p!=NULL){
        q=p;
        p=p->nxt;
    }

    if(p==head){
        head=n;
    }
    else{q->nxt=n;}

    n->nxt=p;
}

//Adds the most recent transaction history at the head of the transaction history linked list
void ATM:: addHistory(){
HISTORY *n;

    n= new HISTORY;
    n->dateTime= dt;
    n->type=type; n->accNum=p->accNum; n->amount=amount;
    n->recipient=recipient; n->balance=p->balance;
    n->nxt=headH;
    headH=n;

}

//Adds the currently retrieved transaction history at the end of the transaction history linked list
//To keep the list in chronological order (based from the transaction time and date)
void ATM:: addRetrievedHistory(){                                   //sine-save yung lahat ng accounts mulsa sa file sa LinkedList
HISTORY *q, *p, *n;

    n= new HISTORY;
    n->dateTime=dt; n->type=type; n->accNum=accNum; n->amount= amount;
    n->recipient= recipient; n->balance=balance;

    p=q=headH;
    while(p!=NULL){
        q=p;
        p=p->nxt;
    }

    if(p==headH){
        headH=n;
    }
    else{q->nxt=n;}

    n->nxt=p;

}

//Saves all transaction history of the current user in the history.txt in the USB
void ATM::saveHistory(){
fstream historyFP;
historyFP.open("D:history.txt", ios::out);

HISTORY *p;

    p=headH;
    if(!historyFP){
        cout <<"history.txt do not exist!\n";;
        system("pause");
    }
    else{
        while(p!=NULL){
            historyFP <<p->dateTime <<"\n" <<p->type <<"\n" <<p->accNum <<"\n";
            historyFP <<p->amount <<"\n" <<p->recipient <<"\n" <<p->balance <<"\n" <<endl;
            p=p->nxt;
        }
    }
    historyFP.close();
}

//Retrieves transaction history linked list from history.txt
//by storing each data in a variable and add it in the linked list
void ATM::retrieveHistory(){
fstream historyFP;
historyFP.open("D:history.txt", ios::in);

    if(!historyFP){
        cout<< "File error!\n";
        system("pause");
    }

    else{
        while(1){
            getline(historyFP, dt);
            getline(historyFP, type);
            historyFP >>accNum;
            historyFP >>amount;
            historyFP.ignore();
            getline(historyFP, recipient);

            historyFP >>balance;

            historyFP.ignore();
            if(!historyFP.eof()){
                addRetrievedHistory();
                historyFP.ignore();
            }
            else{break;}
        }
    }
    historyFP.close();
}

//Adds a certain value to each digit of the PIN beofre saving in the pincode.txt
//The ATM encrypts pincode to secure the user's account
void ATM:: encrypt(){

int i=0;

    while(pin[i]!='\0'){                                     //habang di pa NULL
    pin[i]=pin[i] + 123;                                     //add code each character
    i++;
    }
}

//Deducts the added value from each digit of the PIN before comparing to the user's entered PIN
void ATM:: decrypt(){                                       //from random symbol, papalabasin pin code para ma-check kung match inenter.
int i=0;

    while(pin[i]!='\0'){                                    //habang di pa NULL
        pin[i]=pin[i] - 123;                                //minus code each character
        i++;
    }
}

//Asks the user to enter PIN until it is match with their actual PIN
//After 3 incorrect tries, it blocks the account and exits the program
void ATM:: askPin(){
int tries=0;
string enteredPin;

    while(enteredPin!=pin && tries<3){       //hanggang di pa correct pin at di pa blocked
        system("cls");
        design.secondBorder();
        design.homeTitle();
        gotoxy(60,30); cout <<"Enter 6-digit pin: ";
        pincode();
        enteredPin=pin;
        retrievePincode();
        decrypt();
        if(enteredPin!=pin){                 //kapag mali ang pin
            SetConsoleTextAttribute(m,4);
            gotoxy(60,33); cout <<"Incorrect pin!";
            SetConsoleTextAttribute(m,15);
            tries++; gotoxy(60,34); system("pause");        //madadagdagan ang number of tries
        }
    }

    if(tries==3){                              //kapag na-block na
        cout <<"\nYour account was blocked!";
        removeCard(); exit(0);
                                            //balik sa homepage.
    }
}

//assigns null to the head of the all accounts and history linked list
void ATM::makeNull(){
    head=NULL;
    headH=NULL;
}

//Displays the available transactions ask the user for its preference.
int ATM:: menu(){

    system("cls");
    design.secondBorder();
    design.homeTitle();
    design.otherScreen();
    design.menuboxes();
    gotoxy(32,28);cout <<RED"[1] Balance Inquiry";
    gotoxy(97,28);cout <<RED"[2] Withdrawal\n";
    gotoxy(32,32);cout <<RED"[3] Deposit";
    gotoxy(97,32);cout <<RED"[4] Fund Transfer";
    gotoxy(32,36);cout <<RED"[5] Other Transactions\n";
    gotoxy(97,36);cout <<RED"[6] Exit\n";
    gotoxy(62,43);cout <<"Enter option 1-6: ";
    cin >> option;
    system(RESET);
    return option;
    if(option > 6 || option <1){
        gotoxy(60,43);cout <<"Invalid option!";
        gotoxy(60,45);system("pause");
    }
}

//Creates a time and date in 12 hr format
//This function is being called to create date for each transaction
void Date() //12 hr format
{
    time_t ttime = time(0); // currrent time

    (strftime(dateTime, sizeof(dateTime), "%a %B %d,%Y %I:%M:%S %p "  ,localtime(&ttime))); //strttime converts the date and time information from a given calendar time
        //cout << dateTime << '\n';  // a = weekday  B= month, d= day, Y= year x= time in 2 hr format  p = am or pm in strftime
    dt=dateTime;
}

//Adds comma in amounts
void putComma(){
    std::locale comma_locale(std::locale(), new comma_numpunct());
    std::cout.imbue(comma_locale);
    cout << std::setprecision(2) << std::fixed;
}

//Sets a fixed window size
HWND WINAPI GetConsoleWindowNT(void)
{
    //declare function pointer type
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    //declare one such function pointer
    GetConsoleWindowT GetConsoleWindow;
    //get a handle on kernel32.dll
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    //assign procedure address to function pointer
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib
    ,TEXT("GetConsoleWindow"));
    //check if the function pointer is valid
    //since the function is undocumented
    if(GetConsoleWindow == NULL){
        return NULL;
    }
    //call the undocumented function
    return GetConsoleWindow();
}

//Sets a fixed font size
void setFontStyle(int FontSize){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = FontSize;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // font style
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

//Sets the fixed place of displays
void gotoxy(int x,int y){
    COORD coord = {0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

