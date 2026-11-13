#include "Menu.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
using namespace std;

// Font giao dien
static Font UI_FONT = {0};

// Tao danh sach ky tu can hien thi,
// bao gom cac ky tu tieng Viet co dau.
static vector<int> createVietnameseCodepoints() {
    vector<int> codepoints;

    for (int i = 32; i <= 126; i++)
        codepoints.push_back(i);

    for (int i = 160; i <= 255; i++)
        codepoints.push_back(i);

    for (int i = 258; i <= 382; i++)
        codepoints.push_back(i);

    for (int i = 7840; i <= 7929; i++)
        codepoints.push_back(i);

    return codepoints;
}

// Dung font Unicode cho tat ca DrawText trong file
#define DrawText(text, x, y, size, color) \
    DrawTextEx(UI_FONT, text, Vector2{(float)(x), (float)(y)}, \
    (float)(size), 1.0f, color)

// MAU SAC

static const Color PRIMARY = {35, 105, 180, 255};
static const Color PRIMARY_DARK = {25, 75, 135, 255};
static const Color BACKGROUND = {245, 248, 252, 255};
static const Color SIDEBAR = {255, 255, 255, 255};
static const Color TEXT_COLOR = {40, 50, 65, 255};
static const Color SUBTEXT = {100, 110, 125, 255};
static const Color BORDER_COLOR = {210, 220, 232, 255};
static const Color SUCCESS_COLOR = {35, 150, 95, 255};
static const Color ERROR_COLOR = {210, 65, 65, 255};

// KHOI TAO
Menu::Menu() {
    currentScreen = LOGIN;

    loginID = "";
    loginPassword = "";
    profilePhone = "";
    profileAddress = "";

    showPassword = false;
    isMessageError = false;
    isEditingProfile = false;

    activeInput = -1;
    selectedMenu = 0;
    selectedEmployeeIndex = -1;
    scrollOffset = 0;

    showConfirm = false;
    confirmAction = 0;

    message = "";
    
}

// HAM HO TRO
bool Menu::isMouseInside(Rectangle rect) {
    return CheckCollisionPointRec(GetMousePosition(), rect);
}

