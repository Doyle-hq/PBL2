#ifndef ACCOUNT_REPOSITORY_H
#define ACCOUNT_REPOSITORY_H

#include "../Models/Account.h"
#include <vector>
#include <string>
using namespace std;

class AccountRepository {
private:
    string fileName;

public:
    AccountRepository(string fileName = "Data/Account.txt");

    vector<Account> getAll();
    bool saveAll(const vector<Account>& accounts);

    bool add(const Account& account);
    bool update(const Account& account);
    bool remove(string NV_ID);

    bool findByID(string NV_ID, Account& account);
};

#endif