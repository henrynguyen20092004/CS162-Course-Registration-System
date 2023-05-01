#include "ScrollBar.h"

void drawScrollBar(
    const Rectangle &bounds, const char *text, const Rectangle &content, Vector2 &scroll

) {
    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, 0xa5d7e8ff);

    if (GuiIsLocked()) {
        GuiUnlock();
        GuiScrollPanel(bounds, text, content, &scroll);
        GuiLock();
    } else {
        GuiScrollPanel(bounds, text, content, &scroll);
    }

    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, 0xf5f5f5ff);
}
