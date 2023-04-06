#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include "../GlobalStyle.h"

class TextInput {
   private:
    Rectangle textInputBox;
    char *input;

   public:
    TextInput(char *input, float posY, float posX = 570.0f, float width = 460.0f);
    bool drawTextInput(const char *label, bool &editMode);
};

#endif
