#include "Button.h"

#include "../GlobalStyle.h"

Button::Button(const char *text, float posX, float posY, float width)
    : buttonBox({posX, posY, width, DEFAULT_ITEM_HEIGHT}), text(text) {}

bool Button::drawButton() { return GuiButton(buttonBox, text); }
