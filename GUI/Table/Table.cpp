#include "Table.h"

#include <algorithm>

#include "../GetCenterPosition/GetCenterPosition.h"
#include "../TextFunction/TextFunction.h"

Table::Table()
    : tableData(nullptr),
      columnTitle(nullptr),
      tableTitle(nullptr),
      row(0),
      col(0),
      rowHeights(nullptr),
      columnWidths(nullptr),
      tablePos({0.0f, 0.0f}),
      initialTextPosition({0.0f, 0.0f}) {}

Table::Table(
    std::string** tableData, std::string* columnTitle, const char* tableTitle, int row,
    int col, int* rowHeights, float* columnWidths, float tablePosY
)
    : tableData(tableData),
      columnTitle(columnTitle),
      tableTitle(tableTitle),
      row(row),
      col(col),
      rowHeights(rowHeights),
      columnWidths(columnWidths) {
    tableHeight = DEFAULT_TITLE_SIZE + DEFAULT_ITEM_MARGIN.y;

    for (int j = 0; j < col; ++j) {
        columnWidths[j] += TABLE_CELL_PADDING_X * 2;
        tableWidth += columnWidths[j];
    }

    for (int i = 0; i < row; ++i) {
        tableHeight += rowHeights[i];
    }

    tablePos = {getCenterX(tableWidth), tablePosY};
    initialTextPosition = {
        tablePos.x + TABLE_CELL_PADDING_X,
        tablePos.y + DEFAULT_TITLE_SIZE + DEFAULT_ITEM_MARGIN.y +
            (rowHeights[0] - DEFAULT_TEXT_SIZE) / 2.0f};
}

void Table::drawTable() {
    Vector2 textPosition = initialTextPosition, cellPos = tablePos;

    DrawRectangleV(
        {tablePos.x - DEFAULT_PADDING.x, tablePos.y - DEFAULT_PADDING.y},
        {tableWidth + DEFAULT_PADDING.x * 2, tableHeight + DEFAULT_PADDING.y * 2}, WHITE
    );
    drawDefaultTitle(
        titleFont, tableTitle,
        {getCenterX(measureTextWidth(titleFont, tableTitle)), tablePos.y}
    );

    for (int j = 0; j < col; ++j) {
        cellPos.y = tablePos.y + DEFAULT_TITLE_SIZE + DEFAULT_ITEM_MARGIN.y;

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

    for (int j = 0; j < col; ++j) {
        textPosition.y = initialTextPosition.y;

        for (int i = 0; i < row; ++i) {
            float textSize = measureTextWidth(textFont, tableData[i][j].c_str());

            if (j < 2) {
                textPosition.x += (columnWidths[j] - textSize) / 2 - TABLE_CELL_PADDING_X;
            }

            drawDefaultText(textFont, tableData[i][j].c_str(), textPosition, BLACK);

            if (j < 2) {
                textPosition.x -= (columnWidths[j] - textSize) / 2 - TABLE_CELL_PADDING_X;
            }

            textPosition.y += rowHeights[i];
        }

        textPosition.x += columnWidths[j];
    }
}
