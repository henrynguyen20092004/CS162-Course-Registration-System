#include "FontFunction.h"

#include "../GlobalStyle/GlobalStyle.h"

Font loadFont(const char* titlePath, int titleSize) {
    return LoadFontEx(titlePath, titleSize, nullptr, 256);
}

Font loadDefaultTitleFont() {
    return loadFont(titleFontPath, titleFontSize);
}

Font loadDefaultTextFont() {
    return loadFont(textFontPath, textFontSize);
}