bool Menu::button(const char* text, Rectangle rect, Color color){
    bool hovered = isMouseInside(rect);

    Color drawColor = color;

    if(hovered){
        drawColor ={
            (unsigned char)(color.r * 0.85f),
            (unsigned char)(color.g * 0.85f),
            (unsigned char)(color.b * 0.85f),
            color.a
        };
    }

    DrawRectangleRounded(rect, 0.15f, 8, drawColor);

    int textWidth = (int)MeasureTextEx(UI_FONT, text, 19, 1.0f).x;

    DrawText(text, rect.x + (rect.width - textWidth) / 2, rect.y + (rect.height - 19) / 2, 19, WHITE);

    return hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void Menu::drawTextLabel(const string& text, int x, int y, int fontSize, Color color){
    DrawText(text.c_str(), x, y, fontSize, color);
}

void Menu::setMessage(const string& text, bool isError) {
    message = text;
    isMessageError = isError;
}

void Menu::openConfirm(const string& title, const string& content, int action){
    confirmTitle = title;
    confirmContent = content;
    confirmAction = action;
    showConfirm = true;
}

void Menu::resetEmployeeForm(){
    inputNV_ID = "";
    inputName = "";
    inputDOB = "";
    inputGender = "";
    inputPhone = "";
    inputAddress = "";
    inputDepartment = "";
    activeInput = -1;
}

void Menu::loadEmployees() {
    employees = employeeService.getAllEmployees();
}

// O NHAP LIEU
bool Menu::inputBox(const char* label, Rectangle rect, string& value, int inputID, bool password) {
    DrawText(label, rect.x, rect.y - 30, 18, TEXT_COLOR);

    bool hovered = isMouseInside(rect);

    if(hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        activeInput = inputID;
    }

    Color borderColor =
        (activeInput == inputID) ? PRIMARY : BORDER_COLOR;

    DrawRectangleRounded(rect, 0.12f, 8, WHITE);
    DrawRectangleRoundedLines(rect, 0.12f, 8, borderColor);

    string displayValue = value;

    if (displayValue.empty() && activeInput != inputID) {
        displayValue = "Nhap thong tin...";
        DrawText(
            displayValue.c_str(),
            rect.x + 12,
            rect.y + 13,
            17,
            SUBTEXT
        );
    }
    else {
        DrawText(
            displayValue.c_str(),
            rect.x + 15,
            rect.y + 12,
            19,
            TEXT_COLOR
        );
    }

    if (activeInput == inputID) {
        int key = GetCharPressed();

        while (key > 0) {
            if (key >= 32 && key <= 125 && value.length() < 100) {
                value += (char)key;
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !value.empty()) {
            value.pop_back();
        }
    }

    return activeInput == inputID;
}

// =====================================================
// GIAO DIEN DANG NHAP
// =====================================================

void Menu::drawLogin() {
    ClearBackground(BACKGROUND);

    DrawRectangle(0, 0, 570, 750, PRIMARY_DARK);

    DrawText("PBL2", 100, 210, 55, WHITE);
    DrawText("EMPLOYEE MANAGEMENT", 100, 285, 24, WHITE);
    DrawText("HE THONG QUAN LY NHAN VIEN", 100, 330, 18, RAYWHITE);

    DrawText("Quan ly nhan su thong minh", 100, 410, 20, WHITE);

    DrawRectangleRounded(
        {650, 120, 430, 500},
        0.04f,
        10,
        WHITE
    );

    DrawText("DANG NHAP", 750, 175, 30, PRIMARY_DARK);
    DrawText("Vui long dang nhap vao he thong", 700, 220, 16, SUBTEXT);

    inputBox(
        "Ma dang nhap",
        {700, 290, 330, 48},
        loginID,
        1
    );

    inputBox(
        "Mat khau",
        {700, 390, 330, 48},
        loginPassword,
        2,
        false
    );

    if (button("DANG NHAP", {700, 490, 330, 50}, PRIMARY)) {
        handleLogin();
    }

    if (!message.empty()) {
        DrawText(
            message.c_str(),
            700,
            570,
            15,
            isMessageError ? ERROR_COLOR : SUCCESS_COLOR
        );
    }

    DrawText(
        "PBL2 - Employee Management System",
        700,
        650,
        14,
        SUBTEXT
    );
}

void Menu::handleLogin() {
    if (loginID.empty() || loginPassword.empty()) {
        setMessage("Vui long nhap day du thong tin!", true);
        return;
    }

    string result;

    if (!accountService.login(
        loginID,
        loginPassword,
        loginAccount,
        result
    )) {
        setMessage(result, true);
        return;
    }

    setMessage(result);

    activeInput = -1;
    loginPassword = "";

    if (loginAccount.getRole() == "manager") {
        currentScreen = MANAGER_DASHBOARD;
        loadEmployees();
    }
    else {
        currentScreen = EMPLOYEE_DASHBOARD;
    }
}

// =====================================================
// HEADER VA SIDEBAR
// =====================================================

void Menu::drawHeader() {
    DrawRectangle(230, 0, 970, 75, WHITE);

    DrawText(
        "EMPLOYEE MANAGEMENT SYSTEM",
        265,
        25,
        22,
        PRIMARY_DARK
    );

    DrawText(
        loginAccount.getNV_ID().c_str(),
        1030,
        30,
        16,
        TEXT_COLOR
    );

    DrawLine(230, 75, 1200, 75, BORDER_COLOR);
}

void Menu::drawSidebar() {
    DrawRectangle(0, 0, 230, 750, SIDEBAR);

    DrawText("PBL2", 30, 25, 35, PRIMARY);
    DrawText("QUAN LY NHAN VIEN", 30, 65, 13, SUBTEXT);

    DrawLine(20, 100, 210, 100, BORDER_COLOR);

    const char* menuItems[] = {
        "Tong quan",
        "Danh sach nhan vien",
        "Them nhan vien",
        "Khoa tai khoan",
        "Mo khoa tai khoan",
        "Xac nhan nghi viec"
    };

    for (int i = 0; i < 6; i++) {
        Rectangle rect = {
            15,
            (float)(125 + i * 65),
            200,
            48
        };

        Color color = (selectedMenu == i)
            ? PRIMARY
            : SIDEBAR;

        DrawRectangleRounded(rect, 0.12f, 8, color);

        Color textColor = (selectedMenu == i)
            ? WHITE
            : TEXT_COLOR;

        DrawText(
            menuItems[i],
            rect.x + 15,
            rect.y + 14,
            16,
            textColor
        );

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            isMouseInside(rect)) {

            selectedMenu = i;

            if (i == 0) {
                currentScreen = MANAGER_DASHBOARD;
            }
            else if (i == 1) {
                currentScreen = EMPLOYEE_LIST;
                loadEmployees();
            }
            else if (i == 2) {
                resetEmployeeForm();
                currentScreen = EMPLOYEE_ADD;
            }
            else if (i == 3) {
                inputNV_ID = "";
                currentScreen = ACCOUNT_LOCK;
            }
            else if (i == 4) {
                inputNV_ID = "";
                currentScreen = ACCOUNT_UNLOCK;
            }
            else if (i == 5) {
                inputNV_ID = "";
                currentScreen = EMPLOYEE_RESIGN;
            }
        }
    }

    if (button("DANG XUAT", {20, 680, 190, 45}, ERROR_COLOR)) {
        currentScreen = LOGIN;
        loginID = "";
        loginPassword = "";
        message = "";
        activeInput = -1;
    }
}

// =====================================================
// DASHBOARD QUAN LY
// =====================================================

void Menu::drawManagerDashboard() {
    ClearBackground(BACKGROUND);

    drawSidebar();
    drawHeader();

    DrawText("TONG QUAN", 265, 110, 28, TEXT_COLOR);

    loadEmployees();

    int total = (int)employees.size();
    int working = 0;
    int resigned = 0;

    for (const Employee& e : employees) {
        if (e.getStatus() == "Da nghi viec") {
            resigned++;
        }
        else {
            working++;
        }
    }

    DrawRectangleRounded({265, 175, 260, 130}, 0.08f, 8, WHITE);
    DrawText("TONG NHAN VIEN", 285, 195, 17, SUBTEXT);
    DrawText(TextFormat("%d", total), 285, 235, 38, PRIMARY);

    DrawRectangleRounded({550, 175, 260, 130}, 0.08f, 8, WHITE);
    DrawText("DANG LAM VIEC", 570, 195, 17, SUBTEXT);
    DrawText(TextFormat("%d", working), 570, 235, 38, SUCCESS_COLOR);

    DrawRectangleRounded({835, 175, 260, 130}, 0.08f, 8, WHITE);
    DrawText("DA NGHI VIEC", 855, 195, 17, SUBTEXT);
    DrawText(TextFormat("%d", resigned), 855, 235, 38, ERROR_COLOR);

    DrawText("CHUC NANG QUAN LY", 265, 350, 22, TEXT_COLOR);

    if (button("DANH SACH NHAN VIEN",
        {265, 405, 250, 65}, PRIMARY)) {

        currentScreen = EMPLOYEE_LIST;
        loadEmployees();
    }

    if (button("THEM NHAN VIEN",
        {550, 405, 250, 65}, SUCCESS_COLOR)) {

        resetEmployeeForm();
        currentScreen = EMPLOYEE_ADD;
    }

    if (button("KHOA TAI KHOAN",
        {835, 405, 250, 65}, ERROR_COLOR)) {

        inputNV_ID = "";
        currentScreen = ACCOUNT_LOCK;
    }
}

// =====================================================
// DANH SACH NHAN VIEN
// =====================================================

void Menu::drawEmployeeTable(
    const vector<Employee>& data
) {
    DrawRectangleRounded(
        {255, 240, 925, 430},
        0.03f,
        8,
        WHITE
    );

    const char* headers[] = {
        "NV_ID",
        "HO TEN",
        "NGAY SINH",
        "GIOI TINH",
        "PHG_ID",
        "TRANG THAI"
    };

    int x[] = {275, 390, 610, 750, 840, 940};

    for (int i = 0; i < 6; i++) {
        DrawText(headers[i], x[i], 195, 14, SUBTEXT);
    }

    DrawLine(270, 225, 1160, 225, BORDER_COLOR);

    int start = scrollOffset;
    int end = min((int)data.size(), start + 10);

    for (int i = start; i < end; i++) {
        const Employee& e = data[i];

        int y = 245 + (i - start) * 40;

        DrawText(e.getNV_ID().c_str(), 275, y, 14, TEXT_COLOR);
        DrawText(e.getFullName().c_str(), 390, y, 14, TEXT_COLOR);
        DrawText(e.getDateOfBirth().c_str(), 610, y, 14, TEXT_COLOR);
        DrawText(e.getGender().c_str(), 750, y, 14, TEXT_COLOR);
        DrawText(e.getPHG_ID().c_str(), 840, y, 14, TEXT_COLOR);

        Color statusColor =
            (e.getStatus() == "Da nghi viec")
            ? ERROR_COLOR
            : SUCCESS_COLOR;

        DrawText(e.getStatus().c_str(), 940, y, 14, statusColor);

        Rectangle row = {
            265,
            (float)(y - 5),
            900,
            32
        };

        if (isMouseInside(row) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            selectedEmployee = e;
            selectedEmployeeIndex = i;
            currentScreen = EMPLOYEE_DETAIL;
        }

        DrawLine(270, y + 25, 1160, y + 25, BORDER_COLOR);
    }

    DrawText(
        TextFormat("Tong so: %d nhan vien", (int)data.size()),
        275,
        650,
        15,
        SUBTEXT
    );
}

void Menu::drawEmployeeList() {
    ClearBackground(BACKGROUND);

    drawSidebar();
    drawHeader();

    DrawText("DANH SACH NHAN VIEN", 265, 105, 28, TEXT_COLOR);

    inputBox(
        "Tim kiem theo ten",
        {265, 175, 280, 45},
        searchKeyword,
        10
    );

    if (button("TIM KIEM", {565, 175, 110, 45}, PRIMARY)) {
        activeInput = -1;
        searchEmployee();
    }

    if (button("SAP XEP MA", {690, 175, 120, 45}, PRIMARY)) {
        sortEmployees(1);
    }

    if (button("SAP XEP TEN", {825, 175, 130, 45}, PRIMARY)) {
        sortEmployees(2);
    }

    if (button("SAP XEP PHONG", {970, 175, 160, 45}, PRIMARY)) {
        sortEmployees(3);
    }

    drawEmployeeTable(employees);

    float wheel = GetMouseWheelMove();

    if (wheel > 0 && scrollOffset > 0) {
        scrollOffset--;
    }

    if (wheel < 0 && scrollOffset + 10 < (int)employees.size()) {
        scrollOffset++;
    }

    if (button("QUAY LAI", {990, 690, 150, 40}, PRIMARY)) {
        currentScreen = MANAGER_DASHBOARD;
    }
}

void Menu::searchEmployee() {
    employees = employeeService.searchByName(searchKeyword);
    scrollOffset = 0;
}

void Menu::sortEmployees(int type) {
    if (type == 1) {
        employees = employeeService.sortByID();
    }
    else if (type == 2) {
        employees = employeeService.sortByName();
    }
    else if (type == 3) {
        employees = employeeService.sortByDepartment();
    }

    scrollOffset = 0;
}

void Menu::filterEmployees() {
    employees = employeeService.filterByDepartment(inputDepartment);
    scrollOffset = 0;
}

// =====================================================
// FORM THEM / SUA NHAN VIEN
// =====================================================

void Menu::drawEmployeeForm() {
    ClearBackground(BACKGROUND);

    drawSidebar();
    drawHeader();

    bool isAdd = (currentScreen == EMPLOYEE_ADD);

    DrawText(
        isAdd ? "THEM NHAN VIEN" : "CAP NHAT NHAN VIEN",
        265,
        110,
        26,
        TEXT_COLOR
    );

    DrawRectangleRounded(
        {265, 165, 850, 490},
        0.04f,
        8,
        WHITE
    );

    if (isAdd) {
        inputBox("Ho ten", {300, 220, 350, 45}, inputName, 11);
        inputBox("Ngay sinh", {700, 220, 350, 45}, inputDOB, 12);
        inputBox("Gioi tinh (Nam/Nu)", {300, 330, 350, 45}, inputGender, 13);
        inputBox("So dien thoai", {700, 330, 350, 45}, inputPhone, 14);
        inputBox("Dia chi", {300, 440, 350, 45}, inputAddress, 15);
        inputBox("Ma phong ban (3 chu so)", {700, 440, 350, 45}, inputDepartment, 16);
    }
    else {
        inputBox("Ho ten", {300, 220, 350, 45}, inputName, 11);
        inputBox("Ngay sinh", {700, 220, 350, 45}, inputDOB, 12);
        inputBox("Gioi tinh (Nam/Nu)", {300, 330, 350, 45}, inputGender, 13);
        inputBox("So dien thoai", {700, 330, 350, 45}, inputPhone, 14);
        inputBox("Dia chi", {300, 440, 350, 45}, inputAddress, 15);
        inputBox("Ma phong ban", {700, 440, 350, 45}, inputDepartment, 16);
    }

    if (button("XAC NHAN", {700, 565, 160, 45}, SUCCESS_COLOR)) {
        activeInput = -1;

        if (isAdd) {
            addEmployee();
        }
        else {
            updateEmployee();
        }
    }

    if (button("HUY", {880, 565, 160, 45}, ERROR_COLOR)) {
        activeInput = -1;
        currentScreen = isAdd
            ? MANAGER_DASHBOARD
            : EMPLOYEE_DETAIL;
    }

    if (!message.empty()) {
        DrawText(
            message.c_str(),
            300,
            610,
            15,
            isMessageError ? ERROR_COLOR : SUCCESS_COLOR
        );
    }
}

// =====================================================
// THEM NHAN VIEN
// =====================================================

void Menu::addEmployee() {
    Employee employee(
        "",
        inputName,
        inputDOB,
        inputGender,
        inputPhone,
        inputAddress,
        inputDepartment,
        "",
        "Dang lam"
    );

    string result;

    // Ham nay can duoc bo sung trong EmployeeService
    if (!employeeService.prepareEmployee(employee, result)) {
        setMessage(result, true);
        return;
    }

    selectedEmployee = employee;

    openConfirm(
        "XAC NHAN THEM NHAN VIEN",
        "Ma nhan vien: " + employee.getNV_ID() +
        "\nHo ten: " + employee.getFullName() +
        "\nNgay sinh: " + employee.getDateOfBirth() +
        "\nGioi tinh: " + employee.getGender() +
        "\nSo dien thoai: " + employee.getPhone() +
        "\nPhong ban: " + employee.getPHG_ID() +
        "\nNgay vao lam: " + employee.getNgayVaoLam() +
        "\nMat khau mac dinh: " + employee.getNV_ID(),
        1
    );
}

// =====================================================
// CAP NHAT NHAN VIEN
// =====================================================

void Menu::updateEmployee() {
    Employee employee = oldEmployee;

    employee.setFullName(inputName);
    employee.setDateOfBirth(inputDOB);
    employee.setGender(inputGender);
    employee.setPhone(inputPhone);
    employee.setAddress(inputAddress);
    employee.setPHG_ID(inputDepartment);

    selectedEmployee = employee;

    openConfirm(
        "XAC NHAN CAP NHAT",
        "Ma nhan vien: " + employee.getNV_ID() +
        "\nHo ten moi: " + employee.getFullName() +
        "\nNgay sinh moi: " + employee.getDateOfBirth() +
        "\nGioi tinh moi: " + employee.getGender() +
        "\nSo dien thoai moi: " + employee.getPhone() +
        "\nDia chi moi: " + employee.getAddress() +
        "\nPhong ban moi: " + employee.getPHG_ID(),
        2
    );
}

void Menu::updateMyProfile() {

    string result;

    if (employeeService.updateMyContactInfo(
        loginAccount.getNV_ID(),
        profilePhone,
        profileAddress,
        result
    )) {
        setMessage(result);

        isEditingProfile = false;
        activeInput = -1;

        profilePhone = "";
        profileAddress = "";
    }
    else {
        setMessage(result, true);
    }
}

// =====================================================
// CHI TIET NHAN VIEN
// =====================================================

void Menu::drawEmployeeDetail() {
    ClearBackground(BACKGROUND);

    drawSidebar();
    drawHeader();

    DrawText("CHI TIET NHAN VIEN", 265, 110, 26, TEXT_COLOR);

    DrawRectangleRounded(
        {265, 165, 850, 450},
        0.04f,
        8,
        WHITE
    );

    const Employee& e = selectedEmployee;

    drawTextLabel("Ma nhan vien: " + e.getNV_ID(), 310, 205, 18);
    drawTextLabel("Ho ten: " + e.getFullName(), 310, 250, 18);
    drawTextLabel("Ngay sinh: " + e.getDateOfBirth(), 310, 295, 18);
    drawTextLabel("Gioi tinh: " + e.getGender(), 310, 340, 18);
    drawTextLabel("So dien thoai: " + e.getPhone(), 310, 385, 18);
    drawTextLabel("Dia chi: " + e.getAddress(), 310, 430, 18);
    drawTextLabel("Phong ban: " + e.getPHG_ID(), 310, 475, 18);
    drawTextLabel("Ngay vao lam: " + e.getNgayVaoLam(), 310, 520, 18);

    Color statusColor =
        (e.getStatus() == "Da nghi viec")
        ? ERROR_COLOR
        : SUCCESS_COLOR;

    drawTextLabel(
        "Trang thai: " + e.getStatus(),
        310,
        565,
        18,
        statusColor
    );

    if (button("CAP NHAT", {700, 650, 130, 40}, PRIMARY)) {
        if (selectedEmployee.getStatus() == "Da nghi viec") {
            setMessage("Nhan vien da nghi viec, khong the cap nhat!", true);
        }
        else {
            oldEmployee = selectedEmployee;

            inputName = oldEmployee.getFullName();
            inputDOB = oldEmployee.getDateOfBirth();
            inputGender = oldEmployee.getGender();
            inputPhone = oldEmployee.getPhone();
            inputAddress = oldEmployee.getAddress();
            inputDepartment = oldEmployee.getPHG_ID();

            currentScreen = EMPLOYEE_EDIT;
        }
    }

    if (button("XOA", {850, 650, 100, 40}, ERROR_COLOR)) {
        openConfirm(
            "XAC NHAN XOA NHAN VIEN",
            "Ban co chac chan muon xoa nhan vien " +
            selectedEmployee.getNV_ID() + " - " +
            selectedEmployee.getFullName() + "?",
            3
        );
    }

    if (button("QUAY LAI", {970, 650, 130, 40}, PRIMARY)) {
        currentScreen = EMPLOYEE_LIST;
    }
}

void Menu::deleteEmployee() {
    string result;

    if (employeeService.deleteEmployee(
        selectedEmployee.getNV_ID(),
        result
    )) {
        setMessage(result);
        loadEmployees();
        currentScreen = EMPLOYEE_LIST;
    }
    else {
        setMessage(result, true);
    }
}

// =====================================================
// KHOA / MO KHOA TAI KHOAN
// =====================================================

void Menu::drawAccountAction() {
    ClearBackground(BACKGROUND);

    drawSidebar();
    drawHeader();

    bool isLock = (currentScreen == ACCOUNT_LOCK);

    DrawText(
        isLock ? "KHOA TAI KHOAN" : "MO KHOA TAI KHOAN",
        265,
        110,
        26,
        TEXT_COLOR
    );

    DrawRectangleRounded(
        {350, 200, 600, 300},
        0.04f,
        8,
        WHITE
    );

    inputBox(
        "Nhap ma nhan vien",
        {450, 300, 400, 50},
        inputNV_ID,
        20
    );

    if (button("TIEP TUC", {450, 400, 180, 45}, PRIMARY)) {
        activeInput = -1;

        vector<Account> accounts = accountService.getAllAccounts();

        bool found = false;

        for (const Account& account : accounts) {
            if (account.getNV_ID() == inputNV_ID) {
                found = true;

                if (isLock) {
                    if (account.getIsLocked()) {
                        setMessage("Tai khoan da bi khoa!", true);
                    }
                    else {
                        openConfirm(
                            "XAC NHAN KHOA TAI KHOAN",
                            "Ma nhan vien: " + inputNV_ID +
                            "\nTrang thai hien tai: Dang hoat dong" +
                            "\nTrang thai sau khi xac nhan: Da khoa",
                            4
                        );
                    }
                }
                else {
                    if (!account.getIsLocked()) {
                        setMessage("Tai khoan dang hoat dong!", true);
                    }
                    else {
                        openConfirm(
                            "XAC NHAN MO KHOA TAI KHOAN",
                            "Ma nhan vien: " + inputNV_ID +
                            "\nTrang thai hien tai: Da khoa" +
                            "\nTrang thai sau khi xac nhan: Dang hoat dong",
                            5
                        );
                    }
                }

                break;
            }
        }

        if (!found) {
            setMessage("Khong tim thay tai khoan!", true);
        }
    }

    if (button("QUAY LAI", {650, 400, 180, 45}, ERROR_COLOR)) {
        currentScreen = MANAGER_DASHBOARD;
        activeInput = -1;
    }

    if (!message.empty()) {
        DrawText(
            message.c_str(),
            400,
            470,
            16,
            isMessageError ? ERROR_COLOR : SUCCESS_COLOR
        );
    }
}

void Menu::lockAccount() {
    string result;

    if (accountService.lockAccount(inputNV_ID, result)) {
        setMessage(result);
    }
    else {
        setMessage(result, true);
    }
}

void Menu::unlockAccount() {
    string result;

    if (accountService.unlockAccount(inputNV_ID, result)) {
        setMessage(result);
    }
    else {
        setMessage(result, true);
    }
}

// =====================================================
// XAC NHAN NGHI VIEC
// =====================================================

void Menu::resignEmployee() {
    string result;

    if (employeeService.confirmResignation(
        selectedEmployee.getNV_ID(),
        result
    )) {
        setMessage(result);

        selectedEmployee.setStatus("Da nghi viec");

        loadEmployees();
        currentScreen = EMPLOYEE_DETAIL;
    }
    else {
        setMessage(result, true);
    }
}

// =====================================================
// DOI MAT KHAU
// =====================================================

void Menu::drawChangePassword() {
    ClearBackground(BACKGROUND);

    drawHeader();

    DrawText("DOI MAT KHAU", 265, 110, 28, TEXT_COLOR);

    DrawRectangleRounded(
        {350, 180, 600, 400},
        0.04f,
        8,
        WHITE
    );

    inputBox(
        "Mat khau hien tai",
        {450, 260, 400, 45},
        oldPassword,
        31,
        true
    );

    inputBox(
        "Mat khau moi",
        {450, 360, 400, 45},
        newPassword,
        32,
        true
    );

    inputBox(
        "Nhap lai mat khau moi",
        {450, 460, 400, 45},
        confirmPassword,
        33,
        true
    );

    if (button("TIEP TUC", {450, 530, 180, 45}, PRIMARY)) {
        activeInput = -1;

        if (newPassword != confirmPassword) {
            setMessage("Mat khau nhap lai khong trung khop!", true);
        }
        else if (newPassword.empty()) {
            setMessage("Mat khau moi khong duoc de trong!", true);
        }
        else {
            openConfirm(
                "XAC NHAN DOI MAT KHAU",
                "Tai khoan: " + loginAccount.getNV_ID() +
                "\nMat khau cu: ********" +
                "\nMat khau moi: ********",
                7
            );
        }
    }

    if (button("QUAY LAI", {670, 530, 180, 45}, ERROR_COLOR)) {
        currentScreen = EMPLOYEE_DASHBOARD;
        activeInput = -1;
    }

    if (!message.empty()) {
        DrawText(
            message.c_str(),
            450,
            600,
            15,
            isMessageError ? ERROR_COLOR : SUCCESS_COLOR
        );
    }
}

void Menu::changePassword() {
    string result;

    if (accountService.changePassword(
        loginAccount.getNV_ID(),
        oldPassword,
        newPassword,
        result
    )) {
        setMessage(result);
        oldPassword = "";
        newPassword = "";
        confirmPassword = "";
        currentScreen = EMPLOYEE_DASHBOARD;
    }
    else {
        setMessage(result, true);
    }
}

// =====================================================
// DASHBOARD NHAN VIEN
// =====================================================
void Menu::drawEmployeeDashboard() {
    ClearBackground(BACKGROUND);

    drawHeader();

    DrawText("TRANG NHAN VIEN", 265, 105, 28, TEXT_COLOR);

    Employee employee;

    if (!employeeService.findByID(
        loginAccount.getNV_ID(),
        employee
    )) {
        drawTextLabel(
            "Khong tim thay thong tin nhan vien!",
            300, 200, 20, ERROR_COLOR
        );
        return;
    }

    // Khung ho so
    DrawRectangleRounded(
        {280, 155, 700, 430},
        0.04f,
        8,
        WHITE
    );

    DrawText("HO SO CA NHAN", 315, 175, 23, PRIMARY);

    // Cot ben trai
    drawTextLabel(
        "Ma nhan vien: " + employee.getNV_ID(),
        315, 220, 18
    );

    drawTextLabel(
        "Ho va ten: " + employee.getFullName(),
        315, 260, 18
    );

    drawTextLabel(
        "Ngay sinh: " + employee.getDateOfBirth(),
        315, 300, 18
    );

    drawTextLabel(
        "Gioi tinh: " + employee.getGender(),
        315, 340, 18
    );

    drawTextLabel(
        "Phong ban: " + employee.getPHG_ID(),
        315, 380, 18
    );

    // Cot ben phai
    drawTextLabel(
        "Ngay vao lam: " + employee.getNgayVaoLam(),
        650, 220, 18
    );

    drawTextLabel(
        "Trang thai: " + employee.getStatus(),
        650, 260, 18
    );

    // Thong tin lien he
    if (!isEditingProfile) {

        drawTextLabel(
            "So dien thoai: " + employee.getPhone(),
            315, 435, 18
        );

        drawTextLabel(
            "Dia chi: " + employee.getAddress(),
            315, 480, 18
        );

    }
    else {

        inputBox(
            "So dien thoai",
            {315, 425, 300, 38},
            profilePhone,
            20
        );

        inputBox(
            "Dia chi",
            {650, 425, 290, 38},
            profileAddress,
            21
        );
    }

    // Nut chinh sua va xac nhan
    if (!isEditingProfile) {

        if (button(
            "CHINH SUA HO SO",
            {315, 525, 190, 45},
            PRIMARY
        )) {
            profilePhone = employee.getPhone();
            profileAddress = employee.getAddress();

            activeInput = -1;
            isEditingProfile = true;
        }

    }
    else {

        if (button(
            "XAC NHAN",
            {315, 525, 150, 45},
            SUCCESS_COLOR
        )) {
            if (profilePhone.empty() || profileAddress.empty()) {
                setMessage(
                    "Vui long nhap day du thong tin!",
                    true
                );
            }
            else {
                string content =
                    "So dien thoai moi: " + profilePhone +
                    "\nDia chi moi: " + profileAddress;

                openConfirm(
                    "XAC NHAN CAP NHAT HO SO",
                    content,
                    8
                );
            }
        }

        if (button(
            "HUY",
            {485, 525, 120, 45},
            ERROR_COLOR
        )) {
            isEditingProfile = false;
            activeInput = -1;

            profilePhone = "";
            profileAddress = "";
        }
    }

    // Doi mat khau
    if (button(
        "DOI MAT KHAU",
        {315, 625, 180, 45},
        PRIMARY
    )) {
        oldPassword = "";
        newPassword = "";
        confirmPassword = "";

        currentScreen = CHANGE_PASSWORD;
    }

    // Dang xuat
    if (button(
        "DANG XUAT",
        {515, 625, 180, 45},
        ERROR_COLOR
    )) {
        currentScreen = LOGIN;

        loginID = "";
        loginPassword = "";

        profilePhone = "";
        profileAddress = "";
        isEditingProfile = false;

        activeInput = -1;
    }
}

// =====================================================
// HOP THOAI XAC NHAN
// =====================================================

void Menu::drawConfirmDialog() {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.45f));

    DrawRectangleRounded(
        {300, 150, 600, 450},
        0.04f,
        8,
        WHITE
    );

    DrawText(
        confirmTitle.c_str(),
        340,
        185,
        23,
        PRIMARY_DARK
    );

    DrawLine(330, 225, 870, 225, BORDER_COLOR);

    int y = 250;

    string line;
    stringstream ss(confirmContent);

    while (getline(ss, line, '\n')) {
        DrawText(line.c_str(), 345, y, 16, TEXT_COLOR);
        y += 27;
    }

    if (button("XAC NHAN", {380, 530, 180, 45}, SUCCESS_COLOR)) {
        executeConfirmAction();
        showConfirm = false;
    }

    if (button("HUY", {610, 530, 180, 45}, ERROR_COLOR)) {
        showConfirm = false;
        setMessage("Da huy thao tac!");
    }
}

