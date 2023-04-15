#include "TextInput.h"

#include "../GlobalStyle.h"
#include "../TextFunction/TextFunction.h"

TextInput::TextInput(char *input, Vector2 pos, float width)
    : textInputBox({pos.x, pos.y, width, DEFAULT_ITEM_HEIGHT}), input(input) {}

bool TextInput::drawTextInput(const char *label, bool &editMode) {
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
