#include "ImportCSVPage.h"

#include <stdexcept>

#include "../../API/DownloadTemplateCSV/DownloadTemplateCSV.h"
#include "../FileFolderDialog/FileFolderDialog.h"

ImportCSVPage::ImportCSVPage(
    const std::string &title, const char *CSVName, const std::string &arg,
    void (*importCallBack)(char **, char **, const std::string &arg)
)
    : FormPage(title, 2, 1, 1, {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 1.5f}),
      CSVName(CSVName),
      arg(arg),
      importCallBack(importCallBack) {}

void ImportCSVPage::initInputs() {
    float browseButtonWidth = 140.0f,
          textInputWidth = inputWidth - DEFAULT_ITEM_MARGIN.x - browseButtonWidth,
          browseButtonPosX = inputPos[1].x + inputWidth - browseButtonWidth;
    dropDowns[0] = DropDown(
        "What do you want to do?", "Download the template;Import the CSV", inputPos[0],
        inputWidth
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
            if (browseFolderButton.drawButton(scroll)) {
                openFolderDialog(inputs[0]);
            }

            if (textInputs[0].drawTextInput(scroll.y)) {
                submit();
            }

            break;
        }
        case 1: {
            if (browseFileButton.drawButton(scroll)) {
                openFileDialog(inputs[1]);
            }

            if (textInputs[1].drawTextInput(scroll.y)) {
                submit();
            }
        }
    }

    if (dropDowns[0].drawDropDown(dropDownItems[0], scroll.y)) {
        successText = "";
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
            if (inputs[1][0] == '\0') {
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
            successText = "CSV successfully downloaded!";
            break;
        }
        case 1: {
            try {
                importCallBack(inputs, dropDownItems, arg);
            } catch (std::runtime_error &error) {
                successText = "CSV successfully imported!";
                errorText = error.what();
            }
            break;
        }
    }
}
