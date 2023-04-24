#include "Table.h"

#include "../GetCenterPosition/GetCenterPosition.h"
#include "../TextFunction/TextFunction.h"

Table::Table()
    : tableData(nullptr),
      columnTitle(nullptr),
      tableTitle(nullptr),
      row(0),
      col(0),
      rowHeight(0),
      columnWidths(nullptr),
      tablePos({0.0f, 0.0f}),
      initialTextPosition({0.0f, 0.0f}) {}

Table::Table(
    std::string** tableData, std::string* columnTitle, const char* tableTitle, int row,
    int col, int rowHeight, float* columnWidths, float tablePosY
)
    : tableData(tableData),
      columnTitle(columnTitle),
      tableTitle(tableTitle),
      row(row),
      col(col),
      rowHeight(rowHeight),
      columnWidths(columnWidths) {
    for (int j = 0; j < col; ++j) {
        tableWidth += columnWidths[j];
    }

    tableHeight = DEFAULT_TITLE_SIZE + DEFAULT_ITEM_MARGIN.y + rowHeight * row;
    tablePos = {getCenterX(tableWidth), tablePosY};
    initialTextPosition = {
        tablePos.x, tablePos.y + DEFAULT_TITLE_SIZE + DEFAULT_ITEM_MARGIN.y +
                        (rowHeight - DEFAULT_TEXT_SIZE) / 2.0f};
}

void Table::drawTable() {
    float prevWidth = tablePos.x;
    Vector2 textPosition = initialTextPosition;

    DrawRectangleV(
        {tablePos.x - DEFAULT_PADDING.x, tablePos.y - DEFAULT_PADDING.y},
        {tableWidth + DEFAULT_PADDING.x * 2, tableHeight + DEFAULT_PADDING.y * 2}, WHITE
    );
    drawDefaultTitle(
        titleFont, tableTitle,
        {getCenterX(measureTextWidth(titleFont, tableTitle)), tablePos.y}
    );

    for (int j = 0; j < col; ++j) {
        if (j > 0) {
            prevWidth += columnWidths[j - 1];
        }

        for (int i = 0; i < row; ++i) {
            DrawRectangleLines(
                prevWidth,
                i * rowHeight + tablePos.y + DEFAULT_TITLE_SIZE + DEFAULT_ITEM_MARGIN.y,
                columnWidths[j], rowHeight, BLACK
            );
        }
    }

    for (int j = 0; j < col; ++j) {
        if (j > 0) {
            textPosition.x += columnWidths[j - 1] / 2;
        }

        textPosition.x += columnWidths[j] / 2;
        textPosition.y = initialTextPosition.y;

        for (int i = 0; i < row; ++i) {
            float textSize = measureTextWidth(textFont, tableData[i][j].c_str());
            textPosition.x -= textSize / 2;
            drawDefaultText(textFont, tableData[i][j].c_str(), textPosition, BLACK);
            textPosition.x += textSize / 2;
            textPosition.y += rowHeight;
        }
    }
}
