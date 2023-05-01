#include "Page.h"

#include "../../GlobalVar/GlobalVar.h"
#include "../Button/Button.h"
#include "../DropDown/DropDown.h"
#include "../MenuBar/MenuBar.h"
#include "../TextFunction/TextFunction.h"

Page::Page() { menuDropDownItems = new char[MAX_INPUT_CHAR]; }

void Page::mainLoop() {
    std::string currentSemesterText = "Current semester: Semester " +
                                      std::to_string(GlobalVar::currentSemester.number) +
                                      ", " + GlobalVar::currentSemester.schoolYearName;

    DropDown menuDropDown(
        currentSemesterText.c_str(), "Change current semester;Change password; Log out",
        {120.0f, DEFAULT_PADDING.y * 3.5f}, DEFAULT_MENU_BUTTON_WIDTH * 1.5f
    );
    Button homeButton(
        "HOME", DEFAULT_PADDING.x / 2.0f, MENU_HEIGHT + DEFAULT_PADDING.y / 2.0f, 75.0f
    );
    initComponents();

    while (!stopLoop) {
        if (WindowShouldClose()) {
            GlobalVar::currentCommand = EXIT;
            break;
        }

        BeginDrawing();
        ClearBackground(PRIMARY_COLOR);
        drawPage();
        drawMenuBar(menuDropDown, menuDropDownItems, stopLoop);
        drawDefaultText(
            ("Welcome, " + GlobalVar::currentUser.username).c_str(),
            {120.0f, DEFAULT_PADDING.y / 2.0f}, WHITE
        );

        if (homeButton.drawButton()) {
            GlobalVar::currentCommand = HOME;
            stopLoop = true;
        }

        EndDrawing();
    }
}

Page::~Page() { delete[] menuDropDownItems; }
