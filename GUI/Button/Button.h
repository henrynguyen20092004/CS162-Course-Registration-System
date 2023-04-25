#ifndef BUTTON_H
#define BUTTON_H

#include "../GlobalStyle.h"

class Button {
   private:
    Rectangle buttonBox;
    const char *label;

   public:
    Button();
    Button(const char *label, float posX, float posY, float width);
    bool drawButton(float scrollY = 0.0f);
};

#endif
