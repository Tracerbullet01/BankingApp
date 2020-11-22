//
//  main.cpp
//  myBankApplication
//
//  Created by Elias Tiso on 11/28/17.
//  Copyright © 2017 Elias Tiso. All rights reserved.
//

/****************************************************************************
 *                          BANKING APPLICATION                             *
 *                     -----------------------------                        *
 *                                                                          *
 *  @Author: Elias Tiso                                                     *
 *  @created: November 28, 2017                                             *
 ****************************************************************************
 */

#include <iostream>
#include <iomanip>
#include <regex>
#include <string>
#include <math.h>
#include "Account.hpp"
#include <vector>
#include <fstream>

using namespace std;

void intro();
int getChoice();
void checkInt(string &);
void displayMenu();
void loadRecords(vector<Account> &);
void tokenizer(string, int &, string &, char &, double &);
void createAccount(vector<Account> &);
bool isAccountNumUsed(const vector<Account> &, int);
void writeAccount(const vector<Account> &);
void showAccount(const Account &);
void listAllAccounts(const vector<Account> &);
void displayAnAccount(const vector<Account> &);
int getIndex(const vector<Account> &, int);
void accountNotFound(int);
void updateAnAccount(vector<Account> &);
void depositWithdraw(vector<Account> &, int);
void displaySortedAccounts(vector<Account>);
void myBubbleSort(vector<Account> &);
void dummyMessage();
void goodbye();

int main() {
    int choice;
    
    vector<Account> acc;
    
    loadRecords(acc);
    
    intro();
    
    
    do{
        displayMenu();
        choice = getChoice();
    
        switch (choice) {
            case 1:
                createAccount(acc);
                break;
            case 2:
                displayAnAccount(acc);
                break;
            case 3:
                listAllAccounts(acc);
                break;
            case 4:
                displaySortedAccounts(acc);
                break;
            case 5:
                updateAnAccount(acc);
                break;
            case 6:
                depositWithdraw(acc, 0);
                break;
            case 7:
                depositWithdraw(acc, 1);
                break;
            case 8:
                goodbye();
                
        }
        
    }while(1 <= choice && choice <= 8 );
    
    return 0;
}


/****************************************************************************
 *                       FUNCTION DEFINITION intro                          *
 *                     -----------------------------                        *
 * This function outputs a preliminary screen for the program.              *
 ****************************************************************************
 */
void intro(){
    //Formatted output for INITIAL SCREEN of application
    cout << "\n\n\n";
    cout << setw(14) << right << "$" << "--------------------------------------"
    "----------------------------------$" << endl;
    cout << setw(14) << "$" << "  MMM     MMM  YY   YY       BBBBBB      AAA   "
    "   NNN     NN  KK    KK  $" << endl;
    cout << setw(14) << "$" << "  MM MM MM MM   YY YY        BB   BB    A   A  "
    "   NN NN   NN  KK  KK    $" << endl;
    cout << setw(14) << "$" << "  MM  MMM  MM    YY    $$$$  BBBBBB    AAAAAAA "
    "   NN  NN  NN  KKK       $" << endl;
    cout << setw(14) << "$" << "  MM       MM    YY          BB   BB  AA     AA"
    "   NN   NN NN  KK  KK    $" << endl;
    cout << setw(14) << "$" << "  MM       MM    YY          BBBBBB  AA       A"
    "A  NN     NNN  KK    KK  $" << endl;
    cout << setw(14) << "$" << "-----------------------------------------------"
    "-------------------------$" << endl;
    cout << setw(14) << "$" << "                                               "
    "                         $" << endl;
    cout << setw(14) << "$" << "                          BANKING APPLICATION  "
    "                         $" << endl;
    cout << setw(14) << "$" << "                                               "
    "                         $" << endl;
    cout << setw(14) << "$" << "                 AUTHOR: ELIAS TISO, AN A++ STU"
    "DENT                     $" << endl;
    cout << setw(14) << "$" << "                 SCHOOL: COLLEGE OF THE DESERT, "
    "PALM DESERT             $" << endl;
    cout << setw(14) << "$" << "                                               "
    "                         $" << endl;
    cout << setw(14) << "$" << "                                               "
    "                         $" << endl;
    cout << setw(14) << "$" << "                 version: 1.0.0.00.000 (alpha) "
    "                         $" << endl;
    cout << setw(14) << "$" << "-----------------------------------------------"
    "-------------------------$" << endl;
    
    cout << "\n\n\n" << setw(43) << "Press Any Key to Continue...";
    
    //program halting function
    cin.get();
}