void Menu::executeConfirmAction() {
    switch (confirmAction) {
        case 1: {
            string result;

            if (employeeService.addEmployee(selectedEmployee, result)) {
                setMessage(result);
                loadEmployees();
                currentScreen = EMPLOYEE_LIST;
                resetEmployeeForm();
            }
            else {
                setMessage(result, true);
            }
            break;
        }

        case 2: {
            string result;

            if (employeeService.updateEmployee(selectedEmployee, result)) {
                setMessage(result);
                loadEmployees();
                currentScreen = EMPLOYEE_LIST;
            }
            else {
                setMessage(result, true);
            }
            break;
        }

        case 3:
            deleteEmployee();
            break;

        case 4:
            lockAccount();
            break;

        case 5:
            unlockAccount();
            break;

        case 6:
            resignEmployee();
            break;

        case 7:
            changePassword();
            break;

        case 8:
        updateMyProfile();
        break;
    }
}

void Menu::drawResignEmployee() {
    ClearBackground(BACKGROUND);

    drawSidebar();
    drawHeader();

    DrawText("XAC NHAN NGHI VIEC", 265, 110, 28, TEXT_COLOR);

    DrawRectangleRounded(
        {350, 200, 600, 300},
        0.04f,
        8,
        WHITE
    );

    inputBox(
        "Ma nhan vien can xac nhan nghi viec",
        {450, 290, 400, 50},
        inputNV_ID,
        20
    );

    if (button("TIEP TUC", {450, 390, 180, 45}, PRIMARY)) {
        activeInput = -1;

        Employee employee;

        if (!employeeService.findByID(inputNV_ID, employee)) {
            setMessage("Khong tim thay nhan vien!", true);
        }
        else if (employee.getStatus() == "Da nghi viec") {
            setMessage("Nhan vien da nghi viec!", true);
        }
        else {
            selectedEmployee = employee;

            openConfirm(
                "XAC NHAN NGHI VIEC",
                "Ma nhan vien: " + employee.getNV_ID() +
                "\nHo ten: " + employee.getFullName() +
                "\nPhong ban: " + employee.getPHG_ID() +
                "\nTrang thai sau xac nhan: Da nghi viec" +
                "\nTai khoan sau xac nhan: Da khoa",
                6
            );
        }
    }

    if (button("QUAY LAI", {650, 390, 180, 45}, ERROR_COLOR)) {
        currentScreen = MANAGER_DASHBOARD;
        activeInput = -1;
    }

    if (!message.empty()) {
        DrawText(
            message.c_str(),
            400,
            470,
            16,
            isMessageError ? ERROR_COLOR : SUCCESS_COLOR
        );
    }
}

