#include "TextInput.h"

#include "../GlobalStyle.h"
#include "../TextFunction/TextFunction.h"

TextInput::TextInput(char *input, float posY, float posX, float width)
    : textInputBox({posX, posY, width, 60.0f}), input(input) {}

bool TextInput::drawTextInput(const char *label, bool &editMode) {
    if (IsMouseButtonPressed(0)) {
        if (CheckCollisionPointRec(GetMousePosition(), textInputBox)) {
            editMode = true;
        } else {
            editMode = false;
        }
    }

    drawDefaultText(textFont, label, {textInputBox.x, textInputBox.y - 30.0f});
    return GuiTextBox(textInputBox, input, MAX_INPUT_CHAR, editMode);
}
