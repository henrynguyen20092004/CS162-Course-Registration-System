#include "Table.h"

#include "../DrawScrollBar/DrawScrollBar.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../TextFunction/TextFunction.h"

Table::Table() {}

Table::Table(
    std::string** tableData, std::string* columnTitle, const char* tableTitle, int row,
    int col, int buttonCol, int headerButton, int* rowHeights, float* columnWidths,
    float tableWidth, Vector2 tablePos, Button** columnButtons, Button* headerButtons
)
    : tableData(tableData),
      columnTitle(columnTitle),
      tableTitle(tableTitle),
      row(row),
      col(col),
      headerButton(headerButton),
      buttonCol(buttonCol),
      rowHeights(rowHeights),
      columnWidths(columnWidths),
      tableWidth(tableWidth),
      tablePos(tablePos),
      columnButtons(columnButtons),
      headerButtons(headerButtons) {
    tableHeight = DEFAULT_TITLE_SIZE + DEFAULT_ITEM_MARGIN.y;
    tableOffsetY = (headerButton > 0) * (DEFAULT_ITEM_HEIGHT + DEFAULT_ITEM_MARGIN.y);

    for (int i = 0; i < row; ++i) {
        tableHeight += rowHeights[i];
    }

    backgroundHeight = tableHeight + DEFAULT_PADDING.y * 2 + tableOffsetY;
    initialTextPos = {
        tablePos.x + TABLE_CELL_PADDING_X,
        tablePos.y + DEFAULT_TITLE_SIZE + DEFAULT_ITEM_MARGIN.y +
            (rowHeights[0] - DEFAULT_TEXT_SIZE) / 2.0f + tableOffsetY};
}

void Table::drawGrid() {
    Vector2 cellPos = tablePos;

    for (int j = 0; j < col + buttonCol; ++j) {
        cellPos.y = tablePos.y + DEFAULT_TITLE_SIZE + DEFAULT_ITEM_MARGIN.y +
                    tableOffsetY + scroll.y;

        if (j > 0) {
            cellPos.x += columnWidths[j - 1];
        }

        for (int i = 0; i < row; ++i) {
            if (i > 0) {
                cellPos.y += rowHeights[i - 1];
            }

            DrawRectangleLines(
                cellPos.x, cellPos.y, columnWidths[j], rowHeights[i], BLACK
            );
        }
    }
}

void Table::drawText() {
    Vector2 textPos = initialTextPos;

    for (int j = 0; j < col + buttonCol; ++j) {
        textPos.y = initialTextPos.y + scroll.y;

        for (int i = 0; i < row; ++i) {
            float textSize = measureTextWidth(textFont, tableData[i][j].c_str());

            if (j < 2) {
                textPos.x += (columnWidths[j] - textSize) / 2 - TABLE_CELL_PADDING_X;
            }

            drawDefaultText(textFont, tableData[i][j].c_str(), textPos, BLACK);
            textPos.y += rowHeights[i];

            if (j < 2) {
                textPos.x -= (columnWidths[j] - textSize) / 2 - TABLE_CELL_PADDING_X;
            }
        }

        textPos.x += columnWidths[j];
    }
}

void Table::drawButton() {
    for (int i = 0; i < headerButton; ++i) {
        if (headerButtons[i].drawButton(scroll.y)) {
            std::cout << "Hi\n";
        }
    }

    for (int i = 0; i < 3; ++i) {
        GuiSetStyle(BUTTON, i * 3, 0xffffffff);
        GuiSetStyle(BUTTON, i * 3 + 1, 0xffffffff);
    }

    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0x0b182fff);

    for (int i = 0; i < row - 1; ++i) {
        for (int j = 0; j < buttonCol; ++j) {
            if (columnButtons[i][j].drawButton(scroll.y)) {
                std::cout << "Ho " << tableData[i + 1][1] << '\n';
            }
        }
    }

    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x838383ff);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x063970ff);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xffffffff);
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, 0x5bb2d9ff);
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0xc9effeff);
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, 0x0492c7ff);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0x97e8ffff);
}

void Table::drawTable() {
    drawScrollBar(
        {0, MENU_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - MENU_HEIGHT}, nullptr,
        {tablePos.x, tablePos.y, tableWidth,
         backgroundHeight + DEFAULT_ITEM_MARGIN.y * 2},
        scroll
    );
    DrawRectangleV(
        {tablePos.x - DEFAULT_PADDING.x, tablePos.y - DEFAULT_PADDING.y + scroll.y},
        {tableWidth + DEFAULT_PADDING.x * 2, backgroundHeight}, WHITE
    );
    drawDefaultTitle(
        titleFont, tableTitle,
        {getCenterX(measureTextWidth(titleFont, tableTitle)), tablePos.y + scroll.y}
    );
    drawText();
    drawButton();
    drawGrid();
}
