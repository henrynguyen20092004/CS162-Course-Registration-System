#include "DrawMenu.h"

#include <cstring>
#include <iostream>

#include "../Button/Button.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../LogOutPage/LogOutPage.h"
#include "../TextFunction/TextFunction.h"
#include "../TextInput/TextInput.h"

void drawStudentMenu() {}

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

void drawMenu(const std::string& currentUsername) {
    char* username = c_string(currentUsername);

    Button accountNameButton(
        username, defaultAvatarPosition.x + DEFAULT_AVATAR_SIZE.x + DEFAULT_PADDING.x * 2,
        DEFAULT_PADDING * 2, DEFAULT_MENU_BUTTON_WIDTH
    );

    if (accountNameButton.drawButton()) {
        // logout and change password
    }

    if (strncmp(username, "admin", 5) == 0) {
        drawAdminMenu();
    } else {
        drawStudentMenu();
    }
}
