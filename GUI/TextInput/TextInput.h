#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include <string>

#include "../GlobalStyle.h"

class TextInput {
   private:
    Rectangle textInputBox{0.0f, 0.0f, 0.0f, 0.0f};
    const char *label = nullptr;
    char *input = nullptr;
    bool editMode = false;
    float width = 0.0f;
    std::string truncatedInput;
    void truncateInput();

   public:
    TextInput();
    TextInput(const char *label, char *input, Vector2 pos, float width);
    bool drawTextInput(float scrollY = 0.0f);
};

#endif
