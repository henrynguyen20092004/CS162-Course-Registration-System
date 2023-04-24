#include "DrawMenu.h"

#include "../Button/Button.h"

void drawStudentMenu() {
    Button studentInformation(
        "Your information", SCREEN_WIDTH / 1.6f, DEFAULT_PADDING.y * 2,
        DEFAULT_MENU_BUTTON_WIDTH
    );
    Button currentCoursesButton(
        "Current course",
        SCREEN_WIDTH / 1.6f + DEFAULT_MENU_BUTTON_WIDTH + DEFAULT_ITEM_MARGIN.x,
        DEFAULT_PADDING.y * 2, DEFAULT_MENU_BUTTON_WIDTH
    );
    Button scoreboard(
        "Scoreboard",
        SCREEN_WIDTH / 1.6f + 2 * (DEFAULT_MENU_BUTTON_WIDTH + DEFAULT_ITEM_MARGIN.x),
        DEFAULT_PADDING.y * 2, DEFAULT_MENU_BUTTON_WIDTH
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

void drawMenu(DropDown& menuDropDown, char*& menuDropDownItems) {
    DrawRectangleV({0.0f, 0.0f}, {SCREEN_WIDTH, MENU_HEIGHT}, SECONDARY_COLOR);
    DrawTextureV(defaultAvatar, AVATAR_POSITION, WHITE);

    menuDropDown.drawDropDown(menuDropDownItems, 0.0f, WHITE);

    if (currentUser.username == "admin") {
        drawAdminMenu();
    } else {
        drawStudentMenu();
    }

    switch (menuDropDown.activeItemIndex) {
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
