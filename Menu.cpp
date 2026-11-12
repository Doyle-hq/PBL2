#include "Menu.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
using namespace std;

Menu::Menu() {}

void Menu::displayEmployee(const Employee& e) {
    cout << "\n========== THONG TIN NHAN VIEN ==========\n";
    cout << "Ma nhan vien: " << e.getNV_ID() << endl;
    cout << "Ho ten: " << e.getFullName() << endl;
    cout << "Ngay sinh: " << e.getDateOfBirth() << endl;
    cout << "Gioi tinh: " << e.getGender() << endl;
    cout << "So dien thoai: " << e.getPhone() << endl;
    cout << "Dia chi: " << e.getAddress() << endl;
    cout << "Ma phong ban: " << e.getPHG_ID() << endl;
    cout << "Ngay vao lam: " << e.getNgayVaoLam() << endl;
    cout << "Trang thai: " << e.getStatus() << endl;
}

void Menu::displayEmployeeList(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "\nDanh sach nhan vien trong!\n";
        return;
    }

    cout << "\n";
    cout << left
         << setw(13) << "NV_ID"
         << setw(25) << "Ho ten"
         << setw(15) << "Ngay sinh"
         << setw(10) << "Gioi tinh"
         << setw(13) << "PHG_ID"
         << setw(15) << "Ngay vao lam"
         << setw(18) << "Trang thai" << endl;

    cout << string(109, '-') << endl;

    for (const Employee& e : employees) {
        cout << left
             << setw(13) << e.getNV_ID()
             << setw(25) << e.getFullName()
             << setw(15) << e.getDateOfBirth()
             << setw(10) << e.getGender()
             << setw(13) << e.getPHG_ID()
             << setw(15) << e.getNgayVaoLam()
             << setw(18) << e.getStatus() << endl;
    }
}

void Menu::run() {
    while (true) {
        cout << "\n========== DANG NHAP ==========\n";

        string NV_ID, pass;
        cout << "Ma dang nhap: ";
        getline(cin, NV_ID);

        cout << "Mat khau: ";
        getline(cin, pass);

        Account loginAccount;
        string message;

        if (!accountService.login(NV_ID, pass, loginAccount, message)) {
            cout << "\n" << message << endl;
            cout << "1. Dang nhap lai\n";
            cout << "0. Thoat\n";
            cout << "Lua chon: ";

            string choice;
            getline(cin, choice);

            if (choice == "0") return;
            continue;
        }

        cout << "\n" << message << endl;

        if (loginAccount.getRole() == "manager") {
            managerMenu();
        }
        else if (loginAccount.getRole() == "employee" ||
                 loginAccount.getRole() == "NhanVien" ||
                 loginAccount.getRole() == "nhanvien") {
            employeeMenu(loginAccount);
        }
        else {
            cout << "Tai khoan khong co quyen truy cap!\n";
        }

        return;
    }
}

// ================= MENU QUAN LY =================

void Menu::managerMenu() {
    while (true) {
        cout << "\n========== MENU QUAN LY ==========\n";
        cout << "1. Them nhan vien\n";
        cout << "2. Cap nhat nhan vien\n";
        cout << "3. Xoa nhan vien\n";
        cout << "4. Hien thi danh sach nhan vien\n";
        cout << "5. Tim kiem nhan vien\n";
        cout << "6. Sap xep nhan vien\n";
        cout << "7. Loc theo phong ban\n";
        cout << "8. Khoa tai khoan\n";
        cout << "9. Mo khoa tai khoan\n";
        cout << "10. Xac nhan nhan vien nghi viec\n";
        cout << "0. Dang xuat\n";
        cout << "Lua chon: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") addEmployee();
        else if (choice == "2") updateEmployee();
        else if (choice == "3") deleteEmployee();
        else if (choice == "4") displayEmployees();
        else if (choice == "5") searchEmployee();
        else if (choice == "6") sortEmployees();
        else if (choice == "7") filterEmployees();
        else if (choice == "8") lockAccount();
        else if (choice == "9") unlockAccount();
        else if (choice == "10") resignEmployee();
        else if (choice == "0") {
            cout << "Da dang xuat!\n";
            return;
        }
        else {
            cout << "Lua chon khong hop le!\n";
        }
    }
}

