#include "DrawMenu.h"

#include <cstring>
#include <iostream>

#include "../Button/Button.h"
#include "../DropDown/DropDown.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../TextFunction/TextFunction.h"
#include "../TextInput/TextInput.h"

void drawStudentMenu() {
    Button studentInformation(
        "Your information", SCREEN_WIDTH / 1.7f, DEFAULT_PADDING.x * 2,
        DEFAULT_MENU_BUTTON_WIDTH
    );
    Button currentCoursesButton(
        "Current courses", SCREEN_WIDTH / 1.7f + DEFAULT_MENU_BUTTON_WIDTH,
        DEFAULT_PADDING.x * 2, DEFAULT_MENU_BUTTON_WIDTH
    );
    Button scoreboard(
        "Scoreboard", SCREEN_WIDTH / 1.7f + 2 * DEFAULT_MENU_BUTTON_WIDTH,
        DEFAULT_PADDING.x * 2, DEFAULT_MENU_BUTTON_WIDTH
    );

    if (studentInformation.drawButton()) {
        // viewStudentInformationPage
    }

    if (currentCoursesButton.drawButton()) {
        // viewCurrentCoursesPage
    }

    if (scoreboard.drawButton()) {
        // viewScoreboardPage
    }
}

void drawAdminMenu() {
    Button schoolYearButton(
        "School years", SCREEN_WIDTH / 2, DEFAULT_PADDING.x * 2, DEFAULT_MENU_BUTTON_WIDTH
    );
    Button semesterButton(
        "Semesters", SCREEN_WIDTH / 2 + DEFAULT_MENU_BUTTON_WIDTH, DEFAULT_PADDING.x * 2,
        DEFAULT_MENU_BUTTON_WIDTH
    );
    Button courseButton(
        "Courses", SCREEN_WIDTH / 2 + 2 * DEFAULT_MENU_BUTTON_WIDTH,
        DEFAULT_PADDING.x * 2, DEFAULT_MENU_BUTTON_WIDTH
    );
    Button classButton(
        "Classes", SCREEN_WIDTH / 2 + 3 * DEFAULT_MENU_BUTTON_WIDTH,
        DEFAULT_PADDING.x * 2, DEFAULT_MENU_BUTTON_WIDTH
    );

    if (schoolYearButton.drawButton()) {
        // viewSchoolYearPage
    }

    if (semesterButton.drawButton()) {
        // viewSemesterPage
    }

    if (courseButton.drawButton()) {
        // viewCoursePage
    }

    if (classButton.drawButton()) {
        // viewClassPage
    }
}

void drawMenu(
    const std::string& currentUsername, char*& menuDropDownItems,
    int& menuDropdownActiveItems, bool& menuDropDownEditMode, const Texture2D& avatar
) {
    DrawTextureV(avatar, DEFAULT_AVATAR_POSITION, BACK_GROUND_COLOR);

    DropDown accountNameDropDown(
        "Change Current Semester;Change Password;Log out",
        {DEFAULT_AVATAR_SIZE.x + DEFAULT_PADDING.x * 4 + 8, DEFAULT_PADDING.y * 2},
        DEFAULT_MENU_BUTTON_WIDTH * 1.7f
    );

    accountNameDropDown.drawDropDown(
        ("Welcome, " + currentUsername).c_str(), menuDropDownItems,
        menuDropdownActiveItems, menuDropDownEditMode
    );

    if (currentUsername == "admin") {
        drawAdminMenu();
    } else {
        drawStudentMenu();
    }

    switch (menuDropdownActiveItems) {
        case 0:
            // changeCurrentSemesterPage
            break;

        case 1:
            // changePasswordPage
            break;

        case 2:
            // logoutPage
            break;
    }
}