/****************************************************************************
 *                    FUNCTION DEFINITION displayMenu                       *
 *                     -----------------------------                        *
 * This function displays a menu which provides the user with options to    *
 * choose from.                                                             *
 ****************************************************************************
 */
void displayMenu(){
    system("cls");
    cout << "\n\n\n\n";
    cout << setw(30) << "MAIN MENU\n\n";
    cout << setw(15) << "1." << " Create a New Account\n";
    cout << setw(15) << "2." << " Display an Account\n";
    cout << setw(15) << "3." << " List All Accounts\n";
    cout << setw(15) << "4." << " List All Accounts, Sorted\n";
    cout << setw(15) << "5." << " Update Account\n";
    cout << setw(15) << "6." << " Make a Deposit\n";
    cout << setw(15) << "7." << " Withdraw Money\n";
    cout << setw(15) << "8." << " Exit the Program\n";
    cout << endl;
    cout << setw(13) << " " << "Enter your choice: ";
}

/****************************************************************************
 *                    FUNCTION DEFINITION loadRecords                       *
 *                     -----------------------------                        *
 * This function loads the data of an account from a file.                  *
 ****************************************************************************
 */
void loadRecords(vector<Account> &v){
    Account acc;
    int accNo;
    string name, str;
    char ch;
    double bal;
    
    ifstream inFile("accounts.txt");
    if(!inFile){
        cout << setw(13) << " " << "ERROR!!! Could not open file";
        exit(0);
    }
    while(getline(inFile, str)){
        tokenizer(str, accNo, name, ch, bal);
        acc.setAccountNo(accNo);
        acc.setName(name);
        acc.setType(ch);
        acc.setBalance(bal);
        
        v.push_back(acc);
    }
}

/****************************************************************************
 *                     FUNCTION DEFINITION tokenizer                        *
 *                     -----------------------------                        *
 * This function separates the various pieces of data from a single string. *
 ****************************************************************************
 */
void tokenizer(string str, int &accNo, string &name, char &ch, double &bal){
    size_t length = str.length();
    
    size_t firstSlash = str.find_first_of('/');
    
    size_t secondSlash = str.find_first_of('/', firstSlash + 1);
    
    size_t thirdSlash = str.find_first_of('/', secondSlash + 1);
    
    string acno = str.substr(0, firstSlash);
    accNo = stoi(acno);
    
    name = str.substr(firstSlash + 1, (secondSlash - firstSlash) - 1);
    
    string chr = str.substr(secondSlash + 1, 1);
    
    ch = chr[0];        //cast a string to a char
    string doubleBal = str.substr(thirdSlash + 1, (length - thirdSlash) - 1);
    bal = stod(doubleBal);      //casts string to a double
}

/****************************************************************************
 *                   FUNCTION DEFINITION createAccount                      *
 *                     -----------------------------                        *
 * This function allows a user to create a new account, with account        *
 * number, name, type, and amount.                                          *
 ****************************************************************************
 */
void createAccount(vector<Account> &v){
    Account acc;
    int accNo;
    string name;
    char ch;
    double bal;
    
    system("cls");
    cout << "\n\n\n";
    cout << setw(40) << "CREATE AN ACCOUNT" << endl << endl;
    
    cout << setw(13) << " " << "Enter an Account Number............. ";
    cin >> accNo;
    
    while(cin.fail()){
        
        cin.clear();        //clear the buffer
        cin.ignore();
        
        cout << setw(13) << " " << "Only Integers. Please Re-Enter.. ";
        cin >> accNo;
    }
    
    while(isAccountNumUsed(v, accNo)){
        cout << setw(13) << " " << "Error!!! Acc No used. Re-Enter.. ";
        cin >> accNo;
        
    }
    
    acc.setAccountNo(accNo);
    cin.ignore();
    
    cout << setw(13) << " " << "Enter an Account Name............... ";
    getline(cin, name);
    acc.setName(name);
    
    cout << setw(13) << " " << "Enter an Account Type....... S/C ... ";
    cin >> ch;
    ch = toupper(ch);
    acc.setType(ch);
    
    cout << setw(13) << " " << "Enter an Account Balance............ ";
    cin >> bal;
    acc.setBalance(bal);
    
    v.push_back(acc);
    
    writeAccount(v);
    
    showAccount(acc);
}

