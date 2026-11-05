#include <fstream> //cho phép chương trình đọc và ghi dữ liệu vào tệp
#include <ctime>   //cho phép chương trình làm việc với thời gian
#include <iomanip> //cho phép chương trình định dạng dữ liệu khi nhập và xuất
#include <sstream> //cho phép chương trình chuyển đổi dữ liệu giữa các kiểu dữ liệu khác nhau
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
        cout << "Ma phong ban khong duoc de trong!" << endl;
        return;
    }

    if (PHG_ID.length() != 3) {
        cout << "Ma phong ban phai co 3 chu so!" << endl;
        return;
    }

    for (int i = 0; i < PHG_ID.length(); i++) {
        if (PHG_ID[i] < '0' || PHG_ID[i] > '9') {
            cout << "Ma phong ban chi duoc chua chu so!" << endl;
            return;
        }
    }

    cout << "Nhap gioi tinh (Nam/Nu): ";
    getline(cin, gender);

    if (gender != "Nam" && gender != "Nu") {
        cout << "Gioi tinh khong hop le!" << endl;
        return;
    }

    string genderCode;

    if (gender == "Nu") {
        genderCode = "02";
    }
    else {
        genderCode = "01";
    }

    // Tim so thu tu tiep theo trong phong ban
    int nextNumber = 11;

    for (int i = 0; i < listEmployee.size(); i++) {
        string id = listEmployee[i].getNV_ID();

        if (id.length() != 10) continue;

        string suf = id.substr(5);
        if (suf.find_first_not_of("0123456789") != string::npos) continue;

        nextNumber = max(nextNumber, stoi(suf) + 1);
    }

    string suffix = to_string(nextNumber);

    while (suffix.length() < 5) {
        suffix = "0" + suffix;
    }

    if (nextNumber > 99999) {
        cout << "Da vuot qua so luong ma nhan vien cho phep!" << endl;
        return;
    }

    NV_ID = PHG_ID + genderCode + suffix;

    cout << "Ma nhan vien duoc tao: " << NV_ID << endl;

    cout << "Nhap ho ten: ";
    getline(cin, fullName);

    if (fullName.empty()) {
        cout << "Ho ten khong duoc de trong!" << endl;
        return;
    }

    cout << "Nhap ngay sinh: ";
    getline(cin, dateOfBirth);

    cout << "Nhap so dien thoai: ";
    getline(cin, phone);

    cout << "Nhap dia chi: ";
    getline(cin, address);

    //Nhap ngay vao lam
    time_t now = time(0);
    tm* localTime = localtime(&now);
    stringstream ss;
    ss << put_time(localTime, "%d/%m/%Y");
    
    ngayVaoLam = ss.str();

    cout << "Nhap trang thai: ";
    getline(cin, status);

    if (status.empty()) {
        status = "Dang lam";
    }

    Employee nv(NV_ID, fullName, dateOfBirth, gender, phone, address, PHG_ID, ngayVaoLam, status);

    cout << endl << "===== XAC NHAN THONG TIN NHAN VIEN =====" << endl;
    nv.displayInfo();

    char choice;
    cout << endl << "Ban co chac chan muon them nhan vien nay khong? (Y/N): ";
    cin >> choice;
    cin.ignore();

    if (choice == 'Y' || choice == 'y') {
        listEmployee.push_back(nv);
        cout << "Them nhan vien thanh cong!" << endl;
    } else{
        cout << "Da huy them nhan vien!" << endl;
    }    
}

void Manage::removeEmployee() {
    string NV_ID;

    cout << "Nhap ma nhan vien can xoa: ";
    getline(cin, NV_ID);

    // Tim nhan vien theo ma
    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getNV_ID() == NV_ID) {

            cout << endl << "===== THONG TIN NHAN VIEN CAN XOA =====" << endl;
            listEmployee[i].displayInfo();

            char choice;

            cout << endl << "Ban co chac chan muon xoa nhan vien nay khong? (Y/N): ";
            cin >> choice;
            cin.ignore();

            if (choice == 'Y' || choice == 'y') {
                listEmployee.erase(listEmployee.begin() + i); // Xoa nhan vien tai vi tri i
                cout << "Xoa nhan vien thanh cong!" << endl;
            }
            else {
                cout << "Da huy xoa nhan vien!" << endl;
            }
            return;
        }
    }

    cout << "Khong tim thay ma nhan vien!" << endl;
}

