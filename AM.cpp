#include "AM.h"
#include <fstream>

AccountManagement::AccountManagement() {
}


void AccountManagement::readFile() {
    ifstream file("Account.txt"); //mo file de doc

    if (!file.is_open()) {
        cout << "Không mở được file tài khoản" << endl;
        return;
    }

    listAccount.clear();

    string username;
    string pass;
    string vale;
    string NV_ID;

    while (getline(file, username)) {
        if (!getline(file, pass) || !getline(file, vale) || !getline(file, NV_ID)){

            cout << "Dữ liệu tài khoản không đầy đủ" << endl;
            break;
        }

        Account tk(username, pass, vale, NV_ID);

        listAccount.push_back(tk);
    }

    file.close();

    cout << "Doc danh sach tai khoan thanh cong!\n";
}


bool AccountManagement::login(Account& loginAccount) {
    string username;
    string pass;

    cout << "Nhap ten dang nhap: ";
    getline(cin, username);

    cout << "Nhap mat khau: ";
    getline(cin, pass);

    for (int i = 0; i < listAccount.size(); i++) {
        if (listAccount[i].getUserName() == username && listAccount[i].getPass() == pass) {

            loginAccount = listAccount[i];

            cout << "Dang nhap thanh cong!\n";
            return true;
        }
    }

    cout << "Ten dang nhap hoac mat khau khong dung!\n";
    return false;
}
