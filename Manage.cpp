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

    cout << "Nhập mã nhân viên: ";
    getline(cin, NV_ID);
    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getNV_ID() == NV_ID) {
            cout << "Ma nhan vien da ton tai!\n";
            return;
        }
    }

    cout << "Nhập họ tên: ";
    getline(cin, fullName);

    cout << "Nhập ngày sinh: ";
    getline(cin, dateOfBirth);

    cout << "Nhập giới tính: ";
    getline(cin, gender);

    cout << "Nhập số điện thoại: ";
    getline(cin, phone);

    cout << "Nhập địa chỉ: ";
    getline(cin, address);

    cout << "Nhập mã phòng ban: ";
    getline(cin, PHG_ID);

    cout << "Nhập ngày vào làm: ";
    getline(cin, ngayVaoLam);

    cout << "Nhập trạng thái: ";
    getline(cin, status);

    Employee nv(NV_ID, fullName, dateOfBirth, gender, phone, address, PHG_ID, ngayVaoLam, status);

    listEmployee.push_back(nv);

    cout << "Thêm nhân viên thành công" << endl;
}


void Manage::removeEmployee() {
    string NV_ID;

    cout << "Nhập mã nhân viên cần xoá: ";
    getline(cin, NV_ID);

    // Tim nhan vien theo ma
    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getNV_ID() == NV_ID) {

            // Xoa nhan vien tai vi tri i
            listEmployee.erase(listEmployee.begin() + i);

            cout << "Xoá nhân viên thành công" << endl;
            return;
        }
    }

    cout << "Không tìm thấy nhân viên!!!" << endl;
}

void Manage::updateEmployee() {
    string NV_ID;

    cout << "Nhập mã nhân viên cần sửa: ";
    getline(cin, NV_ID);

    for (int i = 0; i < listEmployee.size(); i++) {
        if (listEmployee[i].getNV_ID() == NV_ID) {
            cout << "Tìm thấy nhân viên" << endl;

            int choose;
            cout << "===== MENU SỬA NHÂN VIÊN =====" << endl;
            cout << "1. Họ tên" << endl;
            cout << "2. Ngày sinh" << endl;
            cout << "3. Giới tính"<< endl;
            cout << "4. Số điện thoại" << endl;
            cout << "5. Địa chỉ" << endl;
            cout << "6. Mã phòng ban" << endl;
            cout << "7. Ngày vào làm" << endl;
            cout << "8. Trạng thái" << endl;
            cout << "0. Huỷ sửa" << endl;
            cout << "Nhập lựa chọn: ";
            cin >> choose;
            cin.ignore();

            switch (choose) {
                case 1: {
                    string fullName;

                    cout << "Nhập họ tên mới: ";
                    getline(cin, fullName);

                    if (fullName == "") {
                        cout << "Họ tên không được để trống!" << endl;
                        break;
                    }

                    listEmployee[i].setFullName(fullName);

                    cout << "Cập nhật họ tên thành công!" << endl;
                    break;
                }

                case 2: {
                    string dateOfBirth;

                    cout << "Nhập ngày sinh mới: ";
                    getline(cin, dateOfBirth);

                    if (dateOfBirth == "") {
                        cout << "Ngày sinh không được để trống!" << endl;
                        break;
                    }

                    listEmployee[i].setDateOfBirth(dateOfBirth);

                    cout << "Cập nhật ngày sinh thành công!" << endl;
                    break;
                }

                case 3: {
                    string gender;

                    cout << "Nhập giới tính mới: ";
                    getline(cin, gender);

                    if (gender == "") {
                        cout << "Giới tính không được để trống!" << endl;
                        break;
                    }

                    listEmployee[i].setGender(gender);

                    cout << "Cập nhật giới tính thành công!" << endl;
                    break;
                }

                case 4: {
                    string phone;

                    cout << "Nhập số điện thoại mới: ";
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
                        cout << "Ma phong ban khong duoc de trong!\n";
                        break;
                    }

                    listEmployee[i].setPHG_ID(PHG_ID);

                    cout << "Cap nhat ma phong ban thanh cong!\n";
                    break;
                }

                case 7: {
                    string ngayVaoLam;

                    cout << "Nhap ngay vao lam moi: ";
                    getline(cin, ngayVaoLam);

                    if (ngayVaoLam == "") {
                        cout << "Ngay vao lam khong duoc de trong!\n";
                        break;
                    }

                    listEmployee[i].setNgayVaoLam(ngayVaoLam);

                    cout << "Cap nhat ngay vao lam thanh cong!\n";
                    break;
                }

                case 8: {
                    string trangThai;

                    cout << "Nhap trang thai moi: ";
                    getline(cin, trangThai);

                    if (trangThai == "") {
                        cout << "Trang thai khong duoc de trong!\n";
                        break;
                    }

                    listEmployee[i].setStatus(trangThai);

                    cout << "Cap nhat trang thai thanh cong!\n";
                    break;
                }

                case 0:
                    cout << "Da huy sua thong tin!\n";
                    break;

                default:
                    cout << "Lua chon khong hop le!\n";
            }

            return;
        }
    }

    cout << "Khong tim thay ma nhan vien!\n";
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
        if (!getline(file, fullName) ||
            !getline(file, dateOfBirth) ||
            !getline(file, gender) ||
            !getline(file, phone) ||
            !getline(file, address) ||
            !getline(file, PHG_ID) ||
            !getline(file, ngayVaoLam) ||
            !getline(file, status)) {

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

    do {
        cout << "\n========== QUAN LY NHAN VIEN ==========\n";
        cout << "1. Them nhan vien\n";
        cout << "2. Xoa nhan vien\n";
        cout << "3. Sua thong tin nhan vien\n";
        cout << "4. Tim nhan vien theo ma\n";
        cout << "5. Tim nhan vien theo ten\n";
        cout << "6. Sap xep theo ma nhan vien\n";
        cout << "7. Sap xep theo ho ten\n";
        cout << "8. Sap xep theo phong ban\n";
        cout << "9. Loc nhan vien theo phong ban\n";
        cout << "10. Hien thi danh sach nhan vien\n";
        cout << "11. Luu danh sach vao file\n";
        cout << "12. Doc danh sach tu file\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";

        cin >> choose;
        cin.ignore();

        switch (choose) {
            case 1:
                addEmployee();
                break;

            case 2:
                removeEmployee();
                break;

            case 3:
                updateEmployee();
                break;

            case 4:
                seachID();
                break;

            case 5:
                seachName();
                break;

            case 6:
                arrangeID();
                break;

            case 7:
                arrangeName();
                break;

            case 8:
                arrangePHG_ID();
                break;

            case 9:
                filterPHG_ID();
                break;

            case 10:
                displayList();
                break;

            case 11:
                savefile();
                break;

            case 12:
                readfile();
                break;

            case 0:
                cout << "Da thoat chuong trinh!\n";
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while (choose != 0);
}