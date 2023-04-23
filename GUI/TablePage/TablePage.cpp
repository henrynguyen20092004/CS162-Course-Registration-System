#include "TablePage.h"

void TablePage::initComponents() {
    initHeaders();
    convertLinkedListToData();
    table = Table(
        tableData, columnTitle, title.c_str(), row, col, TABLE_ROW_HEIGHT, columnWidths
    );
}

void TablePage::drawPage() { table.drawTable(); }

TablePage::~TablePage() {
    for (int i = 0; i < row; ++i) {
        delete[] tableData[i];
    }

    delete[] tableData;
    delete[] columnTitle;
    delete[] columnWidths;
}
