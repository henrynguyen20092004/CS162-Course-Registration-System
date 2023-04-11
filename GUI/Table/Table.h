#ifndef DRAW_TABLE_H
#define DRAW_TABLE_H

#include <raylib.h>

#include <string>

#include "../../Struct/Student.h"

class Table {
   private:
    std::string **tableData, *columnTitle;
    int row, col;
    float *width, height;
    void convertLinkedListToTableDatas(Student* allStudentsArray);

   public:
    Table(
        Student* allStudentsArray, int row, int col, std::string* columnTitle,
        float* width, float height
    );
    ~Table();

    void drawTable(const char* tableTitle);
};

#endif