/****************************************************************************
 *                  FUNCTION DEFINITION isAccountNumUsed                    *
 *                     -----------------------------                        *
 * This function determines whether or not a given account number exists in *
 * the file.                                                                *
 ****************************************************************************
 */
bool isAccountNumUsed(const vector<Account> &v, int accNo){
    for(size_t i = 0; i < v.size(); i ++){
        if(v[i].getAccountNo() == accNo){
            return true;
            break;
        }
    }
    return false;
}

/****************************************************************************
 *                    FUNCTION DEFINITION writeAccount                      *
 *                     -----------------------------                        *
 * This function writes a created account as one string to a file.          *
 ****************************************************************************
 */
void writeAccount(const vector<Account> &v){
    ofstream outFile("accounts.txt");
    if(!outFile){
        cout << setw(13) << " " << "ERROR!!! Could not open file";
        exit(0);
    }
    
    outFile << fixed << showpoint << setprecision(2);
    
    for(size_t i = 0; i < v.size(); i++) {                                      //either do unsigned i or size_t i
        outFile << v[i].getAccountNo() << "/" << v[i].getName() << "/"          //v[i].blalabla
        << v[i].getType() << "/" << v[i].getBalance() << endl;
    }
}

/****************************************************************************
 *                    FUNCTION DEFINITION showAccount                       *
 *                     -----------------------------                        *
 * This function outputs the data for a previously specified account.       *
 ****************************************************************************
 */
void showAccount(const Account &acc){
    system("cls");
    cout << "\n\n\n";
    cout << fixed << setprecision(2);
    
    cout << setw(40) << "ACCOUNT INFO" << endl << endl;
    cout << setw(13) << " " << "Account Number....................... "
    << acc.getAccountNo() << endl;
    cout << setw(13) << " " << "Account Name......................... "
    << acc.getName() << endl;
    cout << setw(13) << " " << "Account Type......................... "
    << acc.getType() << endl;
    cout << setw(13) << " " << "Account Balance...................... "
    << acc.getBalance() << endl;
    cout << endl;
    cout << setw(13) << " " << "Press Enter to Continue...";
    cin.get();
    cin.get();
    
}

/****************************************************************************
 *                     FUNCTION DEFINITION getChoice                        *
 *                     -----------------------------                        *
 * This function receives and returns the choice of a user from the menu.   *
 ****************************************************************************
 */
int getChoice(){
    string s;
    cin >> s;
    checkInt(s);
    return stoi(s);
}

/****************************************************************************
 *                     FUNCTION DEFINITION checkInt                         *
 *                     -----------------------------                        *
 * This function validates the menu choice of a user.                       *
 ****************************************************************************
 */
void checkInt(string &num){
    regex integer("[1-8]$");
    
    while(!(regex_match(num, integer))){
        cout << setw(13) << " "
        << "Wrong input. Please Re-Enter a number between 1 - 8 ";
        cin >> num;
        if(regex_match(num, integer)){
            break;
        }
    }
}

/****************************************************************************
 *                  FUNCTION DEFINITION listAllAccounts                     *
 *                     -----------------------------                        *
 * This function displays the data of each account in a formatted list.     *
 ****************************************************************************
 */
void listAllAccounts(const vector<Account> &v){
    system("cls");
    cout << "\n\n\n";
    
    cout << setw(40) << "LIST ALL ACCOUNTS" << endl << endl;
    cout << setw(13) << " " << "ACC NO" << setw(9) << "NAME" << setw(16)
    << "TYPE" << setw(13) << "BALANCE" << endl;
    cout << setw(13) << " "
    << "-------------------------------------------------------------" << endl;
    cout << fixed << setprecision(2);
    for(size_t i = 0; i < v.size(); i ++){
        cout << setw(13) << " " << setw(9) << left << v[i].getAccountNo()
        << setw(20) << v[i].getName() << setw(3) << v[i].getType()
        << " $" << setw(10) << right << v[i].getBalance() << endl;
    }
    cout << endl;
    cout << setw(13) << " " << "Press Enter to Continue...";
    cin.get();
    cin.get();
}

