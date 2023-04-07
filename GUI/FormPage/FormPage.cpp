#include "FormPage.h"

#include "../Button/Button.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../TextFunction/TextFunction.h"

FormPage::FormPage(
    const char *title, int numberOfInputs, float firstInputPosY, Vector2 mainBoxSize,
    Vector2 padding
)
    : title(title),
      numberOfInputs(numberOfInputs),
      mainBoxSize(mainBoxSize),
      padding(padding),
      mainBoxPosition(getCenterPosition(mainBoxSize)),
      errorText("") {
    childrenPosX = mainBoxPosition.x + padding.x;
    inputs = new char *[numberOfInputs];
    editModes = new bool[numberOfInputs];
    inputPosY = new float[numberOfInputs];

    for (int i = 0; i < numberOfInputs; i++) {
        inputs[i] = new char[MAX_INPUT_CHAR];
        inputs[i][0] = '\0';
        editModes[i] = false;
        inputPosY[i] = firstInputPosY + i * (DEFAULT_ITEM_HEIGHT + DEFAULT_ITEM_MARGIN.y +
                                             DEFAULT_TEXT_SIZE + DEFAULT_TEXT_MARGIN.y);
    }
}

void FormPage::drawPage() { drawFormBox(); }

void FormPage::drawFormBox() {
    Button submitButton(
        "Submit", mainBoxPosition.y + mainBoxSize.y - padding.y - DEFAULT_ITEM_HEIGHT
    );

    DrawRectangleV(mainBoxPosition, mainBoxSize, WHITE);
    drawDefaultTitle(titleFont, title, {childrenPosX, mainBoxPosition.y + padding.y});
    drawFormInput();
    drawErrorText();

    if (submitButton.drawButton()) {
        submitCallBack();
    }
}

void FormPage::drawErrorText() {
    float posY = mainBoxPosition.y + mainBoxSize.y - padding.y - DEFAULT_TEXT_SIZE -
                 DEFAULT_ITEM_HEIGHT - DEFAULT_TEXT_MARGIN.y;

    drawDefaultText(textFont, errorText, {childrenPosX, posY}, ERROR_TEXT_COLOR);
}

FormPage::~FormPage() {
    for (int i = 0; i < numberOfInputs; i++) {
        delete[] inputs[i];
    }

    delete[] inputs;
    delete[] editModes;
}
