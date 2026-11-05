#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
using namespace std;

class Account{
private:
    string pass;
    string role;
    string NV_ID;

public:
    Account();
    Account(string pass, string role, string NV_ID);

    string getPass();
    string getRole();
    string getNV_ID();

    void setPass(string pass);
    void setRole(string role);
    void setNV_ID(string NV_ID);
};

#endif
