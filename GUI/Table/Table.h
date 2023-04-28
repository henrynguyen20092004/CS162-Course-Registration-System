#ifndef TABLE_H
#define TABLE_H

#define TABLE_CELL_HEIGHT 40
#define TABLE_CELL_PADDING_X 5.0f
#define TABLE_BUTTON_WIDTH 80.0f
#define TABLE_BUTTON_CELL_WIDTH 80.0f

#include <string>

#include "../Button/Button.h"
#include "../GlobalStyle.h"

class Table {
   private:
    const char* tableTitle = nullptr;
    int row = 0, col = 0, buttonCol = 0, headerButton = 0, *rowHeights = nullptr;
    float *columnWidths, tableWidth = 0.0f, tableHeight = 0.0f, tableOffsetY = 0.0f,
                         backgroundHeight = 0.0f;
    std::string **tableData = nullptr, *columnTitle = nullptr;
    Command *columnButtonCommands = nullptr, *headerButtonCommands = nullptr;
    Vector2 tablePos{0.0f, 0.0f}, initialTextPos{0.0f, 0.0f}, scroll{0.0f, 0.0f};
    Button **columnButtons = nullptr, *headerButtons = nullptr;
    void drawGrid();
    void drawText();
    void drawButton(bool& stopLoop);

   public:
    Table();
    Table(
        std::string** tableData, std::string* columnTitle, const char* tableTitle,
        int row, int col, int buttonCol, int headerButton, int* rowHeights,
        float* columnWidths, float tableWidth, Command* columnButtonCommands,
        Command* headerButtonCommands, Vector2 tablePos, Button** columnButtons,
        Button* headerButtons
    );
    void drawTable(bool& stopLoop);
};

#endif
