#ifndef BUTTON_H
#define BUTTON_H

#include "../GlobalStyle.h"

class Button {
   private:
    Rectangle buttonBox;
    const char *text;

   public:
    Button(const char *text, float posX, float posY, float width);
    bool drawButton();
};

#endif