// =====================================================
// CAC HAM XU LY SU KIEN DU PHONG
// =====================================================

void Menu::handleManagerInput() {}
void Menu::handleEmployeeInput() {}
void Menu::handleEmployeeListInput() {}
void Menu::handleEmployeeFormInput() {}
void Menu::handleConfirmInput() {}

// =====================================================
// MENU NHAN VIEN
// =====================================================

void Menu::employeeMenu(const Account& account) {
    loginAccount = account;
    currentScreen = EMPLOYEE_DASHBOARD;
}

// =====================================================
// CHAY CHUONG TRINH
// =====================================================

void Menu::run() {

    // Nap font Arial ho tro tieng Viet
    vector<int> codepoints = createVietnameseCodepoints();

    UI_FONT = LoadFontEx(
        "C:/Windows/Fonts/arial.ttf",
        48,
        codepoints.data(),
        (int)codepoints.size()
    );

    if (UI_FONT.texture.id == 0) {
        cout << "Khong the tai font Arial!" << endl;
        return;
    }

    SetTextureFilter(UI_FONT.texture, TEXTURE_FILTER_BILINEAR);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentScreen) {
            case LOGIN:
                drawLogin();
                break;

            case MANAGER_DASHBOARD:
                drawManagerDashboard();
                break;

            case EMPLOYEE_DASHBOARD:
                drawEmployeeDashboard();
                break;

            case EMPLOYEE_LIST:
                drawEmployeeList();
                break;

            case EMPLOYEE_ADD:
            case EMPLOYEE_EDIT:
                drawEmployeeForm();
                break;

            case EMPLOYEE_DETAIL:
                drawEmployeeDetail();
                break;

            case ACCOUNT_LOCK:
            case ACCOUNT_UNLOCK:
                drawAccountAction();
                break;

            case EMPLOYEE_RESIGN:
                drawAccountAction();
                break;

            case CHANGE_PASSWORD:
                drawChangePassword();
                break;
        }

        if (showConfirm) {
            drawConfirmDialog();
        }

        EndDrawing();
    }

    UnloadFont(UI_FONT);
}
