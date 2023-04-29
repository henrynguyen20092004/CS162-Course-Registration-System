#include "Page.h"

#include "../DrawMenu/DrawMenu.h"
#include "../TextFunction/TextFunction.h"

Page::Page() { menuDropDownItems = new char[MAX_INPUT_CHAR]; }

void Page::mainLoop() {
    std::string currentSemesterText = "Current semester: Semester " +
                                      std::to_string(currentSemester.number) + ", " +
                                      currentSemester.schoolYearName;

    menuDropDown = DropDown(
        currentSemesterText.c_str(), "Change current semester;Change password; Log out",
        {120.0f, DEFAULT_PADDING.y * 3.5f}, DEFAULT_MENU_BUTTON_WIDTH * 1.5f
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
        drawMenu(menuDropDown, menuDropDownItems, stopLoop);
        drawDefaultText(
            textFont, ("Welcome, " + currentUser.username).c_str(),
            {120.0f, DEFAULT_PADDING.y / 2.0f}, WHITE
        );
        EndDrawing();
    }
}

Page::~Page() { delete[] menuDropDownItems; }
