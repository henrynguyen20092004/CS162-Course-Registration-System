#include "DrawMenu.h"

#include "../../Function/LogOut/LogOut.h"
#include "../Button/Button.h"

void drawStudentMenu(bool& stopLoop) {
    Button myInfoButton(
        "My information", SCREEN_WIDTH / 1.6f, DEFAULT_PADDING.y * 2,
        DEFAULT_MENU_BUTTON_WIDTH
    );
    Button myCoursesButton(
        "My courses",
        SCREEN_WIDTH / 1.6f + DEFAULT_MENU_BUTTON_WIDTH + DEFAULT_ITEM_MARGIN.x,
        DEFAULT_PADDING.y * 2, DEFAULT_MENU_BUTTON_WIDTH
    );
    Button myScoreboardButton(
        "My scoreboard",
        SCREEN_WIDTH / 1.6f + 2 * (DEFAULT_MENU_BUTTON_WIDTH + DEFAULT_ITEM_MARGIN.x),
        DEFAULT_PADDING.y * 2, DEFAULT_MENU_BUTTON_WIDTH
    );

    if (myInfoButton.drawButton()) {
        commandChoice = VIEW_STUDENT_INFO;
        stopLoop = true;
    }

    if (myCoursesButton.drawButton()) {
        commandChoice = VIEW_COURSES_OF_STUDENT;
        stopLoop = true;
    }

    if (myScoreboardButton.drawButton()) {
        commandChoice = VIEW_SCOREBOARD_OF_STUDENT;
        stopLoop = true;
    }
}

void drawAdminMenu(bool& stopLoop) {
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
        commandChoice = VIEW_SCHOOL_YEARS;
        stopLoop = true;
    }

    if (semesterButton.drawButton()) {
        commandChoice = VIEW_SEMESTERS;
        stopLoop = true;
    }

    if (courseButton.drawButton()) {
        commandChoice = VIEW_COURSES;
        stopLoop = true;
    }

    if (classButton.drawButton()) {
        commandChoice = VIEW_CLASSES;
        stopLoop = true;
    }
}

void drawMenu(DropDown& menuDropDown, char*& menuDropDownItems, bool& stopLoop) {
    DrawRectangleV({0.0f, 0.0f}, {SCREEN_WIDTH, MENU_HEIGHT}, {6, 57, 112, 255});
    DrawTextureV(defaultAvatar, {5.0f, 15.0f}, WHITE);
    menuDropDown.drawDropDown(menuDropDownItems, 0.0f, WHITE);

    if (currentUser.username == "admin") {
        drawAdminMenu(stopLoop);
    } else {
        drawStudentMenu(stopLoop);
    }

    switch (menuDropDown.activeItemIndex) {
        case 0:
            commandChoice = CHANGE_CURRENT_SEMESTER;
            stopLoop = true;
            break;

        case 1:
            commandChoice = CHANGE_PASSWORD;
            stopLoop = true;
            break;

        case 2:
            logOut(currentUser);
            stopLoop = true;
            break;
    }
}
