#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include "../GlobalStyle.h"

class TextInput {
   private:
    Rectangle textInputBox;
    char *input;
    bool editMode = false;

   public:
    TextInput();
    TextInput(char *input, Vector2 pos, float width);
    bool drawTextInput(const char *label);
};

#endif
