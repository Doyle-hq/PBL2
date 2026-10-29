#include <fstream> //cho phép chương trình đọc và ghi dữ liệu vào tệp
#include "Manage.h"
Manage::Manage() : Person(){
}

// Constructor co tham so
Manage::Manage(string fullName, string dateOfBirth, string gender, string phone, string address) : Person(fullName, dateOfBirth, gender, phone, address) {
}

void Manage::addEmployee() {
    string NV_ID;
    string fullName;
    string dateOfBirth;
    string gender;
    string phone;
    string address;
    string PHG_ID;
    string ngayVaoLam;
    string status;

    cout << "Nhap ma phong ban: ";
    getline(cin, PHG_ID);

    if (PHG_ID.empty()) {
        cout << "Ma phong ban khong duoc de trong!\n";
        return;
    }

    // Tim so thu tu tiep theo trong phong ban
    int nextNumber = 1;

    for (int i = 0; i < listEmployee.size(); i++) {
        string currentID = listEmployee[i].getNV_ID();

        if (listEmployee[i].getPHG_ID() != PHG_ID){
            continue;
        }

        if (currentID.length() <= PHG_ID.length()) {
            continue;
        }

        if (currentID.substr(0, PHG_ID.length()) != PHG_ID) {
            continue;
        }

        string suffix = currentID.substr(PHG_ID.length());
        bool valid = true;

        for (int j = 0; j < suffix.length(); j++) {
            if (suffix[j] < '0' || suffix[j] > '9') {
                valid = false;
                break;
            }
        }

        if (valid && !suffix.empty()) {
            try {
                int number = stoi(suffix);

                if (number >= nextNumber) {
                    nextNumber = number + 1;
                }
            }
            catch (...) {
                cout << "Ma nhan vien trong danh sach khong hop le!\n";
                return;
            }
        }
    }

    string suffix = to_string(nextNumber);

    while (suffix.length() < 3) {
        suffix = "0" + suffix;
    }

    NV_ID = PHG_ID + suffix;

    cout << "Ma nhan vien duoc tao: " << NV_ID << endl;

    cout << "Nhap ho ten: ";
    getline(cin, fullName);

    if (fullName.empty()) {
        cout << "Ho ten khong duoc de trong!\n";
        return;
    }

    cout << "Nhap ngay sinh: ";
    getline(cin, dateOfBirth);

    cout << "Nhap gioi tinh: ";
    getline(cin, gender);

    cout << "Nhap so dien thoai: ";
    getline(cin, phone);

    cout << "Nhap dia chi: ";
    getline(cin, address);

    cout << "Nhap ngay vao lam: ";
    getline(cin, ngayVaoLam);

    cout << "Nhap trang thai: ";
    getline(cin, status);

    if (status.empty()) {
        status = "Dang lam";
    }

    Employee nv(NV_ID, fullName, dateOfBirth, gender, phone, address, PHG_ID, ngayVaoLam, status);

    listEmployee.push_back(nv);

    cout << "Them nhan vien thanh cong!\n";
}



void Manage::removeEmployee() {
    string NV_ID;

    cout << "Nhap ma nhan vien can xoa: ";
    getline(cin, NV_ID);

    // Tim nhan vien theo ma
    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getNV_ID() == NV_ID) {

            // Xoa nhan vien tai vi tri i
            listEmployee.erase(listEmployee.begin() + i);

            cout << "Xoa nhan vien thanh cong!\n";
            return;
        }
    }

    cout << "Khong tim thay ma nhan vien!\n";
}

