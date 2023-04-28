#include "Page.h"

#include <stdexcept>

#include "../DrawMenu/DrawMenu.h"

Page::Page() { menuDropDownItems = new char[MAX_INPUT_CHAR]; }

bool Page::isLoggedIn() { return currentUser.username != ""; }

void Page::mainLoop() {
    menuDropDown = DropDown(
        ("Welcome, " + currentUser.username).c_str(),
        "Change current semester;Change password;Log out",
        {AVATAR_SIZE.x + DEFAULT_PADDING.x * 4 + 8, DEFAULT_PADDING.y * 2},
        DEFAULT_MENU_BUTTON_WIDTH * 1.5f
    );
    initComponents();

    while (!stopLoop) {
        if (WindowShouldClose()) {
            commandChoice = EXIT;
            break;
        }

        BeginDrawing();
        ClearBackground(PRIMARY_COLOR);
        drawPage();

        if (isLoggedIn()) {
            drawMenu(menuDropDown, menuDropDownItems, stopLoop);
        }

        EndDrawing();
    }
}

Page::~Page() { delete[] menuDropDownItems; }
