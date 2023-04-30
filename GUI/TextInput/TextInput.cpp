#include "TextInput.h"

#include <cstring>

#include "../TextFunction/TextFunction.h"

TextInput::TextInput() {}

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

bool TextInput::drawTextInput(float scrollY) {
    Rectangle textInputBoxWithScroll = textInputBox;
    textInputBoxWithScroll.y += scrollY;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        editMode = CheckCollisionPointRec(GetMousePosition(), textInputBoxWithScroll) &&
                   !GuiIsLocked();
    }

    drawDefaultText(
        label, {textInputBoxWithScroll.x,
                textInputBoxWithScroll.y - DEFAULT_TEXT_SIZE - DEFAULT_TEXT_MARGIN.y}
    );

    if (!editMode && measureTextWidth(textFont, input) > width) {
        truncateInput();
        return GuiTextBox(
            textInputBoxWithScroll, truncatedInput.data(), MAX_INPUT_CHAR, editMode
        );
    }

    return GuiTextBox(textInputBoxWithScroll, input, MAX_INPUT_CHAR, editMode);
}