void Manage::updateEmployee() {
    string NV_ID;

    cout << "Nhap ma nhan vien can sua: ";
    getline(cin, NV_ID);

    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getNV_ID() == NV_ID) {
            cout << "Tim thay nhan vien!\n";

            int choose;

            cout << endl << "===== MENU SUA NHAN VIEN =====" << endl;
            cout << "1. Ho ten\n";
            cout << "2. Ngay sinh\n";
            cout << "3. Gioi tinh\n";
            cout << "4. So dien thoai\n";
            cout << "5. Dia chi\n";
            cout << "6. Ma phong ban\n";
            cout << "7. Ngay vao lam\n";
            cout << "8. Trang thai\n";
            cout << "0. Huy sua\n";
            cout << "Nhap lua chon: ";
            cin >> choose;
            cin.ignore();

            switch (choose) {
                case 1: {
                    string fullName;

                    cout << "Nhap ho ten moi: ";
                    getline(cin, fullName);

                    if (fullName == "") {
                        cout << "Ho ten khong duoc de trong!\n";
                        break;
                    }

                    listEmployee[i].setFullName(fullName);

                    cout << "Cap nhat ho ten thanh cong!\n";
                    break;
                }

                case 2: {
                    string dateOfBirth;

                    cout << "Nhap ngay sinh moi: ";
                    getline(cin, dateOfBirth);

                    if (dateOfBirth == "") {
                        cout << "Ngay sinh khong duoc de trong!\n";
                        break;
                    }

                    listEmployee[i].setDateOfBirth(dateOfBirth);

                    cout << "Cap nhat ngay sinh thanh cong!\n";
                    break;
                }

                case 3: {
                    string gender;

                    cout << "Nhap gioi tinh moi: ";
                    getline(cin, gender);

                    if (gender == "") {
                        cout << "Gioi tinh khong duoc de trong!\n";
                        break;
                    }

                    listEmployee[i].setGender(gender);

                    cout << "Cap nhat gioi tinh thanh cong!\n";
                    break;
                }

                case 4: {
                    string phone;

                    cout << "Nhap so dien thoai moi: ";
                    getline(cin, phone);

                    if (phone == "") {
                        cout << "So dien thoai khong duoc de trong!\n";
                        break;
                    }

                    listEmployee[i].setPhone(phone);

                    cout << "Cap nhat so dien thoai thanh cong!\n";
                    break;
                }

                case 5: {
                    string address;

                    cout << "Nhap dia chi moi: ";
                    getline(cin, address);

                    if (address == "") {
                        cout << "Dia chi khong duoc de trong!\n";
                        break;
                    }

                    listEmployee[i].setAddress(address);

                    cout << "Cap nhat dia chi thanh cong!\n";
                    break;
                }

                case 6: {
                    string PHG_ID;

                    cout << "Nhap ma phong ban moi: ";
                    getline(cin, PHG_ID);

                    if (PHG_ID == "") {
                        cout << "Ma phong ban khong duoc de trong!" << endl;
                        break;
                    }

                    listEmployee[i].setPHG_ID(PHG_ID);

                    cout << "Cap nhat ma phong ban thanh cong!" << endl;
                    break;
                }

                case 7: {
                    string ngayVaoLam;

                    cout << "Nhap ngay vao lam moi: ";
                    getline(cin, ngayVaoLam);

                    if (ngayVaoLam == "") {
                        cout << "Ngay vao lam khong duoc de trong!" << endl;
                        break;
                    }

                    listEmployee[i].setNgayVaoLam(ngayVaoLam);

                    cout << "Cap nhat ngay vao lam thanh cong!" << endl;
                    break;
                }

                case 8: {
                    string trangThai;

                    cout << "Nhap trang thai moi: ";
                    getline(cin, trangThai);

                    if (trangThai == "") {
                        cout << "Trang thai khong duoc de trong!" << endl;
                        break;
                    }

                    listEmployee[i].setStatus(trangThai);

                    cout << "Cap nhat trang thai thanh cong!" << endl;
                    break;
                }

                case 0:
                    cout << "Da huy sua thong tin!" << endl;
                    break;

                default:
                    cout << "Lua chon khong hop le!" << endl;
            }

            return;
        }
    }

    cout << "Khong tim thay ma nhan vien!" << endl;
}

void Manage::seachID() {
    string NV_ID;

    cout << "Nhap ma nhan vien can tim: ";
    getline(cin, NV_ID);

    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getNV_ID() == NV_ID) {
            cout << "\nTim thay nhan vien!\n";
            cout << "-------------------------\n";

            listEmployee[i].displayInfo();

            return;
        }
    }

    cout << "Khong tim thay ma nhan vien!\n";
}

void Manage::seachName() {
    string fullName;
    bool timThay = false;

    cout << "Nhap ho ten nhan vien can tim: ";
    getline(cin, fullName);

    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getFullName() == fullName) {
            cout << "\nTim thay nhan vien!\n";
            cout << "-------------------------\n";

            listEmployee[i].displayInfo();

            cout << "-------------------------\n";
            timThay = true;
        }
    }

    if (timThay == false) {
        cout << "Khong tim thay nhan vien!\n";
    }
}

