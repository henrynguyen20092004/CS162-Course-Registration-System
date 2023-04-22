#include "Button.h"

Button::Button() : buttonBox({0.0f, 0.0f, 0.0f, 0.0f}), label("") {}

Button::Button(const char *label, float posX, float posY, float width)
    : buttonBox({posX, posY, width, DEFAULT_ITEM_HEIGHT}), label(label) {}

bool Button::drawButton() { return GuiButton(buttonBox, label); }
