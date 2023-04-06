#include "TextFunction.h"

void drawDefaultTitle(const Font& titleFont, const char* title, const Vector2& position) {
    DrawTextEx(titleFont, title, position, DEFAULT_TITLE_SIZE, SPACING, TEXT_COLOR);
}

void drawDefaultText(const Font& textFont, const char* text, const Vector2& position) {
    DrawTextEx(textFont, text, position, DEFAULT_TEXT_SIZE, SPACING, TEXT_COLOR);
}

float measureTextWidth(const Font& font, const char* text, int fontSize) {
    return MeasureTextEx(font, text, fontSize, SPACING).x;
}
