#include <algorithm>

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
void TablePage<T>::initComponents() {
    initColumns();
    convertLinkedListToData();
    table = Table(
        tableData, columnTitle, title.c_str(), row, col, TABLE_ROW_HEIGHT, columnWidths
    );
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
    delete[] columnWidths;
}
