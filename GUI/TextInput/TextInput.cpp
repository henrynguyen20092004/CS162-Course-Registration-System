#include "TextInput.h"

#include "../TextFunction/TextFunction.h"

TextInput::TextInput() : textInputBox({0.0f, 0.0f, 0.0f, 0.0f}), input(nullptr) {}

TextInput::TextInput(char *input, Vector2 pos, float width)
    : textInputBox({pos.x, pos.y, width, DEFAULT_ITEM_HEIGHT}), input(input) {}

bool TextInput::drawTextInput(const char *label) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        editMode =
            CheckCollisionPointRec(GetMousePosition(), textInputBox) && !GuiIsLocked();
    }

    drawDefaultText(
        textFont, label,
        {textInputBox.x, textInputBox.y - DEFAULT_TEXT_SIZE - DEFAULT_TEXT_MARGIN.y}
    );
    return GuiTextBox(textInputBox, input, MAX_INPUT_CHAR, editMode);
}
