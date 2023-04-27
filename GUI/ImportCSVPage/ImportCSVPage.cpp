#include "ImportCSVPage.h"

#include "../../Function/DownloadTemplateCSV/DownloadTemplateCSV.h"
#include "../OpenDialog/OpenDialog.h"

ImportCSVPage::ImportCSVPage(
    const char *title, const char *CSVName, void (*importCallBack)(char **, char **)
)
    : FormPage(title, 2, 2, 1, {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 1.5f}),
      CSVName(CSVName),
      importCallBack(importCallBack) {}

void ImportCSVPage::initInputs() {
    float browseButtonWidth = 140.0f,
          textInputWidth = inputWidth - DEFAULT_ITEM_MARGIN.x - browseButtonWidth,
          browseButtonPosX = inputPos[1].x + inputWidth - browseButtonWidth;
    dropDowns[0] = DropDown(
        "What do you want to do?", "Download the template;Continue importing the CSV",
        inputPos[0], inputWidth
    );
    textInputs[0] =
        TextInput("Download folder path", inputs[0], inputPos[1], textInputWidth);
    textInputs[1] = TextInput("CSV path", inputs[1], inputPos[1], textInputWidth);
    browseFolderButton =
        Button("Select folder", browseButtonPosX, inputPos[1].y, browseButtonWidth);
    browseFileButton =
        Button("Select file", browseButtonPosX, inputPos[1].y, browseButtonWidth);
}

void ImportCSVPage::drawInputs() {
    switch (dropDowns[0].activeItemIndex) {
        case 0: {
            if (browseFolderButton.drawButton(scroll.y)) {
                openFolderDialog(inputs[0]);
            }

            if (textInputs[0].drawTextInput(scroll.y)) {
                submit();
            }

            break;
        }
        case 1: {
            if (browseFileButton.drawButton(scroll.y)) {
                openFileDialog(inputs[1]);
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