void Manage::updateEmployee() {
    string NV_ID;

    cout << "Nhap ma nhan vien can sua: ";
    getline(cin, NV_ID);

    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getNV_ID() == NV_ID) {
            Employee newEmployee = listEmployee[i];

            cout << endl << "===== THONG TIN NHAN VIEN HIEN TAI =====" << endl;
            listEmployee[i].displayInfo();

            cout << endl << "Tim thay nhan vien!" << endl;

            string newFullName;
            string newDateOfBirth;
            string newPhone;
            string newAddress;
            string newPHG_ID;
            string newStatus;

            int choose;
            bool valid = true;

            cout << endl << "===== MENU SUA NHAN VIEN =====" << endl;
            cout << "1. Ho ten" << endl;
            cout << "2. Ngay sinh" << endl;
            cout << "3. So dien thoai" << endl;
            cout << "4. Dia chi" << endl;
            cout << "5. Ma phong ban" << endl;
            cout << "6. Trang thai" << endl;
            cout << "0. Huy sua" << endl;
            cout << "Nhap lua chon: ";

            cin >> choose;
            cin.ignore();

            switch (choose) {
                case 1: {
                    cout << "Nhap ho ten moi: ";
                    getline(cin, newFullName);

                    if (newFullName == "") {
                        cout << "Ho ten khong duoc de trong!" << endl;
                        valid = false;
                        break;
                    }
                    newEmployee.setFullName(newFullName);
                    break;
                }

                case 2: {
                    cout << "Nhap ngay sinh moi: ";
                    getline(cin, newDateOfBirth);

                    if (newDateOfBirth == "") {
                        cout << "Ngay sinh khong duoc de trong!" << endl;
                        valid = false;
                        break;
                    }
                    newEmployee.setDateOfBirth(newDateOfBirth);
                    break;
                }

                case 3: {
                    cout << "Nhap so dien thoai moi: ";
                    getline(cin, newPhone);

                    if (newPhone == "") {
                        cout << "So dien thoai khong duoc de trong!" << endl;
                        valid = false;
                        break;
                    }
                    newEmployee.setPhone(newPhone);
                    break;
                }

                case 4: {
                    cout << "Nhap dia chi moi: ";
                    getline(cin, newAddress);

                    if (newAddress == "") {
                        cout << "Dia chi khong duoc de trong!" << endl;
                        valid = false;
                        break;
                    }
                    newEmployee.setAddress(newAddress);
                    break;
                }

                case 5: {
                    cout << "Nhap ma phong ban moi: ";
                    getline(cin, newPHG_ID);

                    if (newPHG_ID == "") {
                        cout << "Ma phong ban khong duoc de trong!" << endl;
                        valid = false;
                        break;
                    }
                    newEmployee.setPHG_ID(newPHG_ID);
                    break;
                }

                case 6: {
                    cout << "Nhap trang thai moi: ";
                    getline(cin, newStatus);

                    if (newStatus == "") {
                        cout << "Trang thai khong duoc de trong!" << endl;
                        valid = false;
                        break;
                    }
                    newEmployee.setStatus(newStatus);
                    break;
                }

                case 0:
                    cout << "Da huy sua thong tin!" << endl;
                    return;

                default:
                    cout << "Lua chon khong hop le!" << endl;
                    return;
            }

            // Kiem tra du lieu nhap vao
            if (!valid) {
                cout << "Khong the cap nhat thong tin!" << endl;
                return;
            }

            // Hien thi thong tin sau khi sua
            cout << endl << "===== THONG TIN NHAN VIEN SAU KHI SUA =====" << endl;
            newEmployee.displayInfo();

            // Xac nhan cap nhat
            char confirm;

            cout << endl <<"Ban co chac chan muon cap nhat thong tin khong? (Y/N): ";
            cin >> confirm;
            cin.ignore();

            if (confirm == 'Y' || confirm == 'y') {
                listEmployee[i] = newEmployee;
                cout << "Cap nhat thong tin thanh cong!" << endl;
            }
            else {
                cout << "Da huy cap nhat thong tin!" << endl;
            }
            return;
        }
    }

    cout << "Khong tim thay ma nhan vien!" << endl;
}

