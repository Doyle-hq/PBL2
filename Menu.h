
#ifndef MENU_H
#define MENU_H

#include "raylib.h"

#include "../Services/EmployeeService.h"
#include "../Services/AccountService.h"

#include <string>
#include <vector>

using namespace std;

class Menu {
private:
    // ================= SERVICES =================
    EmployeeService employeeService;
    AccountService accountService;

    // ================= CAC MAN HINH =================
    enum Screen {
        LOGIN,
        MANAGER_DASHBOARD,
        EMPLOYEE_DASHBOARD,
        EMPLOYEE_LIST,
        EMPLOYEE_ADD,
        EMPLOYEE_EDIT,
        EMPLOYEE_DETAIL,
        ACCOUNT_LOCK,
        ACCOUNT_UNLOCK,
        EMPLOYEE_RESIGN,
        CHANGE_PASSWORD
    };

    Screen currentScreen;

    // ================= THONG TIN DANG NHAP =================
    Account loginAccount;

    void employeeMenu(const Account& account);

    string loginID;
    string loginPassword;
    string message;

    bool showPassword;
    bool isMessageError;

    // ================= DU LIEU NHAN VIEN =================
    vector<Employee> employees;
    Employee selectedEmployee;
    Employee oldEmployee;

    // ================= DU LIEU FORM =================
    string inputNV_ID;
    string inputName;
    string inputDOB;
    string inputGender;
    string inputPhone;
    string inputAddress;
    string inputDepartment;

    string profilePhone;
    string profileAddress;
    bool isEditingProfile;

    string searchKeyword;

    // ================= DOI MAT KHAU =================
    string oldPassword;
    string newPassword;
    string confirmPassword;

    // ================= TRANG THAI FORM =================
    int activeInput;
    int selectedMenu;
    int selectedEmployeeIndex;
    int scrollOffset;

    bool showConfirm;
    string confirmTitle;
    string confirmContent;
    int confirmAction;

    // ================= KICH THUOC GIAO DIEN =================
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 750;

    // ================= HAM VE GIAO DIEN =================
    void drawLogin();
    void drawManagerDashboard();
    void drawEmployeeDashboard();
    void drawEmployeeList();
    void drawEmployeeForm();
    void drawEmployeeDetail();
    void drawAccountAction();
    void drawChangePassword();
    void drawSidebar();
    void drawHeader();
    void drawMessage();
    void drawConfirmDialog();
    void drawResignEmployee();
    void drawEmployeeProfile();

    // ================= HAM XU LY SU KIEN =================
    void handleLogin();
    void handleManagerInput();
    void handleEmployeeInput();
    void handleEmployeeListInput();
    void handleEmployeeFormInput();
    void handleConfirmInput();

    // ================= NGHIEP VU NHAN VIEN =================
    void loadEmployees();

    void addEmployee();
    void updateEmployee();
    void deleteEmployee();

    void searchEmployee();
    void sortEmployees(int type);
    void filterEmployees();

    void lockAccount();
    void unlockAccount();
    void resignEmployee();

    void changePassword();
    void updateMyProfile();

    // ================= CAC HAM HO TRO =================
    void resetEmployeeForm();
    void setMessage(const string& text, bool isError = false);

    void openConfirm(const string& title, const string& content, int action
    );

    void executeConfirmAction();

    bool isMouseInside(Rectangle rect);
    bool button(const char* text, Rectangle rect, Color color);

    bool inputBox(const char* label, Rectangle rect, string& value, int inputID, bool password = false);

    void drawTextLabel(const string& text, int x, int y, int fontSize, Color color = DARKGRAY);

    void drawEmployeeTable(const vector<Employee>& data);

public:
    Menu();

    void run();
};

#endif
