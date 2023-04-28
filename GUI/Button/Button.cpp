#include "Button.h"

Button::Button() {}

Button::Button(const char *label, float posX, float posY, float width)
    : buttonBox({posX, posY, width, DEFAULT_ITEM_HEIGHT}), label(label) {}

bool Button::drawButton(float scrollY) {
    Rectangle buttonBoxWithScroll = buttonBox;
    buttonBoxWithScroll.y += scrollY;
    return GuiButton(buttonBoxWithScroll, label);
}
