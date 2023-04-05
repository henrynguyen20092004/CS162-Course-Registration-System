#include "MainWindow.h"

#include "FontFunction/FontFunction.h"
#include "GlobalStyle/GlobalStyle.h"
#include "TextFunction/TextFunction.h"

void initMainWindow() {
    InitWindow(screenWidth, screenHeight, "Course Registration System");

    Image windowIcon = LoadImage("Pictures/WindowIcon.png");
    Font titleFont = loadDefaultTitleFont(), textFont = loadDefaultTextFont();

    SetWindowIcon(windowIcon);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(backgroundColor);

        drawDefaultTitle(titleFont, "This is a title :D", {595.0f, 250.0f});
        drawDefaultText(
            textFont, "Congrats! You created your first window!", {532.5f, 420.0f}
        );

        EndDrawing();
    }

    UnloadImage(windowIcon);
    UnloadFont(titleFont);
    UnloadFont(textFont);
    CloseWindow();
}
