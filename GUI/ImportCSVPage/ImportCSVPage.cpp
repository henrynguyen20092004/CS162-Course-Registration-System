#include "ImportCSVPage.h"

#include "../../Function/DownloadTemplateCSV/DownloadTemplateCSV.h"
#include "../DrawFileDialog/DrawFileDialog.h"

ImportCSVPage::ImportCSVPage(
    const char *title, const char *CSVName, Vector2 mainBoxSize,
    void (*importCallBack)(char **, char **)
)
    : FormPage(title, 2, 2, 1, mainBoxSize),
      CSVName(CSVName),
      importCallBack(importCallBack) {}

void ImportCSVPage::initInputs() {
    float openFileButtonWidth = 120.0f;

    dropDowns[0] = DropDown(
        "What do you want to do?", "Download a template;Continue importing the CSV",
        inputPos[0], inputWidth
    );
    textInputs[0] = TextInput("Download folder path", inputs[0], inputPos[1], inputWidth);
    textInputs[1] = TextInput(
        "CSV path", inputs[1], inputPos[1],
        inputWidth - DEFAULT_ITEM_MARGIN.x - openFileButtonWidth
    );
    openFileButton = Button(
        "Browse file", inputPos[1].x + inputWidth - openFileButtonWidth, inputPos[1].y,
        openFileButtonWidth
    );
}

void ImportCSVPage::drawInputs() {
    switch (dropDowns[0].activeItemIndex) {
        case 0: {
            if (textInputs[0].drawTextInput(scroll.y)) {
                submit();
            }

            break;
        }
        case 1: {
            if (openFileButton.drawButton(scroll.y)) {
                openFileDialog(inputs[1], "CSV File\0*.csv");
            }

            if (textInputs[1].drawTextInput(scroll.y)) {
                submit();
            }

            dropDowns[1].drawDropDown(dropDownItems[1], scroll.y);
            break;
        }
    }

    if (dropDowns[0].drawDropDown(dropDownItems[0], scroll.y)) {
        errorText = "";
    }
}

void ImportCSVPage::checkFilledFields() {
    switch (dropDowns[0].activeItemIndex) {
        case -1: {
            throw std::invalid_argument("Please fill all fields before submitting!");
        }
        case 0: {
            if (inputs[0][0] == '\0') {
                throw std::invalid_argument("Please fill all fields before submitting!");
            }
            break;
        }
        case 1: {
            if (inputs[1][0] == '\0' || dropDownItems[1][0] == '\0') {
                throw std::invalid_argument("Please fill all fields before submitting!");
            }
            break;
        }
    }
}

void ImportCSVPage::submitCallBack() {
    switch (dropDowns[0].activeItemIndex) {
        case 0: {
            downloadTemplateCSV(CSVName, inputs[0]);
            break;
        }
        case 1: {
            importCallBack(inputs, dropDownItems);
            break;
        }
    }
}
