#include <algorithm>

#include "../../GlobalVar/GlobalVar.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../TextFunction/TextFunction.h"
#include "TablePage.h"

template <class T>
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

template <class T>
void TablePage<T>::clipData() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            tableData[i][j] =
                clipText(GlobalVar::textFont, tableData[i][j].c_str(), columnWidths[j]);
        }
    }
}

template <class T>
void TablePage<T>::addColumnsForButton() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < buttonCol; ++j) {
            tableData[i][j] = "";
        }
    }
}

template <class T>
void TablePage<T>::calculateTableAndFirstRow() {
    for (int j = 0; j < col + buttonCol; ++j) {
        columnWidths[j] += TABLE_CELL_PADDING_X * 2;
        tableWidth += columnWidths[j];
    }

    tablePos = {
        tableWidth > SCREEN_WIDTH - DEFAULT_PADDING.x * 4 ? DEFAULT_PADDING.x * 2
                                                          : getCenterX(tableWidth),
        MENU_HEIGHT + DEFAULT_ITEM_MARGIN.y + DEFAULT_PADDING.y};

    if (buttonCol) {
        firstRowButtonsPosX = tablePos.x + TABLE_CELL_PADDING_X;

        for (int i = 0; i < col; ++i) {
            firstRowButtonsPosX += columnWidths[i];
        }
    }
}

template <class T>
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

template <class T>
void TablePage<T>::generateButtons() {
    for (int i = 0; i < headerButton; ++i) {
        headerButtons[i] = Button(
            headerButtonTitles[i], tablePos.x + i * (250.0f + DEFAULT_ITEM_MARGIN.x),
            tablePos.y + DEFAULT_TITLE_SIZE + DEFAULT_ITEM_MARGIN.y, 250.0f
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
            columnButtons[i][j] =
                Button(firstRowButtonTitles[j], columnButtonX, columnButtonY, 80.0f);

            columnButtonX += TABLE_BUTTON_CELL_WIDTH + TABLE_CELL_PADDING_X * 2;
        }
    }
}

template <class T>
void TablePage<T>::initComponents() {
    initColumns();
    addColumnsForButton();
    convertLinkedListToData();
    clipData();
    calculateTableAndFirstRow();
    initButtons();
    generateRowHeights();
    generateButtons();
    table = Table(
        tableData, columnTitle, title.c_str(), row, col, buttonCol, headerButton,
        rowHeights, columnWidths, tableWidth, tablePos
    );
}

template <class T>
void TablePage<T>::createAndSortDataArray(T *&dataArray) {
    int arraySize;
    transformLinkedListToArray(dataLinkedList, dataArray, arraySize);
    std::sort(dataArray, dataArray + arraySize);
}

template <class T>
void TablePage<T>::drawPage() {
    table.drawTable(scroll);
    drawButtons();
}

template <class T>
void TablePage<T>::drawButtons() {
    for (int i = 0; i < headerButton; ++i) {
        if (headerButtons[i].drawButton(scroll)) {
            GlobalVar::previousCommand = GlobalVar::currentCommand;
            GlobalVar::currentCommand = headerButtonCommands[i];
            stopLoop = true;
        }
    }

    for (int i = 0; i < 3; ++i) {
        GuiSetStyle(BUTTON, i * 3, 0xffffffff);
        GuiSetStyle(BUTTON, i * 3 + 1, 0xffffffff);
    }

    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0x0b182fff);
    drawColumnButtons();
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x838383ff);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x063970ff);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xffffffff);
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, 0x5bb2d9ff);
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0xc9effeff);
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, 0x0492c7ff);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0x97e8ffff);
}

template <class T>
void TablePage<T>::drawColumnButtons() {
    for (int i = 0; i < row - 1; ++i) {
        for (int j = 0; j < buttonCol; ++j) {
            if (columnButtons[i][j].drawButton(scroll)) {
                GlobalVar::renderArgs = tableData[i + 1][1];
                GlobalVar::previousCommand = GlobalVar::currentCommand;
                GlobalVar::currentCommand = columnButtonCommands[j];
                stopLoop = true;
            }
        }
    }
}

template <class T>
TablePage<T>::~TablePage() {
    for (int i = 0; i < row; ++i) {
        delete[] tableData[i];
    }

    if (buttonCol) {
        for (int i = 0; i < row - 1; ++i) {
            delete[] columnButtons[i];
        }

        delete[] firstRowButtonTitles;
        delete[] columnButtons;
        delete[] columnButtonCommands;
    }

    delete[] tableData;
    delete[] columnTitle;
    delete[] rowHeights;
    delete[] columnWidths;
    delete[] headerButtons;
    delete[] headerButtonTitles;
    delete[] headerButtonCommands;
}