void Manage::searchID() {
    string NV_ID;

    cout << "Nhap ma nhan vien can tim: ";
    getline(cin, NV_ID);

    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getNV_ID() == NV_ID) {
            cout << endl << "Tim thay nhan vien!" << endl;
            cout << "-------------------------" << endl;

            listEmployee[i].displayInfo();

            return;
        }
    }

    cout << "Khong tim thay ma nhan vien!" << endl;
}

void Manage::searchName() {
    string fullName;
    bool timThay = false;

    cout << "Nhap ho ten nhan vien can tim: ";
    getline(cin, fullName);

    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getFullName() == fullName) {
            cout << endl << "Tim thay nhan vien!" << endl;
            cout << "-------------------------" << endl;

            listEmployee[i].displayInfo();

            cout << "-------------------------" << endl;
            timThay = true;
        }
    }

    if (timThay == false) {
        cout << "Khong tim thay nhan vien!" << endl;
    }
}

void Manage::arrangeID() {
    for (size_t i = 0; i + 1 < listEmployee.size(); i++) {
        for (size_t j = i + 1; j < listEmployee.size(); j++) {
            if (listEmployee[i].getNV_ID() > listEmployee[j].getNV_ID()) {

                Employee temp = listEmployee[i];

                listEmployee[i] = listEmployee[j];

                listEmployee[j] = temp;
            }
        }
    }

    cout << "Sap xep theo ma nhan vien thanh cong!" << endl;
    displayList();
}

void Manage::arrangeName() {
    auto tachTen = [](string fullName) { //auto: tự suy luận kiểu dữ liệu của biến
        int posCuoi = fullName.find_last_of(' ');
        return fullName.substr(posCuoi + 1);
    };

    auto tachTenLot = [](string fullName) {
    int posDau = fullName.find(' ');
    int posCuoi = fullName.find_last_of(' ');

    if (posDau == posCuoi) {
            return string("");
        }
        return fullName.substr(posDau + 1, posCuoi - posDau - 1);
    };

    auto tachHo = [](string fullName) {
        int posDau = fullName.find(' ');

        return fullName.substr(0, posDau);
    };
    
    for (size_t i = 0; i + 1 < listEmployee.size(); i++) {
        for (size_t j = i + 1; j < listEmployee.size(); j++) {
            string ten1 = tachTen(listEmployee[i].getFullName());
            string ten2 = tachTen(listEmployee[j].getFullName());

            string tenLot1 = tachTenLot(listEmployee[i].getFullName());
            string tenLot2 = tachTenLot(listEmployee[j].getFullName());

            string ho1 = tachHo(listEmployee[i].getFullName());
            string ho2 = tachHo(listEmployee[j].getFullName());

            if (ten1 > ten2 || (ten1 == ten2 && tenLot1 > tenLot2) || (ten1 == ten2 && tenLot1 == tenLot2 && ho1 > ho2)) {
                Employee temp = listEmployee[i];
                listEmployee[i] = listEmployee[j];
                listEmployee[j] = temp;
            }
        }
    }

    cout << "Sap xep theo ho ten thanh cong!" << endl;
    displayList();
}

