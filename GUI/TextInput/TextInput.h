#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include "../GlobalStyle.h"

class TextInput {
   private:
    Rectangle textInputBox;
    const char *label;
    char *input;
    bool editMode = false;

   public:
    TextInput();
    TextInput(const char *label, char *input, Vector2 pos, float width);
    bool drawTextInput();
};

#endif
