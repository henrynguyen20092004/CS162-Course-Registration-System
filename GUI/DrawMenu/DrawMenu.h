#ifndef DRAW_PAGE_H
#define DRAW_PAGE_H

#include <raylib.h>

#include <string>

#include "../FontFunction/FontFunction.h"
#include "../GlobalStyle.h"
#include "../Page/Page.h"

void drawMenu(
    const std::string& currentUsername, char*& menuDropDownItems,
    int& menuDropdownActiveItems, bool& menuDropDownEditMode, const Texture2D& avatar
);

#endif
