
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
using namespace std;

class Account{
private:
    string pass;
    string vale;
    string NV_ID;

public:
    Account();
    Account(string pass, string vale, string NV_ID);

    string getPass();
    string getVale();
    string getNV_ID();

    void setPass(string pass);
    void setVale(string vale);
    void setNV_ID(string NV_ID);
};

#endif