// ================= THEM NHAN VIEN =================

void Menu::addEmployee() {
    cout << "\n========== THEM NHAN VIEN ==========\n";

    string name, dob, gender, phone, address, department;

    cout << "Ho ten: ";
    getline(cin, name);

    cout << "Ngay sinh (dd/mm/yyyy): ";
    getline(cin, dob);

    cout << "Gioi tinh (Nam/Nu): ";
    getline(cin, gender);

    cout << "So dien thoai: ";
    getline(cin, phone);

    cout << "Dia chi: ";
    getline(cin, address);

    cout << "Ma phong ban (3 chu so): ";
    getline(cin, department);

    Employee employee(
        "", name, dob, gender, phone, address,
        department, "", "Dang lam"
    );

    string message;

    if (employeeService.addEmployee(employee, message)) {
        cout << "\n" << message << endl;
        cout << "Ma nhan vien moi: " << employee.getNV_ID() << endl;
        cout << "Mat khau mac dinh: " << employee.getNV_ID() << endl;
    }
    else {
        cout << "\n" << message << endl;
    }
}

// ================= CAP NHAT NHAN VIEN =================

void Menu::updateEmployee() {
    cout << "\n========== CAP NHAT NHAN VIEN ==========\n";

    string NV_ID;
    cout << "Nhap ma nhan vien: ";
    getline(cin, NV_ID);

    Employee employee;

    if (!employeeService.findByID(NV_ID, employee)) {
        cout << "Khong tim thay nhan vien!\n";
        return;
    }

    if (employee.getStatus() == "Da nghi viec") {
        cout << "Nhan vien da nghi viec, khong the cap nhat!\n";
        return;
    }

    cout << "\nThong tin hien tai:";
    displayEmployee(employee);

    cout << "\nNhap thong tin moi:\n";

    string value;

    cout << "Ho ten (Enter de giu nguyen): ";
    getline(cin, value);
    if (!value.empty()) employee.setFullName(value);

    cout << "Ngay sinh (Enter de giu nguyen): ";
    getline(cin, value);
    if (!value.empty()) employee.setDateOfBirth(value);

    cout << "Gioi tinh (Enter de giu nguyen): ";
    getline(cin, value);
    if (!value.empty()) employee.setGender(value);

    cout << "So dien thoai (Enter de giu nguyen): ";
    getline(cin, value);
    if (!value.empty()) employee.setPhone(value);

    cout << "Dia chi (Enter de giu nguyen): ";
    getline(cin, value);
    if (!value.empty()) employee.setAddress(value);

    cout << "Ma phong ban (Enter de giu nguyen): ";
    getline(cin, value);
    if (!value.empty()) employee.setPHG_ID(value);

    string message;

    if (employeeService.updateEmployee(employee, message)) {
        cout << message << endl;
    }
    else {
        cout << message << endl;
    }
}

// ================= XOA NHAN VIEN =================

void Menu::deleteEmployee() {
    cout << "\n========== XOA NHAN VIEN ==========\n";

    string NV_ID;
    cout << "Nhap ma nhan vien: ";
    getline(cin, NV_ID);

    Employee employee;

    if (!employeeService.findByID(NV_ID, employee)) {
        cout << "Khong tim thay nhan vien!\n";
        return;
    }

    displayEmployee(employee);

    cout << "\nBan co chac chan muon xoa? (Y/N): ";
    string confirm;
    getline(cin, confirm);

    if (confirm == "Y" || confirm == "y") {
        string message;

        if (employeeService.deleteEmployee(NV_ID, message)) {
            cout << message << endl;
        }
        else {
            cout << message << endl;
        }
    }
    else {
        cout << "Da huy thao tac xoa!\n";
    }
}

// ================= HIEN THI DANH SACH =================

void Menu::displayEmployees() {
    displayEmployeeList(employeeService.getAllEmployees());
}

// ================= TIM KIEM =================

