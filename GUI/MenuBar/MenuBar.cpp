#include "MenuBar.h"

#include "../../GlobalVar/GlobalVar.h"
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
        GlobalVar::currentCommand = VIEW_STUDENT_INFO;
        stopLoop = true;
    }

    if (myCoursesButton.drawButton()) {
        GlobalVar::currentCommand = VIEW_COURSES_OF_STUDENT;
        stopLoop = true;
    }

    if (myScoreboardButton.drawButton()) {
        GlobalVar::currentCommand = VIEW_SCOREBOARD_OF_STUDENT;
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
        GlobalVar::currentCommand = VIEW_SCHOOL_YEARS;
        stopLoop = true;
    }

    if (semesterButton.drawButton()) {
        GlobalVar::currentCommand = VIEW_SEMESTERS;
        stopLoop = true;
    }

    if (courseButton.drawButton()) {
        GlobalVar::currentCommand = VIEW_COURSES;
        stopLoop = true;
    }

    if (classButton.drawButton()) {
        GlobalVar::currentCommand = VIEW_CLASSES;
        stopLoop = true;
    }
}

void drawMenuBar(DropDown& menuDropDown, char*& menuDropDownItems, bool& stopLoop) {
    DrawRectangleV({0.0f, 0.0f}, {SCREEN_WIDTH, MENU_HEIGHT}, {6, 57, 112, 255});
    DrawTextureV(GlobalVar::defaultAvatar, {5.0f, 15.0f}, WHITE);
    menuDropDown.drawDropDown(menuDropDownItems, 0.0f, WHITE);

    if (GlobalVar::currentUser.username == "admin") {
        drawAdminMenu(stopLoop);
    } else {
        drawStudentMenu(stopLoop);
    }

    switch (menuDropDown.activeItemIndex) {
        case 0:
            GlobalVar::currentCommand = CHANGE_CURRENT_SEMESTER;
            stopLoop = true;
            break;

        case 1:
            GlobalVar::currentCommand = CHANGE_PASSWORD;
            stopLoop = true;
            break;

        case 2:
            GlobalVar::currentUser.username = "";
            GlobalVar::currentUser.password = "";
            stopLoop = true;
            break;
    }
}
