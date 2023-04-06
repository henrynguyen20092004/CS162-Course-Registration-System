#include "Button.h"

#include "../GlobalStyle.h"
#include "../TextFunction/TextFunction.h"

Button::Button(const char *text, float posY, float posX, float width)
    : buttonBox({posX, posY, width, 60.0f}), text(text) {}

bool Button::drawButton() {
    return GuiButton(buttonBox, text);
}
