#include "Button.h"

Button::Button() {}

Button::Button(const char *label, float posX, float posY, float width)
    : buttonBox({posX, posY, width, DEFAULT_ITEM_HEIGHT}), label(label) {}

bool Button::drawButton(const Vector2 &scroll) {
    Rectangle buttonBoxWithScroll = buttonBox;
    buttonBoxWithScroll.x += scroll.x;
    buttonBoxWithScroll.y += scroll.y;
    return GuiButton(buttonBoxWithScroll, label);
}
