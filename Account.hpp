//
//  Account.hpp
//  myBankApplication
//
//  Created by Elias Tiso on 11/30/17.
//  Copyright © 2017 Elias Tiso. All rights reserved.
//

#ifndef Account_hpp
#define Account_hpp

#include <string>
using std::string;

#include <stdio.h>



class Account
{
public:
    Account();
    
    //mutators
    void setAccountNo(int);
    void setName(string);
    void setType(char);
    void setBalance(double);
    
                    //accessors
    int getAccountNo()const;
    string getName()const;
    char getType()const;
    double getBalance()const;
                    
    virtual ~Account();
    
protected:
    
private:
                    int accountNo;
                    string name;
                    char type;
                    double balance;
    
    };
#endif /* Account_hpp */
