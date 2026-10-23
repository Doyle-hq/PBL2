#ifndef ACCOUNTMANAGEMENT_H 
#define ACCOUNTMANAGEMENT_H

#include "Account.h"
#include <vector>
#include <string>
using namespace std;

class AccountManagement{
private:
    vector<Account> listAccount;

public:
    AccountManagement();

    void readFile();

    bool login(Account& loginAccount);
};

#endif
