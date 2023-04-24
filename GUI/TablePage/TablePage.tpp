#include <algorithm>

#include "../TextFunction/TextFunction.h"
#include "TablePage.h"

template <typename T>
TablePage<T>::TablePage(const std::string &title, int col, Node<T> *dataLinkedList)
    : title(title),
      col(col),
      columnTitle(nullptr),
      columnWidths(nullptr),
      dataLinkedList(dataLinkedList) {
    row = getLinkedListSize(dataLinkedList) + 1;
    tableData = new std::string *[row];

    for (int i = 0; i < row; ++i) {
        tableData[i] = new std::string[col];
    }
}

template <typename T>
void TablePage<T>::clipData() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            tableData[i][j] =
                clipText(textFont, tableData[i][j].c_str(), columnWidths[j]);
        }
    }
}

template <typename T>
void TablePage<T>::generateRowHeights() {
    rowHeights = new int[row];

    for (int i = 0; i < row; ++i) {
        int maxNumberOfLines = 0;

        for (int j = 0; j < col; ++j) {
            int numberOfLines =
                std::count(tableData[i][j].begin(), tableData[i][j].end(), '\n') + 1;

            if (numberOfLines > maxNumberOfLines) {
                maxNumberOfLines = numberOfLines;
            }
        }

        rowHeights[i] =
            TABLE_ROW_HEIGHT + DEFAULT_TEXT_SIZE * (maxNumberOfLines * 1.5 - 0.5);
    }
}

template <typename T>
void TablePage<T>::initComponents() {
    initColumns();
    convertLinkedListToData();
    clipData();
    generateRowHeights();
    table =
        Table(tableData, columnTitle, title.c_str(), row, col, rowHeights, columnWidths);
}

template <typename T>
void TablePage<T>::createAndSortDataArray(T *&dataArray) {
    int arraySize;
    transformLinkedListToArray(dataLinkedList, dataArray, arraySize);
    std::sort(dataArray, dataArray + arraySize);
}

template <typename T>
void TablePage<T>::drawPage() {
    table.drawTable();
}

template <typename T>
TablePage<T>::~TablePage() {
    for (int i = 0; i < row; ++i) {
        delete[] tableData[i];
    }

    delete[] tableData;
    delete[] columnTitle;
    delete[] rowHeights;
    delete[] columnWidths;
}
