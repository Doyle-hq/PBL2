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
    bool isLocked;

public:
    Account();
    Account(string pass, string role, string NV_ID,bool isLocked);

    string getPass() const;
    string getRole() const;
    string getNV_ID() const;
    bool getIsLocked() const;

    void setPass(string pass);
    void setRole(string role);
    void setNV_ID(string NV_ID);
    void setIsLocked(bool isLocked);
};

#endif