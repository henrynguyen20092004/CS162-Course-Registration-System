#include "FormPage.h"

#include <algorithm>

#include "../Button/Button.h"
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
      mainBoxPosition(getCenterPosition(mainBoxSize)),
      buttonText(buttonText),
      errorText("") {
    inputWidth =
        (mainBoxSize.x - padding.x * 2 - DEFAULT_ITEM_MARGIN.x * (columns - 1)) / columns;
    childrenPosX = mainBoxPosition.x + padding.x;
    firstInputPosY = mainBoxPosition.y + padding.y + DEFAULT_TITLE_SIZE +
                     DEFAULT_TEXT_MARGIN.y + DEFAULT_TEXT_SIZE + DEFAULT_ITEM_MARGIN.y;
    inputs = new char *[numberOfTextInputs];
    textInputEditModes = new bool[numberOfTextInputs];
    inputPos = new Vector2[numberOfTextInputs + numberOfDropDowns];

    if (numberOfDropDowns) {
        dropDownItems = new char *[numberOfDropDowns];
        dropdownActiveItems = new int[numberOfDropDowns];
        dropdownEditModes = new bool[numberOfDropDowns];
    }

    for (int i = 0; i < numberOfTextInputs; ++i) {
        inputs[i] = new char[MAX_INPUT_CHAR];
        inputs[i][0] = '\0';
        textInputEditModes[i] = false;
        inputPos[i] = calculateInputPos(firstInputPosY, i);
    }

    for (int i = 0; i < numberOfDropDowns; ++i) {
        dropDownItems[i] = new char[MAX_INPUT_CHAR];
        dropDownItems[i][0] = '\0';
        dropdownActiveItems[i] = -1;
        dropdownEditModes[i] = false;
        inputPos[i + numberOfTextInputs] =
            calculateInputPos(firstInputPosY, i + numberOfTextInputs);
    }

    currentUser.username = UNKNOWN_USERNAME;

    menuDropDownItems = new char[MAX_INPUT_CHAR];
    menuDropDownItems[0] = '\0';
    menuDropdownActiveItems = -1;
    menuDropDownEditMode = false;

    defaultAvatar = LoadTexture("Pictures/DefaultAvatar.png");
}

Vector2 FormPage::calculateInputPos(float firstInputPosY, int index) {
    return {
        childrenPosX + (inputWidth + DEFAULT_ITEM_MARGIN.x) * (index % columns),
        firstInputPosY + (DEFAULT_ITEM_HEIGHT + DEFAULT_ITEM_MARGIN.y +
                          DEFAULT_TEXT_SIZE + DEFAULT_TEXT_MARGIN.y) *
                             (index / columns)};
}

void FormPage::drawPage() {
    if (currentUser.username != UNKNOWN_USERNAME) {
        drawMenu(
            currentUser.username, menuDropDownItems, menuDropdownActiveItems,
            menuDropDownEditMode, defaultAvatar
        );
    }

    drawFormBox();
}

void FormPage::drawFormBox() {
    Button submitButton(
        buttonText, getCenterX(inputWidth),
        mainBoxPosition.y + mainBoxSize.y - padding.y - DEFAULT_ITEM_HEIGHT, inputWidth
    );

    DrawRectangleV(mainBoxPosition, mainBoxSize, WHITE);
    drawDefaultTitle(titleFont, title, {childrenPosX, mainBoxPosition.y + padding.y});
    drawErrorText();

    for (int i = 0; i < numberOfDropDowns; ++i) {
        if (dropdownEditModes[i]) {
            GuiLock();
            break;
        }
    }

    if (submitButton.drawButton()) {
        submitCallBack();
    }

    drawFormInput();
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

FormPage::~FormPage() {
    for (int i = 0; i < numberOfTextInputs; ++i) {
        delete[] inputs[i];
    }

    for (int i = 0; i < numberOfDropDowns; ++i) {
        delete[] dropDownItems[i];
    }

    delete[] inputs;
    delete[] dropDownItems;
    delete[] dropdownActiveItems;
    delete[] dropdownEditModes;
    delete[] textInputEditModes;
    delete[] inputPos;
    delete[] menuDropDownItems;

    UnloadTexture(defaultAvatar);
}