void Manage::arrangeID() {
    for (int i = 0; i < listEmployee.size() - 1; i++) {
        for (int j = i + 1; j < listEmployee.size(); j++) {
            if (listEmployee[i].getNV_ID() > listEmployee[j].getNV_ID()) {

                Employee temp = listEmployee[i];

                listEmployee[i] = listEmployee[j];

                listEmployee[j] = temp;
            }
        }
    }

    cout << "Sap xep theo ma nhan vien thanh cong!\n";
}

void Manage::arrangeName() {
    for (int i = 0; i < listEmployee.size() - 1; i++) {
        for (int j = i + 1; j < listEmployee.size(); j++) {
            if (listEmployee[i].getFullName() >
                listEmployee[j].getFullName()) {

                Employee temp = listEmployee[i];

                listEmployee[i] = listEmployee[j];

                listEmployee[j] = temp;
            }
        }
    }

    cout << "Sap xep theo ho ten thanh cong!\n";
}

void Manage::arrangePHG_ID() {
    for (int i = 0; i < listEmployee.size() - 1; i++) {
        for (int j = i + 1; j < listEmployee.size(); j++) {
            if (listEmployee[i].getPHG_ID() >
                listEmployee[j].getPHG_ID()) {

                Employee temp = listEmployee[i];

                listEmployee[i] = listEmployee[j];

                listEmployee[j] = temp;
            }
        }
    }

    cout << "Sap xep theo phong ban thanh cong!\n";
}

// Loc nhan vien theo phong ban
void Manage::filterPHG_ID() {
    string PHG_ID;
    bool timThay = false;

    cout << "Nhap ma phong ban can loc: ";
    getline(cin, PHG_ID);

    // Duyet danh sach nhan vien
    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getPHG_ID() == PHG_ID) {
            cout << "\nThong tin nhan vien:\n";
            cout << "-------------------------\n";

            listEmployee[i].displayInfo();

            cout << "-------------------------\n";
            timThay = true;
        }
    }

    if (timThay == false) {
        cout << "Khong tim thay nhan vien thuoc phong ban nay!\n";
    }
}

void Manage::savefile() {
    ofstream file("Employee.txt"); //mở tệp để ghi. Nếu tệp chưa tồn tại, chương trình sẽ tạo tệp.

    if (!file.is_open()) {
        cout << "Khong mo duoc file de ghi!\n";
        return;
    }

    for (int i = 0; i < listEmployee.size(); i++) {
        file << listEmployee[i].getNV_ID() << '\n';
        file << listEmployee[i].getFullName() << '\n';
        file << listEmployee[i].getDateOfBirth() << '\n';
        file << listEmployee[i].getGender() << '\n';
        file << listEmployee[i].getPhone() << '\n';
        file << listEmployee[i].getAddress() << '\n';
        file << listEmployee[i].getPHG_ID() << '\n';
        file << listEmployee[i].getNgayVaoLam() << '\n';
        file << listEmployee[i].getStatus() << '\n';
    }

    file.close();

    cout << "Luu danh sach nhan vien thanh cong!\n";
}

void Manage::readfile() {
    ifstream file("Employee.txt");

    if (!file.is_open()) {
        cout << "Khong mo duoc file de doc!\n";
        return;
    }

    // Xoa danh sach cu de tranh doc trung lap
    listEmployee.clear();

    string NV_ID;
    string fullName;
    string dateOfBirth;
    string gender;
    string phone;
    string address;
    string PHG_ID;
    string ngayVaoLam;
    string status;

    while (getline(file, NV_ID)) {
        if (!getline(file, fullName) || !getline(file, dateOfBirth) || !getline(file, gender) || !getline(file, phone) || !getline(file, address) || !getline(file, PHG_ID) || !getline(file, ngayVaoLam) || !getline(file, status)) {

            cout << "Du lieu trong file khong day du!\n";
            break;
        }

        Employee nv(NV_ID, fullName, dateOfBirth, gender, phone, address, PHG_ID, ngayVaoLam, status);

        listEmployee.push_back(nv);
    }

    file.close();

    cout << "Doc danh sach nhan vien thanh cong!\n";
}

void Manage::displayList() {
    if (listEmployee.empty()) {
        cout << "Danh sach nhan vien rong!\n";
        return;
    }

    for (int i = 0; i < listEmployee.size(); i++) {
        cout << "\n===== NHAN VIEN " << i + 1 << " =====\n";

        listEmployee[i].displayInfo();

        cout << "-------------------------\n";
    }
}

