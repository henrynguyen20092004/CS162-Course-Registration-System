#include "Table.h"

#include "../../GlobalVar/GlobalVar.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../ScrollBar/ScrollBar.h"
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

void Table::drawGrid(const Vector2& scroll) {
    Vector2 cellPos = tablePos;
    cellPos.x += scroll.x;

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

void Table::drawText(const Vector2& scroll) {
    Vector2 textPos = initialTextPos;
    textPos.x += scroll.x;

    for (int j = 0; j < col + buttonCol; ++j) {
        textPos.y = initialTextPos.y + scroll.y;

        for (int i = 0; i < row; ++i) {
            float textSize =
                measureTextWidth(GlobalVar::textFont, tableData[i][j].c_str());

            if (j < 2) {
                textPos.x += (columnWidths[j] - textSize) / 2 - TABLE_CELL_PADDING_X;
            }

            drawDefaultText(tableData[i][j].c_str(), textPos, BLACK);
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
        {tablePos.x, tablePos.y, tableWidth + DEFAULT_PADDING.x * 4,
         backgroundHeight + DEFAULT_ITEM_MARGIN.y * 2},
        scroll
    );
    DrawRectangleV(
        {tablePos.x - DEFAULT_PADDING.x + scroll.x,
         tablePos.y - DEFAULT_PADDING.y + scroll.y},
        {tableWidth + DEFAULT_PADDING.x * 2, backgroundHeight}, WHITE
    );
    drawDefaultTitle(
        tableTitle,
        {getCenterX(measureTextWidth(GlobalVar::titleFont, tableTitle)) + scroll.x,
         tablePos.y + scroll.y}
    );
    drawText(scroll);
    drawGrid(scroll);
}
