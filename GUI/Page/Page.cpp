#include "Page.h"

#include <stdexcept>

#include "../DrawMenu/DrawMenu.h"

Page::Page() { menuDropDownItems = new char[MAX_INPUT_CHAR]; }

void Page::mainLoop() {
    menuDropDown = DropDown(
        "Change current semester;Change password;Log out",
        {AVATAR_SIZE.x + DEFAULT_PADDING.x * 4 + 8, DEFAULT_PADDING.y * 2},
        DEFAULT_MENU_BUTTON_WIDTH * 1.5f
    );
    initComponents();

    while (!stopLoop) {
        if (WindowShouldClose()) {
            throw std::runtime_error("Close window");
        }

        BeginDrawing();
        ClearBackground(PRIMARY_COLOR);
        drawPage();

        if (currentUser.username != "") {
            drawMenu(menuDropDown, menuDropDownItems);
        }
        EndDrawing();
    }
}

Page::~Page() { delete[] menuDropDownItems; }
