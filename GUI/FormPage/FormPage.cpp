#include "FormPage.h"

#include <algorithm>

#include "../DrawMenu/DrawMenu.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../TextFunction/TextFunction.h"

FormPage::FormPage(
    const char *title, int numberOfTextInputs, int numberOfDropDowns, int columns,
    Vector2 mainBoxSize, const char *buttonText, Vector2 padding
)
    : title(title),
      numberOfTextInputs(numberOfTextInputs),
      numberOfDropDowns(numberOfDropDowns),
      columns(columns),
      mainBoxSize(mainBoxSize),
      padding(padding),
      mainBoxPosition(
          {getCenterX(mainBoxSize.x), getCenterY(mainBoxSize.y) + PAGE_Y_OFFSET}
      ),
      buttonText(buttonText) {
    inputWidth =
        (mainBoxSize.x - padding.x * 2 - DEFAULT_ITEM_MARGIN.x * (columns - 1)) / columns;
    childrenPosX = mainBoxPosition.x + padding.x;
    firstInputPosY = mainBoxPosition.y + padding.y + DEFAULT_TITLE_SIZE +
                     DEFAULT_TEXT_MARGIN.y + DEFAULT_TEXT_SIZE + DEFAULT_ITEM_MARGIN.y;
    inputs = new char *[numberOfTextInputs];
    textInputs = new TextInput[numberOfTextInputs];
    inputPos = new Vector2[numberOfTextInputs + numberOfDropDowns];

    if (numberOfDropDowns) {
        dropDownItems = new char *[numberOfDropDowns];
        dropDowns = new DropDown[numberOfDropDowns];
    }

    for (int i = 0; i < numberOfTextInputs; ++i) {
        inputs[i] = new char[MAX_INPUT_CHAR];
        inputs[i][0] = '\0';
        inputPos[i] = calculateInputPos(firstInputPosY, i);
    }

    for (int i = 0; i < numberOfDropDowns; ++i) {
        dropDownItems[i] = new char[MAX_INPUT_CHAR];
        dropDownItems[i][0] = '\0';
        inputPos[i + numberOfTextInputs] =
            calculateInputPos(firstInputPosY, i + numberOfTextInputs);
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

void FormPage::initComponents() {
    submitButton = Button(
        buttonText, getCenterX(inputWidth),
        mainBoxPosition.y + mainBoxSize.y - padding.y - DEFAULT_ITEM_HEIGHT, inputWidth
    );
}

void FormPage::drawFormBox() {
    DrawRectangleV(mainBoxPosition, mainBoxSize, WHITE);
    drawDefaultTitle(titleFont, title, {childrenPosX, mainBoxPosition.y + padding.y});
    drawErrorText();
    dropDownLockGUI();
    passwordHide();

    if (submitButton.drawButton()) {
        submit();
    }

    for (int i = 0; i < numberOfTextInputs; ++i) {
        if (textInputs[i].drawTextInput()) {
            submit();
        }
    }

    for (int i = numberOfDropDowns - 1; i >= 0; --i) {
        dropDowns[i].drawDropDown(dropDownItems[i]);
    }
}

void FormPage::drawErrorText() {
    if (errorText == "") {
        return;
    }

    errorText = clipText(textFont, errorText.c_str(), inputWidth);
    int numberOfLines = std::count(errorText.begin(), errorText.end(), '\n') + 1;

    float posY = mainBoxPosition.y + mainBoxSize.y - padding.y - DEFAULT_ITEM_HEIGHT -
                 DEFAULT_TEXT_SIZE * (numberOfLines * 1.5 - 0.5) - DEFAULT_TEXT_MARGIN.y;

    drawDefaultText(
        textFont, errorText.c_str(), {getCenterX(inputWidth), posY}, ERROR_TEXT_COLOR
    );
}

void FormPage::dropDownLockGUI() {
    for (int i = 0; i < numberOfDropDowns; ++i) {
        if (dropDowns[i].editMode) {
            GuiLock();
            return;
        }
    }

    GuiUnlock();
}

void FormPage::checkFilledFields() {
    for (int i = 0; i < numberOfTextInputs; ++i) {
        if (inputs[i][0] == '\0') {
            throw std::invalid_argument("Please fill all fields before submitting!");
        }
    }

    for (int i = 0; i < numberOfDropDowns; ++i) {
        if (dropDownItems[i][0] == '\0') {
            throw std::invalid_argument("Please fill all fields before submitting!");
        }
    }
}

void FormPage::submit() {
    try {
        checkFilledFields();
        submitCallBack();
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

FormPage::~FormPage() {
    for (int i = 0; i < numberOfTextInputs; ++i) {
        delete[] inputs[i];
    }

    for (int i = 0; i < numberOfDropDowns; ++i) {
        delete[] dropDownItems[i];
    }

    delete[] inputs;
    delete[] textInputs;
    delete[] dropDownItems;
    delete[] dropDowns;
    delete[] inputPos;
}
