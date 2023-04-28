#include <algorithm>

#include "../GetCenterPosition/GetCenterPosition.h"
#include "../TextFunction/TextFunction.h"
#include "TablePage.h"

template <typename T>
TablePage<T>::TablePage(
    const std::string &title, int col, int buttonCol, int headerButton,
    Node<T> *dataLinkedList
)

    : title(title),
      col(col),
      buttonCol(buttonCol),
      headerButton(headerButton),
      dataLinkedList(dataLinkedList) {
    row = getLinkedListSize(dataLinkedList) + 1;
    rowHeights = new int[row];
    tableData = new std::string *[row];

    for (int i = 0; i < row; ++i) {
        tableData[i] = new std::string[col + buttonCol];
    }

    if (headerButton) {
        headerButtons = new Button[headerButton];
        headerButtonTitles = new const char *[headerButton];
    }

    if (buttonCol) {
        firstRowButtonTitles = new const char *[buttonCol];
        columnButtons = new Button *[row - 1];

        for (int i = 0; i < row - 1; ++i) {
            columnButtons[i] = new Button[buttonCol];
        }
    }
}

template <typename T>
void TablePage<T>::clipData() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            tableData[i][j] =
                clipText(textFont, tableData[i][j].c_str(), columnWidths[j]);
        }
    }
}

template <typename T>
void TablePage<T>::addColumnsForButton() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < buttonCol; ++j) {
            tableData[i][j] = "";
        }
    }
}

template <typename T>
void TablePage<T>::calculateTableAndFirstRow() {
    for (int j = 0; j < col + buttonCol; ++j) {
        columnWidths[j] += TABLE_CELL_PADDING_X * 2;
        tableWidth += columnWidths[j];
    }

    tablePos = {
        getCenterX(tableWidth), MENU_HEIGHT + DEFAULT_ITEM_MARGIN.y + DEFAULT_PADDING.y};

    if (buttonCol) {
        firstRowButtonsPosX = tablePos.x + TABLE_CELL_PADDING_X +
                              (TABLE_BUTTON_CELL_WIDTH - TABLE_BUTTON_WIDTH) / 2.0f;

        for (int i = 0; i < col; ++i) {
            firstRowButtonsPosX += columnWidths[i];
        }
    }
}

template <typename T>
void TablePage<T>::generateRowHeights() {
    rowHeights = new int[row];

    for (int i = 0; i < row; ++i) {
        int maxNumberOfLines = 0;

        for (int j = 0; j < col; ++j) {
            int numberOfLines =
                std::count(tableData[i][j].begin(), tableData[i][j].end(), '\n') + 1;

            if (numberOfLines > maxNumberOfLines) {
                maxNumberOfLines = numberOfLines;
            }
        }

        rowHeights[i] =
            TABLE_CELL_HEIGHT + DEFAULT_TEXT_SIZE * (maxNumberOfLines * 1.5 - 0.5);
    }
}

template <typename T>
void TablePage<T>::generateButtons() {
    for (int i = 0; i < headerButton; ++i) {
        headerButtons[i] = Button(
            headerButtonTitles[i],
            tablePos.x + i * (TABLE_BUTTON_WIDTH * 3.0f + DEFAULT_ITEM_MARGIN.x),
            tablePos.y + DEFAULT_TITLE_SIZE + DEFAULT_ITEM_MARGIN.y,
            TABLE_BUTTON_WIDTH * 3.0f
        );
    }

    if (!buttonCol) {
        return;
    }

    float columnButtonY =
        tablePos.y + DEFAULT_ITEM_MARGIN.y + DEFAULT_TITLE_SIZE +
        (headerButton > 0) * (DEFAULT_ITEM_HEIGHT + DEFAULT_ITEM_MARGIN.y) +
        (TABLE_CELL_HEIGHT + DEFAULT_TEXT_SIZE - DEFAULT_ITEM_HEIGHT) / 2.0f;

    for (int i = 0; i < row - 1; ++i) {
        float columnButtonX = firstRowButtonsPosX;
        columnButtonY += rowHeights[i];

        for (int j = 0; j < buttonCol; ++j) {
            columnButtons[i][j] = Button(
                firstRowButtonTitles[j], columnButtonX, columnButtonY, TABLE_BUTTON_WIDTH
            );

            columnButtonX += TABLE_BUTTON_CELL_WIDTH + TABLE_CELL_PADDING_X * 2;
        }
    }
}

template <typename T>
void TablePage<T>::initComponents() {
    initColumns();
    addColumnsForButton();
    calculateTableAndFirstRow();
    initButtons();
    convertLinkedListToData();
    clipData();
    generateRowHeights();
    generateButtons();
    table = Table(
        tableData, columnTitle, title.c_str(), row, col, buttonCol, headerButton,
        rowHeights, columnWidths, tableWidth, columnButtonCommands, headerButtonCommands,
        tablePos, columnButtons, headerButtons
    );
}

template <typename T>
void TablePage<T>::createAndSortDataArray(T *&dataArray) {
    int arraySize;
    transformLinkedListToArray(dataLinkedList, dataArray, arraySize);
    std::sort(dataArray, dataArray + arraySize);
}

template <typename T>
void TablePage<T>::drawPage() {
    table.drawTable(stopLoop);
}

template <typename T>
TablePage<T>::~TablePage() {
    for (int i = 0; i < row; ++i) {
        delete[] tableData[i];
    }

    for (int i = 0; i < buttonCol; ++i) {
        delete[] columnButtons[i];
    }

    delete[] tableData;
    delete[] columnTitle;
    delete[] rowHeights;
    delete[] columnWidths;
    delete[] headerButtons;
    delete[] headerButtonTitles;
    delete[] headerButtonCommands;
    delete[] firstRowButtonTitles;
    delete[] columnButtons;
    delete[] columnButtonCommands;
}
