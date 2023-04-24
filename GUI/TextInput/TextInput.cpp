#include "TextInput.h"

#include <cstring>

#include "../TextFunction/TextFunction.h"

TextInput::TextInput()
    : textInputBox({0.0f, 0.0f, 0.0f, 0.0f}),
      input(nullptr),
      label(nullptr),
      width(0.0f) {}

TextInput::TextInput(const char *label, char *input, Vector2 pos, float width)
    : textInputBox({pos.x, pos.y, width, DEFAULT_ITEM_HEIGHT}),
      input(input),
      label(label),
      width(width - GuiGetStyle(TEXTBOX, TEXT_PADDING) * 2) {}

void TextInput::truncateInput() {
    truncatedInput = "";

    for (int i = 0; input[i] != '\0'; ++i) {
        truncatedInput += input[i];

        if (measureTextWidth(textFont, truncatedInput.c_str()) > width) {
            truncatedInput[i + 1] = '\0';

            for (int j = i - 2; j <= i; ++j) {
                truncatedInput[j] = '.';
            }

            break;
        }
    }
}

bool TextInput::drawTextInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        editMode =
            CheckCollisionPointRec(GetMousePosition(), textInputBox) && !GuiIsLocked();
    }

    drawDefaultText(
        textFont, label,
        {textInputBox.x, textInputBox.y - DEFAULT_TEXT_SIZE - DEFAULT_TEXT_MARGIN.y}
    );

    if (!editMode && measureTextWidth(textFont, input) > width) {
        truncateInput();
        return GuiTextBox(textInputBox, truncatedInput.data(), MAX_INPUT_CHAR, editMode);
    }

    return GuiTextBox(textInputBox, input, MAX_INPUT_CHAR, editMode);
}
