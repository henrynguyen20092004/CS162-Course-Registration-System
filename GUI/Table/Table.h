#ifndef TABLE_H
#define TABLE_H

#define TABLE_CELL_HEIGHT 40
#define TABLE_CELL_PADDING_X 5.0f
#define TABLE_BUTTON_CELL_WIDTH 80.0f

#include <string>

#include "../Button/Button.h"

class Table {
   private:
    const char* tableTitle = nullptr;
    int row = 0, col = 0, buttonCol = 0, headerButton = 0, *rowHeights = nullptr;
    float *columnWidths, tableWidth = 0.0f, tableHeight = 0.0f, tableOffsetY = 0.0f,
                         backgroundHeight = 0.0f;
    std::string **tableData = nullptr, *columnTitle = nullptr;
    Vector2 tablePos{0.0f, 0.0f}, initialTextPos{0.0f, 0.0f};
    void drawGrid(float scrollY);
    void drawText(float scrollY);

   public:
    Table();
    Table(
        std::string** tableData, std::string* columnTitle, const char* tableTitle,
        int row, int col, int buttonCol, int headerButton, int* rowHeights,
        float* columnWidths, float tableWidth, Vector2 tablePos
    );
    void drawTable(Vector2& scroll);
};

#endif
