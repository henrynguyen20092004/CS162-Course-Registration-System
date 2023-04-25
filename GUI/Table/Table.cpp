#include "Table.h"

#include "../DrawScrollBar/DrawScrollBar.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../TextFunction/TextFunction.h"

Table::Table() {}

Table::Table(
    std::string** tableData, std::string* columnTitle, const char* tableTitle, int row,
    int col, int buttonCol, int headerButton, int* rowHeights, float* columnWidths,
    float tableWidth, Vector2 tablePos
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
      tablePos(tablePos) {
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

void Table::drawGrid(float scrollY) {
    Vector2 cellPos = tablePos;

    for (int j = 0; j < col + buttonCol; ++j) {
        cellPos.y = tablePos.y + DEFAULT_TITLE_SIZE + DEFAULT_ITEM_MARGIN.y +
                    tableOffsetY + scrollY;

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

void Table::drawText(float scrollY) {
    Vector2 textPos = initialTextPos;

    for (int j = 0; j < col + buttonCol; ++j) {
        textPos.y = initialTextPos.y + scrollY;

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

void Table::drawTable(Vector2& scroll) {
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
    drawText(scroll.y);
    drawGrid(scroll.y);
}
