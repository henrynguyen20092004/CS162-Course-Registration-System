#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include "../GlobalStyle.h"

class TextInput {
   private:
    Rectangle textInputBox;
    char *input;

   public:
    TextInput(char *input, Vector2 pos, float width);
    bool drawTextInput(const char *label, bool &editMode);
};

#endif
