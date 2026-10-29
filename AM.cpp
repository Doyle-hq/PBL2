#include "AM.h"
#include <fstream>
#include <iostream>

AccountManagement::AccountManagement() {
}

void AccountManagement::readFile() {
    ifstream file("Account.txt");

    if (!file.is_open()) {
        cout << "Khong mo duoc file tai khoan!\n";
        return;
    }

    listAccount.clear();

    string pass;
    string role;
    string NV_ID;

    while (getline(file, pass)) {
        if (!getline(file, role) || !getline(file, NV_ID)) {

            cout << "Du lieu tai khoan khong day du!\n";
            break;
        }

        Account tk(pass, role, NV_ID);
        listAccount.push_back(tk);
    }

    file.close();
    cout << "Doc danh sach tai khoan hoan tat.\n";
}

bool AccountManagement::login(const string& NV_ID, const string& pass, Account& loginAccount){
    // Kiem tra tai khoan Admin
    if (NV_ID == "Admin" && pass == "quanly123") {
        loginAccount = Account("quanly123", "manager", "Admin");
        return true;
    }

    // Kiem tra tai khoan nhan vien trong file
    for (int i = 0; i < listAccount.size(); i++) {
        if (listAccount[i].getNV_ID() == NV_ID && listAccount[i].getPass() == pass){
            loginAccount = listAccount[i];
            return true;
        }
    }

    return false;
}
