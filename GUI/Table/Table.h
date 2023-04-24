#ifndef TABLE_H
#define TABLE_H

#include <string>

#include "../GlobalStyle.h"

class Table {
   private:
    const char* tableTitle;
    int row, col, *rowHeights;
    float *columnWidths, tableWidth = 0.0f, tableHeight = 0.0f;
    std::string **tableData, *columnTitle;
    Vector2 tablePos, initialTextPosition;

   public:
    Table();
    Table(
        std::string** tableData, std::string* columnTitle, const char* tableTitle,
        int row, int col, int* rowHeights, float* columnWidths,
        float tablePosY = SCREEN_HEIGHT / 6.4f + DEFAULT_ITEM_MARGIN.y + DEFAULT_PADDING.y
    );
    void drawTable();
};

#endif
