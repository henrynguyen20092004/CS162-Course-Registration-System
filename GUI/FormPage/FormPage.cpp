#include "FormPage.h"

#include <algorithm>

#include "../DrawScrollBar/DrawScrollBar.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../TextFunction/TextFunction.h"

FormPage::FormPage(
    const std::string &title, int numberOfTextInputs, int numberOfDropDowns, int columns,
    Vector2 mainBoxSize, Command backButtonCommand
)
    : title(title),
      backButtonText("#114#Back"),
      numberOfTextInputs(numberOfTextInputs),
      numberOfDropDowns(numberOfDropDowns),
      columns(columns),
      mainBoxSize(
          {mainBoxSize.x, mainBoxSize.y + (DEFAULT_ITEM_HEIGHT + DEFAULT_ITEM_MARGIN.y)}
      ),
      backButtonCommand(backButtonCommand) {
    mainBoxPos = {getCenterX(mainBoxSize.x), getCenterY(mainBoxSize.y) + 45.0f};
    inputWidth =
        (mainBoxSize.x - DEFAULT_PADDING.x * 2 - DEFAULT_ITEM_MARGIN.x * (columns - 1)) /
        columns;
    childrenPosX = mainBoxPos.x + DEFAULT_PADDING.x;
    titlePosY =
        mainBoxPos.y + DEFAULT_PADDING.y + DEFAULT_ITEM_HEIGHT + DEFAULT_ITEM_MARGIN.y;
    firstInputPosY = titlePosY + DEFAULT_TITLE_SIZE + DEFAULT_TEXT_MARGIN.y +
                     DEFAULT_TEXT_SIZE + DEFAULT_ITEM_MARGIN.y;
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

void FormPage::initComponents() {
    submitButton = Button(
        "Submit", getCenterX(inputWidth),
        mainBoxPos.y + mainBoxSize.y - DEFAULT_PADDING.y - DEFAULT_ITEM_HEIGHT, inputWidth
    );
    backButton = Button(
        backButtonText, mainBoxPos.x + mainBoxSize.x - DEFAULT_PADDING.x - 80.0f,
        mainBoxPos.y + DEFAULT_PADDING.y + scroll.y, 80.0f
    );
    initInputs();

    if (dropDowns) {
        for (int i = 0; i < numberOfDropDowns; ++i) {
            int numberOfItems =
                std::count(dropDowns[i].items.begin(), dropDowns[i].items.end(), ';') + 1;
            float maxHeight = dropDowns[i].dropDownBox.y +
                              dropDowns[i].dropDownBox.height * numberOfItems;

            if (maxHeight > pageHeight) {
                pageHeight = maxHeight;
            }
        }
    }
}

void FormPage::drawPage() {
    if (pageHeight > SCREEN_HEIGHT - MENU_HEIGHT) {
        drawScrollBar(
            {0, MENU_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - MENU_HEIGHT}, nullptr,
            {mainBoxPos.x, mainBoxPos.y, mainBoxSize.x, pageHeight}, scroll
        );
    }

    DrawRectangleV({mainBoxPos.x, mainBoxPos.y + scroll.y}, mainBoxSize, WHITE);
    drawDefaultTitle(titleFont, title.c_str(), {childrenPosX, titlePosY + scroll.y});
    drawErrorText();
    dropDownLockGUI();

    if (submitButton.drawButton(scroll.y)) {
        submit();
    }

    if (backButton.drawButton(scroll.y)) {
        commandChoice = backButtonCommand;
        stopLoop = true;
    }

    drawInputs();
}

void FormPage::drawInputs() {
    for (int i = 0; i < numberOfTextInputs; ++i) {
        if (textInputs[i].drawTextInput(scroll.y)) {
            submit();
        }
    }

    for (int i = numberOfDropDowns - 1; i >= 0; --i) {
        dropDowns[i].drawDropDown(dropDownItems[i], scroll.y);
    }
}

void FormPage::drawErrorText() {
    if (errorText == "") {
        return;
    }

    errorText = clipText(textFont, errorText.c_str(), inputWidth);
    int numberOfLines = std::count(errorText.begin(), errorText.end(), '\n') + 1;

    float posY = mainBoxPos.y + mainBoxSize.y - DEFAULT_PADDING.y - DEFAULT_ITEM_HEIGHT -
                 DEFAULT_TEXT_SIZE * (numberOfLines * 1.5 - 0.5) - DEFAULT_TEXT_MARGIN.y +
                 scroll.y;

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
        errorText = "";
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