/****************************************************************************
 *                 FUNCTION DEFINITION displayAnAccount                     *
 *                     -----------------------------                        *
 * This function shows the data for the account of the user's choice.       *
 ****************************************************************************
 */
void displayAnAccount(const vector<Account> &v){
    system("cls");
    Account     acc;
    int         accNo;
    
    cout << "\n\n\n";
    cout << setw(44) << "ACCOUNT INFO FOR ACCOUNT NUMBER" << endl << endl;
    cout << setw(13) << " " << "Enter an Account Number.............. :";
    cin >> accNo;
    
    if(!isAccountNumUsed(v, accNo)){
        cout << setw(13) << " " << "ERROR!!! No Account. Re-Enter.... :";
        cin >> accNo;
    }
    if(isAccountNumUsed(v, accNo)){
        int index = getIndex(v, accNo);
        acc = v[index];
        showAccount(acc);
    }
    else{
        accountNotFound(accNo);
    }
    
}

/****************************************************************************
 *                     FUNCTION DEFINITION getIndex                         *
 *                     -----------------------------                        *
 * This function finds and returns the index for an account stored in the   *
 * Account vector.                                                          *
 ****************************************************************************
 */
int getIndex(const vector<Account> &v, int accNo){
    int index;
    for(int i = 0; i < v.size(); i ++){
        if(v[i].getAccountNo() == accNo){
            index = i;
            break;
        }
    }
    return index;
}

/****************************************************************************
 *                  FUNCTION DEFINITION accountNotFound                     *
 *                     -----------------------------                        *
 * This function outputs a message to be used if the user enters a          *
 * nonexistent account number.                                              *
 ****************************************************************************
 */
void accountNotFound(int accNo){
    cout << setw(13) << " " << "No Account with Account Number "
    << accNo << " Exists" << endl;
    
    cout << setw(13) << " " << "Press Enter to continue...";
    cin.get();
    cin.get();

}

/****************************************************************************
 *                  FUNCTION DEFINITION updateAnAccount                     *
 *                     -----------------------------                        *
 * This function updates each member of an account object.                  *
 ****************************************************************************
 */
void updateAnAccount(vector<Account> &v){
    Account     acc;
    int         accNo, index;
    string      name;
    char        ch;
    double      bal;
    
    cout << "\n\n\n";
    cout << setw(40) << "UPDATE AN ACCOUNT" << endl << endl;
    cout << setw(13) << " " << "Enter an Account Number......... ";
    cin >> accNo;
    if(isAccountNumUsed(v, accNo)){
        system("cls");
        index = getIndex(v, accNo);
        acc = v[index];
        system("cls");
        cout << "\n\n\n";
        cout << fixed << setprecision(2);
        cout << setw(40) << "ACCOUNT INFORMATION" << endl << endl;
        
        cout << setw(13) << " " << "Account No.................... "
        << acc.getAccountNo() << endl;
        cout << setw(13) << " " << "Account Holder Name........... "
        << acc.getName() << endl;
        cout << setw(13) << " " << "Account Holder Type........... "
        << acc.getType() << endl;
        cout << setw(13) << " " << "Account Holder Balance........ "
        << acc.getBalance() << endl;
        cout << "\n\n\n";
        cout << setw(40) << "UPDATE INFORMATION" << endl << endl;
        
        cout << setw(13) << " " << "Account No.................... "
        << acc.getAccountNo() << endl;
        cout << setw(13) << " " << "Account Holder Name........... ";
        cin.ignore();
        getline(cin, name);
        acc.setName(name);
        cout << setw(13) << " " << "Account Holder Type........... ";
        cin >> ch;
        ch = toupper(ch);
        acc.setType(ch);
        cout << setw(13) << " " << "Account Holder Balance........ ";
        cin >> bal;
        acc.setBalance(bal);
        
        v[index] = acc;
        writeAccount(v);
        showAccount(acc);
    }
    else{
        accountNotFound(accNo);
    }
}

