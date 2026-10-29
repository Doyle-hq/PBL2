
#include <iostream>
#include <string>

#include "Manage.h"
#include "AM.h"
#include "Account.h"

using namespace std;

int main() {
    // Tai khoan quan ly duoc khai bao truc tiep trong code
    const string MANAGER_USERNAME = "admin";
    const string MANAGER_PASSWORD = "quanly123";

    Manage manage;
    AccountManagement accountManagement;

    // Doc du lieu tu file
    manage.readfile();
    accountManagement.readFile();

    cout << "\n========== DANG NHAP ==========\n";

    string username;
    string pass;

    cout << "Ten dang nhap: ";
    getline(cin, username);

    cout << "Mat khau: ";
    getline(cin, pass);

    // Kiem tra tai khoan quan ly truoc
    if (username == MANAGER_USERNAME &&
        pass == MANAGER_PASSWORD) {

        cout << "\nDang nhap voi quyen quan ly thanh cong!\n";

        manage.menu();

        // Luu lai du lieu sau khi quan ly thoat menu
        manage.savefile();

        cout << "Da luu du lieu va ket thuc chuong trinh.\n";
        return 0;
    }

    // Neu khong phai quan ly, kiem tra tai khoan nhan vien
    Account loginAccount;

    if (accountManagement.login(username, pass, loginAccount)) {
        string role = loginAccount.getVale();

        if (role == "NhanVien" || role == "nhanvien" || role == "employee") {

            cout << "\nDang nhap voi quyen nhan vien thanh cong!\n";

            // Nhan vien chi xem duoc thong tin theo NV_ID
            manage.displayEmployeeByID(loginAccount.getNV_ID());
        }
        else {
            cout << "Tai khoan khong co quyen truy cap!\n";
            return 0;
        }
    }
    else {
        cout << "Ten dang nhap hoac mat khau khong dung!\n";
        return 0;
    }

    return 0;
}
