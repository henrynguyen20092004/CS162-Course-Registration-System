#include "LogOutPage.h"

#include <raylib.h>

#include "../Button/Button.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../GlobalStyle.h"
#include "../TextFunction/TextFunction.h"

void LogOutPage::drawPage() {
    Vector2 centerPosition = getCenterPosition({SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3});
    DrawRectangleV(centerPosition, {SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3}, WHITE);
    drawDefaultTitle(titleFont, "Are you sure?", centerPosition);

    Button acceptButton(
        "YES", centerPosition.x, centerPosition.y, DEFAULT_MENU_BUTTON_WIDTH
    );
    Button denyButton(
        "NO", centerPosition.x, centerPosition.y + DEFAULT_PADDING,
        DEFAULT_MENU_BUTTON_WIDTH
    );

    if (acceptButton.drawButton()) {
        stopLoop = true;
    }
    if (denyButton.drawButton()) {
        stopLoop = true;
    }
}
