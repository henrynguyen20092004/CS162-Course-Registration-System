#ifndef BUTTON_H
#define BUTTON_H

#include "../GlobalStyle.h"

class Button {
   private:
    const char *label = nullptr;

   public:
    Rectangle buttonBox{0.0f, 0.0f, 0.0f, 0.0f};
    Button();
    Button(const char *label, float posX, float posY, float width);
    bool drawButton(const Vector2 &scroll = {0.0f, 0.0f});
};

#endif
