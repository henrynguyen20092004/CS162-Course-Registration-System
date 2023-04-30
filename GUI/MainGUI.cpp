#define RAYGUI_IMPLEMENTATION

#include "MainGUI.h"

#include "../Function/GetCurrentSemester/GetCurrentSemester.h"
#include "../GlobalVar/GlobalVar.h"
#include "FontFunction/FontFunction.h"
#include "GlobalStyle.h"
#include "LogInPage/LogInPage.h"

void setDefaultStyle() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, DEFAULT_TEXT_SIZE);
    GuiSetStyle(TEXTBOX, TEXT_COLOR_DISABLED, 0x5d6874ff);
    GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
    GuiSetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING, 0);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x063970ff);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xffffffff);
    GuiSetStyle(LISTVIEW, SCROLLBAR_WIDTH, 18);
    GuiSetFont(GlobalVar::textFont);
}

void mainWindow() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Course Registration System");
    getCurrentSemester();

    Image windowIcon = LoadImage("Pictures/WindowIcon.png");
    GlobalVar::titleFont = loadDefaultTitleFont();
    GlobalVar::textFont = loadDefaultTextFont();
    GlobalVar::defaultAvatar = LoadTexture("Pictures/DefaultAvatar.png");
    GlobalVar::fullScreenLogo = LoadTexture("Pictures/FullScreenLogo.png");
    GlobalVar::groupInfo = LoadTexture("Pictures/GroupInfo.png");

    SetWindowIcon(windowIcon);
    SetTargetFPS(60);
    setDefaultStyle();

    do {
        if (GlobalVar::currentUser.username == "") {
            logInPage();
        } else {
            selectPage();
        }
    } while (GlobalVar::commandChoice != EXIT);

    UnloadImage(windowIcon);
    UnloadFont(GlobalVar::titleFont);
    UnloadFont(GlobalVar::textFont);
    UnloadTexture(GlobalVar::defaultAvatar);
    UnloadTexture(GlobalVar::fullScreenLogo);
    UnloadTexture(GlobalVar::groupInfo);
    CloseWindow();
}