void Menu::searchEmployee() {
    cout << "\n========== TIM KIEM NHAN VIEN ==========\n";
    cout << "1. Tim theo ma nhan vien\n";
    cout << "2. Tim theo ho ten\n";
    cout << "Lua chon: ";

    string choice;
    getline(cin, choice);

    if (choice == "1") {
        string NV_ID;
        cout << "Nhap ma nhan vien: ";
        getline(cin, NV_ID);

        Employee employee;

        if (employeeService.findByID(NV_ID, employee)) {
            displayEmployee(employee);
        }
        else {
            cout << "Khong tim thay nhan vien!\n";
        }
    }
    else if (choice == "2") {
        string name;
        cout << "Nhap ten can tim: ";
        getline(cin, name);

        displayEmployeeList(employeeService.searchByName(name));
    }
    else {
        cout << "Lua chon khong hop le!\n";
    }
}

// ================= SAP XEP =================

void Menu::sortEmployees() {
    cout << "\n========== SAP XEP NHAN VIEN ==========\n";
    cout << "1. Sap xep theo ma nhan vien\n";
    cout << "2. Sap xep theo ho ten\n";
    cout << "3. Sap xep theo phong ban\n";
    cout << "Lua chon: ";

    string choice;
    getline(cin, choice);

    if (choice == "1") {
        displayEmployeeList(employeeService.sortByID());
    }
    else if (choice == "2") {
        displayEmployeeList(employeeService.sortByName());
    }
    else if (choice == "3") {
        displayEmployeeList(employeeService.sortByDepartment());
    }
    else {
        cout << "Lua chon khong hop le!\n";
    }
}

// ================= LOC PHONG BAN =================

void Menu::filterEmployees() {
    string PHG_ID;

    cout << "\nNhap ma phong ban can loc: ";
    getline(cin, PHG_ID);

    displayEmployeeList(employeeService.filterByDepartment(PHG_ID));
}

// ================= KHOA TAI KHOAN =================

void Menu::lockAccount() {
    string NV_ID;

    cout << "\nNhap ma nhan vien can khoa tai khoan: ";
    getline(cin, NV_ID);

    string message;

    if (accountService.lockAccount(NV_ID, message)) {
        cout << message << endl;
    }
    else {
        cout << message << endl;
    }
}

// ================= MO KHOA TAI KHOAN =================

void Menu::unlockAccount() {
    string NV_ID;

    cout << "\nNhap ma nhan vien can mo khoa: ";
    getline(cin, NV_ID);

    string message;

    if (accountService.unlockAccount(NV_ID, message)) {
        cout << message << endl;
    }
    else {
        cout << message << endl;
    }
}

// ================= NGHI VIEC =================

void Menu::resignEmployee() {
    string NV_ID;

    cout << "\nNhap ma nhan vien nghi viec: ";
    getline(cin, NV_ID);

    Employee employee;

    if (!employeeService.findByID(NV_ID, employee)) {
        cout << "Khong tim thay nhan vien!\n";
        return;
    }

    displayEmployee(employee);

    cout << "\nXac nhan nhan vien nghi viec? (Y/N): ";
    string confirm;
    getline(cin, confirm);

    if (confirm == "Y" || confirm == "y") {
        string message;

        if (employeeService.confirmResignation(NV_ID, message)) {
            cout << message << endl;
        }
        else {
            cout << message << endl;
        }
    }
    else {
        cout << "Da huy thao tac!\n";
    }
}

// ================= MENU NHAN VIEN =================

void Menu::employeeMenu(const Account& account) {
    while (true) {
        cout << "\n========== MENU NHAN VIEN ==========\n";
        cout << "1. Xem thong tin ca nhan\n";
        cout << "2. Doi mat khau\n";
        cout << "0. Dang xuat\n";
        cout << "Lua chon: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            Employee employee;

            if (employeeService.findByID(account.getNV_ID(), employee)) {
                displayEmployee(employee);
            }
            else {
                cout << "Khong tim thay thong tin nhan vien!\n";
            }
        }
        else if (choice == "2") {
            string oldPass, newPass, message;

            cout << "Nhap mat khau hien tai: ";
            getline(cin, oldPass);

            cout << "Nhap mat khau moi: ";
            getline(cin, newPass);

            if (accountService.changePassword(
                account.getNV_ID(), oldPass, newPass, message)) {
                cout << message << endl;
            }
            else {
                cout << message << endl;
            }
        }
        else if (choice == "0") {
            cout << "Da dang xuat!\n";
            return;
        }
        else {
            cout << "Lua chon khong hop le!\n";
        }
    }
}