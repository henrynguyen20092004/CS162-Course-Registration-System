#include "Page.h"

#include <stdexcept>

#include "../GlobalStyle.h"

void Page::mainLoop() {
    while (!stopLoop) {
        if (WindowShouldClose()) {
            throw std::runtime_error("Close window");
        }

        BeginDrawing();
        ClearBackground(BACK_GROUND_COLOR);
        drawPage();
        EndDrawing();
    }
}
