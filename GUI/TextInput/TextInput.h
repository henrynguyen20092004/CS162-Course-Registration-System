#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include <string>

#include "../GlobalStyle.h"

class TextInput {
   private:
    Rectangle textInputBox;
    const char *label;
    char *input;
    bool editMode = false;
    float width;
    std::string truncatedInput = "";
    void truncateInput();

   public:
    TextInput();
    TextInput(const char *label, char *input, Vector2 pos, float width);
    bool drawTextInput();
};

#endif
