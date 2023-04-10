#include "FormPage.h"

#include "../Button/Button.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../TextFunction/TextFunction.h"

FormPage::FormPage(
    const char *title, int numberOfInputs, int columns, Vector2 mainBoxSize,
    const char *buttonText, Vector2 padding
)
    : title(title),
      numberOfInputs(numberOfInputs),
      columns(columns),
      mainBoxSize(mainBoxSize),
      padding(padding),
      mainBoxPosition(getCenterPosition(mainBoxSize)),
      buttonText(buttonText),
      errorText("") {
    inputWidth =
        (mainBoxSize.x - padding.x * 2 - DEFAULT_ITEM_MARGIN.x * (columns - 1)) / columns;
    childrenPosX = mainBoxPosition.x + padding.x;
    firstInputPosY = mainBoxPosition.y + padding.y + DEFAULT_TITLE_SIZE +
                     DEFAULT_TEXT_MARGIN.y + DEFAULT_TEXT_SIZE + DEFAULT_ITEM_MARGIN.y;
    inputs = new char *[numberOfInputs];
    editModes = new bool[numberOfInputs];
    inputPos = new Vector2[numberOfInputs];

    for (int i = 0; i < numberOfInputs; i++) {
        inputs[i] = new char[MAX_INPUT_CHAR];
        inputs[i][0] = '\0';
        editModes[i] = false;
        inputPos[i] = calculateInputPos(firstInputPosY, i);
    }
}

Vector2 FormPage::calculateInputPos(float firstInputPosY, int index) {
    return {
        childrenPosX + (inputWidth + DEFAULT_ITEM_MARGIN.x) * (index % columns),
        firstInputPosY + (DEFAULT_ITEM_HEIGHT + DEFAULT_ITEM_MARGIN.y +
                          DEFAULT_TEXT_SIZE + DEFAULT_TEXT_MARGIN.y) *
                             (index / columns)};
}

void FormPage::drawPage() { drawFormBox(); }

void FormPage::drawFormBox() {
    Button submitButton(
        buttonText, getCenterX(inputWidth),
        mainBoxPosition.y + mainBoxSize.y - padding.y - DEFAULT_ITEM_HEIGHT, inputWidth
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

    drawDefaultText(
        textFont, errorText.c_str(), {getCenterX(inputWidth), posY}, ERROR_TEXT_COLOR
    );
}

FormPage::~FormPage() {
    for (int i = 0; i < numberOfInputs; i++) {
        delete[] inputs[i];
    }

    delete[] inputs;
    delete[] editModes;
    delete[] inputPos;
}
