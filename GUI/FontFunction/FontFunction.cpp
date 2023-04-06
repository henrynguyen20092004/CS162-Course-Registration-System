#include "FontFunction.h"

Font loadFont(const char* titlePath, int titleSize) {
    return LoadFontEx(titlePath, titleSize, nullptr, 256);
}

Font loadDefaultTitleFont() {
    return loadFont(DEFAULT_TITLE_PATH, DEFAULT_TITLE_SIZE);
}

Font loadDefaultTextFont() {
    return loadFont(DEFAULT_TEXT_PATH, DEFAULT_TEXT_SIZE);
}
