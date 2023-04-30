#ifndef TEXT_FUNCTION_H
#define TEXT_FUNCTION_H

#include <string>

#include "../GlobalStyle.h"

float measureTextWidth(const Font& font, const char* text);
std::string clipText(const Font& font, const char* text, int maxWidth);
void drawDefaultTitle(
    const char* title, const Vector2& position, const Color& color = NORMAL_TEXT_COLOR
);
void drawDefaultText(
    const char* text, const Vector2& position, const Color& color = NORMAL_TEXT_COLOR
);

#endif
