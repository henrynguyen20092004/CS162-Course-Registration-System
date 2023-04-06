#ifndef TEXT_FUNCTION_H
#define TEXT_FUNCTION_H

#include "../GlobalStyle.h"

void drawDefaultTitle(
    const Font& titleFont, const char* title, const Vector2& position,
    const Color& color = NORMAL_TEXT_COLOR
);
void drawDefaultText(
    const Font& textFont, const char* text, const Vector2& position,
    const Color& color = NORMAL_TEXT_COLOR
);
float measureTextWidth(const Font& font, const char* text, int fontSize);

#endif
