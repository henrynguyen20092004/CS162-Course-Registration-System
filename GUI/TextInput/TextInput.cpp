#include "TextInput.h"

#include "../TextFunction/TextFunction.h"

TextInput::TextInput()
    : textInputBox({0.0f, 0.0f, 0.0f, 0.0f}), input(nullptr), label(nullptr) {}

TextInput::TextInput(const char *label, char *input, Vector2 pos, float width)
    : textInputBox({pos.x, pos.y, width, DEFAULT_ITEM_HEIGHT}),
      input(input),
      label(label) {}

bool TextInput::drawTextInput() {
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
