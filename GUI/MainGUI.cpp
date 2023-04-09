#define RAYGUI_IMPLEMENTATION

#include "MainGUI.h"

#include "AddStudentToCoursePage/AddStudentToCoursePage.h"
#include "Create/CreateClassPage/CreateClassPage.h"
#include "ExportStudentsInCoursePage/ExportStudentsInCoursePage.h"
#include "FontFunction/FontFunction.h"
#include "GlobalStyle.h"
#include "LogInPage/LogInPage.h"
#include "Page/Page.h"
#include "UpdateCoursePage/UpdateCoursePage.h"

Font titleFont, textFont;
Texture2D defaultAvatar;
User currentUser;

void SetDefaultStyle() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, DEFAULT_TEXT_SIZE);
    GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
    GuiSetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING, 0);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x063970ff);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xffffffff);
    GuiSetFont(textFont);
}

void mainWindow() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Course Registration System");

    Image windowIcon = LoadImage("Pictures/WindowIcon.png");
    titleFont = loadDefaultTitleFont();
    textFont = loadDefaultTextFont();
    defaultAvatar = LoadTexture("Pictures/DefaultAvatar.png");

    SetWindowIcon(windowIcon);
    SetTargetFPS(60);
    SetDefaultStyle();

    // Testing
    try {
        logInPage();
        createClassPage();
        Page tempPage;
        tempPage.mainLoop();
    } catch (std::runtime_error &error) {
        UnloadImage(windowIcon);
        UnloadFont(titleFont);
        UnloadFont(textFont);
        UnloadTexture(defaultAvatar);
        CloseWindow();
    }
}
