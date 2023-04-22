#include "DrawMenu.h"

#include "../Button/Button.h"
#include "../DropDown/DropDown.h"

void drawStudentMenu() {
    Button studentInformation(
        "Your information", SCREEN_WIDTH / 1.6f, DEFAULT_PADDING.x * 2,
        DEFAULT_MENU_BUTTON_WIDTH
    );
    Button currentCoursesButton(
        "Current course", SCREEN_WIDTH / 1.6f + DEFAULT_MENU_BUTTON_WIDTH,
        DEFAULT_PADDING.x * 2, DEFAULT_MENU_BUTTON_WIDTH
    );
    Button scoreboard(
        "Scoreboard", SCREEN_WIDTH / 1.6f + 2 * DEFAULT_MENU_BUTTON_WIDTH,
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
        "School year", SCREEN_WIDTH / 2.0f, DEFAULT_PADDING.y * 2,
        DEFAULT_MENU_BUTTON_WIDTH
    );
    Button semesterButton(
        "Semester",
        SCREEN_WIDTH / 2.0f + DEFAULT_MENU_BUTTON_WIDTH + DEFAULT_ITEM_MARGIN.x,
        DEFAULT_PADDING.y * 2, DEFAULT_MENU_BUTTON_WIDTH
    );
    Button courseButton(
        "Course",
        SCREEN_WIDTH / 2.0f + 2 * (DEFAULT_MENU_BUTTON_WIDTH + DEFAULT_ITEM_MARGIN.x),
        DEFAULT_PADDING.y * 2, DEFAULT_MENU_BUTTON_WIDTH
    );
    Button classButton(
        "Class",
        SCREEN_WIDTH / 2.0f + 3 * (DEFAULT_MENU_BUTTON_WIDTH + DEFAULT_ITEM_MARGIN.x),
        DEFAULT_PADDING.y * 2, DEFAULT_MENU_BUTTON_WIDTH
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

void drawMenu(char*& menuDropDownItems) {
    DrawRectangleV({0.0f, 0.0f}, {SCREEN_WIDTH, SCREEN_HEIGHT / 6.4f}, SECONDARY_COLOR);
    DrawTextureV(defaultAvatar, AVATAR_POSITION, WHITE);

    DropDown accountNameDropDown(
        "Change current semester;Change password;Log out",
        {AVATAR_SIZE.x + DEFAULT_PADDING.x * 4 + 8, DEFAULT_PADDING.y * 2},
        DEFAULT_MENU_BUTTON_WIDTH * 1.5f
    );

    accountNameDropDown.drawDropDown(
        ("Welcome, " + currentUser.username).c_str(), menuDropDownItems, WHITE
    );

    if (currentUser.username == "admin") {
        drawAdminMenu();
    } else {
        drawStudentMenu();
    }

    switch (accountNameDropDown.activeItemIndex) {
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
