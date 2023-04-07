#include "FontFunction.h"

#include "../GlobalStyle.h"

Font loadFont(const char* titlePath, int titleSize) {
    return LoadFontEx(titlePath, titleSize, nullptr, 256);
}

Font loadDefaultTitleFont() {
    return loadFont("Font/tahoma.ttf", DEFAULT_TITLE_SIZE);
}

Font loadDefaultTextFont() {
    return loadFont("Font/cambria.ttf", DEFAULT_TEXT_SIZE);
}