void Manage::menu() {
    int choose;
    int subChoose;

    do {
        cout << "========== QUAN LY NHAN VIEN ==========" << endl;
        cout << "1. Tra cuu va hien thi" << endl;
        cout << "2. Cap nhap danh sach" << endl;
        cout << "3. Sap xep danh sach" << endl;
        cout << "4. Xu ly tap tin" << endl;
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";

        cin >> choose;
        cin.ignore();        

        switch (choose) {
            case 1:
                do{
                    cout << endl << "========== TRA CUU & HIEN THI ==========" << endl;
                    cout << "1. Tra cuu theo ma" << endl;
                    cout << "2. Tra cuu theo ten" << endl;
                    cout << "3. Tra cuu theo phong ban" << endl;
                    cout << "4. Hien thi danh sach nhan vien" << endl;
                    cout << "0. Thoat" << endl;
                    cout << "Nhap lua chon: ";
                    cin >> subChoose;
                    cin.ignore();

                    switch (subChoose)
                    {
                    case 1:
                        seachID();
                        break;

                    case 2:
                        seachName();
                        break;

                    case 3:
                        filterPHG_ID();
                        break;

                    case 4:
                        displayList();
                        break;

                    case 0:
                    cout << "Da thoat chuong trinh!" << endl;
                    break;

                    default:
                        cout << "Lua chon khong hop le!" << endl;
                    }
                }while (subChoose != 0);
                break;

            case 2:
                do{
                    cout << endl << "========== CAP NHAP DANH SACH ==========" << endl;
                    cout << "1. Them nhan vien" << endl;
                    cout << "2. Xoa nhan vien" << endl;
                    cout << "3. Cap nhap" << endl;
                    cout << "0. Thoat" << endl;
                    cout << "Nhap lua chon: ";
                    cin >> subChoose;
                    cin.ignore();

                    switch (subChoose)
                    {
                    case 1:
                        addEmployee();
                        break;

                    case 2:
                        removeEmployee();
                        break;

                    case 3:
                        updateEmployee();
                        break;

                    case 0:
                        cout << "Da thoat chuong trinh!" << endl;
                        break;

                    default:
                        cout << "Lua chon khong hop le!" << endl;
                    }
                }while (subChoose != 0);
                break;

            case 3:
                do{
                    cout << endl << "========== SAP XEP DANH SACH ==========" << endl;
                    cout << "1. Sap xep theo ma" << endl;
                    cout << "2. Sap xep theo ten" << endl;
                    cout << "3. Sap xep theo phong" << endl;
                    cout << "0. Thoat" << endl;
                    cout << "Nhap lua chon: ";
                    cin >> subChoose;
                    cin.ignore();

                    switch (subChoose)
                    {
                    case 1:
                        arrangeID();
                        break;

                    case 2:
                        arrangeName();
                        break;

                    case 3:
                        arrangePHG_ID();
                        break;

                    case 0:
                        cout << "Da thoat chuong trinh!" << endl;
                        break;

                    default:
                        cout << "Lua chon khong hop le!" << endl;
                    }
                }while (subChoose != 0);
                break;

            case 4:
                do{
                    cout << endl << "========== XU LY TAP TIN ==========" << endl;
                    cout << "1. Luu file" << endl;
                    cout << "2. Doc file" << endl;
                    cout << "0. Thoat" << endl;
                    cout << "Nhap lua chon: ";
                    cin >> subChoose;
                    cin.ignore();

                    switch (subChoose)
                    {
                    case 1:
                        savefile();
                        break;

                    case 2:
                        readfile();
                        break;

                    case 0:
                        cout << "Da thoat chuong trinh!" << endl;
                        break;

                    default:
                        cout << "Lua chon khong hop le!" << endl;
                    }
                }while (subChoose != 0);
                break;

            case 0:
                cout << "Da thoat chuong trinh!\n";
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while (choose != 0);
}


bool Manage::displayEmployeeByID(string NV_ID) {
    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getNV_ID() == NV_ID) {
            cout << "\n===== THONG TIN CA NHAN =====\n";
            listEmployee[i].displayInfo();
            return true;
        }
    }

    cout << "Khong tim thay thong tin nhan vien!\n";
    return false;
}
