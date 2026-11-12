#include "Presentation/Menu.h"
#include "raylib.h"

int main() {
    // Khoi tao cua so
    InitWindow(1200, 750, "PBL2 - Employee Management System");

    // Gioi han toc do khung hinh
    SetTargetFPS(60);

    // Khoi tao Menu
    Menu menu;

    // Chay ung dung
    menu.run();

    // Dong cua so
    CloseWindow();

    return 0;
}
