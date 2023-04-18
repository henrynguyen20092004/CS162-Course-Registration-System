#include "Button.h"

#include <cstring>

#include "../GlobalStyle.h"
#include "../TextFunction/TextFunction.h"

Button::Button(const char *text, float posX, float posY, float width)
    : buttonBox({posX, posY, width, DEFAULT_ITEM_HEIGHT}), text(text) {}

Button::Button(const char *text, float posX, float posY)
    : buttonBox(
          {posX, posY, strlen(text) * SPACING + DEFAULT_PADDING.x * 2,
           DEFAULT_ITEM_HEIGHT}
      ) {}

bool Button::drawButton() { return GuiButton(buttonBox, text); }