void Manage::arrangePHG_ID() {
    for (size_t i = 0; i + 1 < listEmployee.size(); i++) {
        for (size_t j = i + 1; j < listEmployee.size(); j++) {
            if (listEmployee[i].getPHG_ID() > listEmployee[j].getPHG_ID()) {

                Employee temp = listEmployee[i];
                listEmployee[i] = listEmployee[j];
                listEmployee[j] = temp;
            }
        }
    }

    cout << "Sap xep theo phong ban thanh cong!" << endl;
    displayList();
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
            cout << endl << "Thong tin nhan vien:" << endl;
            cout << "-------------------------" << endl;

            listEmployee[i].displayInfo();

            cout << "-------------------------" << endl;
            timThay = true;
        }
    }

    if (timThay == false) {
        cout << "Khong tim thay nhan vien thuoc phong ban nay!" << endl;
    }
}

void Manage::savefile() {
    ofstream file("Employee.txt"); //mở tệp để ghi. Nếu tệp chưa tồn tại, chương trình sẽ tạo tệp.

    if (!file.is_open()) {
        cout << "Khong mo duoc file de ghi!" << endl;
        return;
    }

    for (size_t i = 0; i < listEmployee.size(); i++) {
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

    if (!file) {
        cout << "Loi trong qua trinh ghi file!" << endl;
        return;
    }

    file.close();

    cout << "Luu danh sach nhan vien thanh cong!" << endl;
}

void Manage::readfile() {
    ifstream file("Employee.txt");

    if (!file.is_open()) {
        cout << "Khong mo duoc file de doc!" << endl;
        return;
    }

    // Xoa danh sach cu de tranh doc trung lap
    vector<Employee> tempList;
    bool docThanhCong = true;
    
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
            cout << "Du lieu trong file khong day du!" << endl;
            docThanhCong = false;
            break;
        }

        Employee nv(NV_ID, fullName, dateOfBirth, gender, phone, address, PHG_ID, ngayVaoLam, status);

        tempList.push_back(nv);
    }

    file.close();

    if (docThanhCong) {
        listEmployee = tempList;
        cout << "Doc danh sach nhan vien thanh cong!" << endl;
    }
}

void Manage::displayList() {
    if (listEmployee.empty()) {
        cout << "Danh sach nhan vien rong!" << endl;
        return;
    }

    cout << left
         << setw(6)  << "STT"
         << setw(25) << "Ho ten"
         << setw(15) << "Ngay sinh"
         << setw(15) << "Ma NV"
         << setw(12) << "Ma PB"
         << setw(16) << "Ngay vao lam"
         << setw(15) << "Trang thai"
         << endl;

    cout << string(105, '-') << endl;

    for (int i = 0; i < listEmployee.size(); i++) {
        cout << left
             << setw(6)  << i + 1
             << setw(25) << listEmployee[i].getFullName()
             << setw(15) << listEmployee[i].getDateOfBirth()
             << setw(15) << listEmployee[i].getNV_ID()
             << setw(12) << listEmployee[i].getPHG_ID()
             << setw(16) << listEmployee[i].getNgayVaoLam()
             << setw(15) << listEmployee[i].getStatus()
             << endl;
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
        cout << "0. Thoat" << endl;
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
                        searchID();
                        break;

                    case 2:
                        searchName();
                        break;

                    case 3:
                        filterPHG_ID();
                        break;

                    case 4:
                        displayList();
                        break;

                    case 0:
                    cout << "Quay lai menu chinh!" << endl;
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
                        cout << "Quay lai menu chinh!" << endl;
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
                        cout << "Quay lai menu chinh!" << endl;
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
                        cout << "Quay lai menu chinh!" << endl;
                        break;

                    default:
                        cout << "Lua chon khong hop le!" << endl;
                    }
                }while (subChoose != 0);
                break;

            case 0:
                cout << "Da thoat chuong trinh!" << endl;
                break;

            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (choose != 0);
}

bool Manage::displayEmployeeByID(string NV_ID) {
    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getNV_ID() == NV_ID) {
            cout << endl << "===== THONG TIN CA NHAN =====" << endl;
            listEmployee[i].displayInfo();
            return true;
        }
    }
    cout << "Khong tim thay thong tin nhan vien!" << endl;
    return false;
}
