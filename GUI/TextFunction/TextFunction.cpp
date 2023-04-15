#include "TextFunction.h"

#include <cstring>

float measureTextWidth(const Font& font, const char* text) {
    return MeasureTextEx(font, text, font.baseSize, SPACING).x;
}

std::string clipText(const Font& font, const char* text, int maxWidth) {
    if (measureTextWidth(font, text) <= maxWidth) {
        return text;
    }

    int curSpace = 1, textLength = strlen(text);
    std::string curText, result = text;

    for (int i = 1; i < textLength; ++i) {
        if (text[i] == ' ') {
            curSpace = i;
        }

        if (measureTextWidth(font, curText.c_str()) > maxWidth) {
            result[curSpace] = '\n';
            curText = "";
            i = curSpace + 1;
        }

        curText += text[i];
    }

    return result;
}

void drawDefaultTitle(
    const Font& titleFont, const char* title, const Vector2& position, const Color& color
) {
    DrawTextEx(titleFont, title, position, DEFAULT_TITLE_SIZE, SPACING, color);
}

void drawDefaultText(
    const Font& textFont, const char* text, const Vector2& position, const Color& color
) {
    DrawTextEx(textFont, text, position, DEFAULT_TEXT_SIZE, SPACING, color);
}