/****************************************************************************
 *                  FUNCTION DEFINITION depositWithdraw                     *
 *                     -----------------------------                        *
 * This function increases or decreases the balance member variable of an   *
 * account object.                                                          *
 ****************************************************************************
 */
void depositWithdraw(vector<Account> &v, int flag){
    system("cls");
    Account acc;
    int     accNo, index;
    double bal, amount;
    
    cout << "\n\n\n";
    cout << setw(40) << "DEPOSIT/WITHDRAW" << endl << endl;
    
    cout << setw(13) << " " << "Enter an Account Number............. ";
    cin >> accNo;
    
    if(isAccountNumUsed(v, accNo)){
        index = getIndex(v, accNo);
        acc = v[index];
        cout << fixed << setprecision(2);
        bal = acc.getBalance();
        cout << setw(13) << " " << "Account Balance is " << bal << endl;
        
        if(flag == 0){
            cout << setw(13) << " " << "Enter the Amount to Deposit........ :";
            cin >> amount;
            bal += amount;
        }
        
        else if(flag == 1){
            cout << setw(13) << " " << "Enter the Amount to Withdraw........ :";
            cin >> amount;
            bal -= amount;
        }
        acc.setBalance(bal);
        v[index] = acc;
        writeAccount(v);
        cout << endl;
        cout << setw(13) << " " << "New Balance for " << accNo << " $"
        << bal << endl;
        
        cout << setw(13) << " " << "Press Enter to Continue...";
        cin.get();
        cin.get();
        
    }
    else{
        accountNotFound(accNo);
        
    }
    
}

/****************************************************************************
 *                FUNCTION DEFINITION displaySortedAccounts                 *
 *                     -----------------------------                        *
 * This function displays a formatted list of data for each account.        *
 ****************************************************************************
 */
void displaySortedAccounts(vector<Account> v){
    myBubbleSort(v);
    
    system("cls");
    cout << "\n\n\n";
    cout << fixed << setprecision(2);
    cout << setw(40) << "LIST ALL ACCOUNTS SORTED" << endl << endl;
    cout << setw(13) << " " << "AccNo" << setw(14) << "Name"
    << setw(17) << "AccType" << setw(11) << "Balance" << endl;
    cout << setw(13) << " " << "=============================="
    "========================" << endl;
    for(size_t i = 0; i < v.size(); i++){
        cout << setw(13) << " " << setw(7) << left << v[i].getAccountNo()
        << setw(25) << v[i].getName() << setw(5) << v[i].getType()
        << setw(10) << right << v[i].getBalance() << endl;
    }
    cout << setw(13) << " " << "Press Enter to Continue...";
    cin.get();
    cin.get();
    
}

/****************************************************************************
 *                    FUNCTION DEFINITION myBubbleSort                      *
 *                     -----------------------------                        *
 * This function sorts accounts in a vector by name.                        *
 ****************************************************************************
 */
void myBubbleSort(vector<Account> & v){
    Account temp;
    bool madeSwap;
    
    do{
        madeSwap = false;
        for(size_t i = 0; i < v.size() - 1; i ++){
            if(v[i].getName() > v[i + 1].getName()){
                temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                madeSwap = true;
            }
        }
    }while(madeSwap);
}

/****************************************************************************
 *                   FUNCTION DEFINITION dummyMesssage                      *
 *                     -----------------------------                        *
 * This function was used to tell the user that a selected module had been  *
 * developed during program development.                                    *
 ****************************************************************************
 */
void dummyMessage(){
    cout << "\n\n\n";
    cout << setw(13) << " " << "This module has not been developed yet" << endl;
    cout << endl;
    cout << setw(13) << " " << "Please return later!!!!" << endl;
    cout << endl;
    cout << setw(13) << " " << "Press Enter to continue....";
    cin.get();
    cin.get();
}

/****************************************************************************
 *                      FUNCTION DEFINITION goodbye                         *
 *                     -----------------------------                        *
 * This function displays a goodbye message if the user chooses to end the  *
 * program.                                                                 *
 ****************************************************************************
 */
void goodbye(){
    system("cls");
    cout << "\n\n\n";
    cout << setw(13) << " " << "We hate to see you leave" << endl;
    cout << endl;
    cout << setw(13) << " " << "     GOODBYE!!!!" << endl;
    cout << endl << endl;
    exit(0);
}
