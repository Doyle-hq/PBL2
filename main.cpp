#include <iostream>
#include <string>

#include "Manage.h"
#include "AM.h"
#include "Account.h"

using namespace std;

int main() {
    Manage manage;
    AccountManagement accountManagement;

    // Doc du lieu tu file
    manage.readfile();
    accountManagement.readFile();

    cout << "\n========== DANG NHAP ==========\n";

    string NV_ID;
    string pass;

    cout << "Ma dang nhap: ";
    getline(cin, NV_ID);

    cout << "Mat khau: ";
    getline(cin, pass);

    // Kiem tra thong tin dang nhap
    Account loginAccount;

    if (!accountManagement.login(NV_ID, pass, loginAccount)) {
        cout << "\nMa dang nhap hoac mat khau khong dung!\n";
        return 0;
    }

    // Phan quyen theo vai tro tai khoan
    string role = loginAccount.getVale();

    if (role == "manager") {
        cout << "\nDang nhap voi quyen quan ly thanh cong!\n";

        // Hien thi menu quan ly
        manage.menu();

        // Luu du lieu sau khi quan ly thoat menu
        manage.savefile();

        cout << "\nDa luu du lieu va ket thuc chuong trinh.\n";
    } else if (role == "NhanVien" || role == "nhanvien" || role == "employee") {
        cout << "\nDang nhap voi quyen nhan vien thanh cong!\n";

        // Nhan vien chi xem thong tin cua minh
        manage.displayEmployeeByID(loginAccount.getNV_ID());
    } else {
        cout << "\nTai khoan khong co quyen truy cap!\n";
        return 0;
    }

    return 0;
}
