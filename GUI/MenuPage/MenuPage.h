#ifndef MENU_PAGE_H
#define MENU_PAGE_H

#include <raylib.h>

#include "../FontFunction/FontFunction.h"
#include "../GlobalStyle.h"
#include "../Page/Page.h"

class MenuPage : public Page {
    void drawPage() override;
    void submitCallBack(int choice);

   protected:
    Font textFont = loadDefaultTitleFont();
    Texture defaultAvatar = LoadTexture("Pictures/DefaultAvatar.png");

   public:
    ~MenuPage();
};

#endif
