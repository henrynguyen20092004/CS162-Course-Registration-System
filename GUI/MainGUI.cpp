#define RAYGUI_IMPLEMENTATION

#include "MainGUI.h"

#include "AddStudentToCoursePage/AddStudentToCoursePage.h"
#include "FontFunction/FontFunction.h"
#include "GlobalStyle.h"
#include "LogInPage/LogInPage.h"
#include "Page/Page.h"

Font titleFont, textFont;

void mainWindow() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Course Registration System");

    Image windowIcon = LoadImage("Pictures/WindowIcon.png");
    titleFont = loadDefaultTitleFont();
    textFont = loadDefaultTextFont();

    SetWindowIcon(windowIcon);
    SetTargetFPS(60);
    GuiSetStyle(DEFAULT, TEXT_SIZE, DEFAULT_TEXT_SIZE);
    GuiSetFont(textFont);

    // Testing
    try {
        addStudentToCoursePage();
        Page tempPage;
        tempPage.mainLoop();
    } catch (std::runtime_error &error) {
        UnloadImage(windowIcon);
        UnloadFont(titleFont);
        UnloadFont(textFont);
        CloseWindow();
    }
}
