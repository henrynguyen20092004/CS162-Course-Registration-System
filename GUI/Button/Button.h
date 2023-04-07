#ifndef BUTTON_H
#define BUTTON_H

#include "../GlobalStyle.h"

class Button {
   private:
    Rectangle buttonBox;
    const char *text;

   public:
    Button(const char *text, float posY, float posX = 570.0f, float width = 460.0f);
    bool drawButton();
};

#endif
