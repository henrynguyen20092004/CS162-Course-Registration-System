#include "TextFunction.h"

#include "../GlobalStyle/GlobalStyle.h"

void drawDefaultTitle(const Font& titleFont, const char* title, const Vector2& position) {
    DrawTextEx(titleFont, title, position, titleFontSize, spacing, textColor);
}

void drawDefaultText(const Font& textFont, const char* text, const Vector2& position) {
    DrawTextEx(textFont, text, position, textFontSize, spacing, textColor);
}

float measureTextWidth(const Font& font, const char* text, int fontSize) {
    return MeasureTextEx(font, text, fontSize, spacing).x;
}
