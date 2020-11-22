//
//  Account.cpp
//  myBankApplication
//
//  Created by Elias Tiso on 11/30/17.
//  Copyright © 2017 Elias Tiso. All rights reserved.
//

#include "Account.hpp"

Account::Account(){
    accountNo = 0;
    name = "";
    type = 0;
    balance = 0.0;
}

//Mutators implementation
void Account::setAccountNo(int a){
    accountNo = a;
}

void Account::setName(string n){
    name = n;
}

void Account::setType(char t){
    type = t;
}

void Account::setBalance(double b){
    balance = b;
}

//Accessors implementation
int Account::getAccountNo()const{
    return accountNo;
}

string Account::getName()const{
    return name;
}

char Account::getType()const{
    return type;
}

double Account::getBalance()const{
    return balance;
}
Account::~Account(){}
