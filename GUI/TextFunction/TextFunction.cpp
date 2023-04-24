#include "TextFunction.h"

float measureTextWidth(const Font& font, const char* text) {
    return MeasureTextEx(font, text, font.baseSize, TEXT_SPACING).x;
}

std::string clipText(const Font& font, const char* text, int maxWidth) {
    if (measureTextWidth(font, text) <= maxWidth) {
        return text;
    }

    int curDelimiter = 1;
    std::string curText, result = text;

    for (int i = 0; result[i] != '\0'; ++i) {
        if (result[i] == ' ') {
            curDelimiter = i;
        }

        if (measureTextWidth(font, curText.c_str()) > maxWidth) {
            result[curDelimiter] = '\n';
            curText = "";
            i = curDelimiter + 1;
        }

        curText += text[i];
    }

    return result;
}

void drawDefaultTitle(
    const Font& titleFont, const char* title, const Vector2& position, const Color& color
) {
    DrawTextEx(titleFont, title, position, DEFAULT_TITLE_SIZE, TEXT_SPACING, color);
}

void drawDefaultText(
    const Font& textFont, const char* text, const Vector2& position, const Color& color
) {
    DrawTextEx(textFont, text, position, DEFAULT_TEXT_SIZE, TEXT_SPACING, color);
}
