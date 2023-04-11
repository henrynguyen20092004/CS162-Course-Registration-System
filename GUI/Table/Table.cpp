#include "Table.h"

#include "../../Function/GetAll/GetAll.h"
#include "../../Struct/Data.h"
#include "../../Struct/LinkedList.h"
#include "../FontFunction/FontFunction.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../GlobalStyle.h"
#include "../TextFunction/TextFunction.h"

Table::Table(
    Student* allStudentsArray, int row, int col, std::string* columnTitle, float* width,
    float height
)
    : columnTitle(columnTitle), row(row), col(col), width(width), height(height) {
    convertLinkedListToTableDatas(allStudentsArray);
    delete[] allStudentsArray;
}

void Table::convertLinkedListToTableDatas(Student* allStudentsArray) {
    tableData = new std::string*[row];
    for (int i = 0; i < row; ++i) {
        tableData[i] = new std::string[col];
    }
    /*std::string columnTitle[col] = {"N0",     "Student ID",    "First Name", "Last
       Name", "Gender", "Date of Birth", "Social ID"};*/
    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
    }
    for (int i = 1; i < row; ++i) {
        tableData[i][1] = allStudentsArray[i - 1].id;
        tableData[i][2] = allStudentsArray[i - 1].firstName;
        tableData[i][3] = allStudentsArray[i - 1].lastName;
        tableData[i][4] = allStudentsArray[i - 1].gender;
        tableData[i][5] = allStudentsArray[i - 1].dateOfBirth;
        tableData[i][6] = allStudentsArray[i - 1].socialID;
    }
}

void Table::drawTable(const char* tableTitle) {
    Vector2 titlePosition;
    titlePosition.x = 600;
    titlePosition.y = 0;
    float tableWidth = 0;
    for (int j = 0; j < col; ++j) {
        tableWidth += width[j];
    }
    while (WindowShouldClose) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        float tablePos = (SCREEN_WIDTH - tableWidth) / 2, prevWidth = tablePos;
        drawDefaultTitle(titleFont, tableTitle, titlePosition, RED);

        Vector2 textPosition;
        textPosition.x = tablePos;
        textPosition.y = height / 2 + 90;

        for (int i = 0; i < row; ++i) {
            DrawRectangleLines(tablePos, i * height + 100, width[0], height, BLACK);
        }

        for (int j = 1; j <= col; ++j) {
            prevWidth += width[j - 1];
            for (int i = 0; i < row; ++i) {
                DrawRectangleLines(prevWidth, i * height + 100, width[j], height, BLACK);
            }
        }

        for (int j = 0; j < col; ++j) {
            if (j == 0) {
                textPosition.x += width[j] / 2;
            } else {
                textPosition.x += width[j - 1] / 2 + width[j] / 2;
            }
            textPosition.y = height / 2 + 90;
            for (int i = 0; i < row; ++i) {
                float textSize = measureTextWidth(textFont, tableData[i][j].c_str());
                textPosition.x -= textSize / 2;
                drawDefaultText(textFont, tableData[i][j].c_str(), textPosition, BLACK);
                textPosition.x += textSize / 2;
                textPosition.y += height;
            }
        }
        EndDrawing();
    }
}

Table::~Table() {
    for (int i = 0; i < row; ++i) {
        delete[] tableData[i];
    }
    delete[] tableData;
}