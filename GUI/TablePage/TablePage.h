#ifndef TABLE_PAGE_H
#define TABLE_PAGE_H

#include "../Page/Page.h"
#include "../Table/Table.h"

class TablePage : public Page {
   private:
    virtual void initColumns() {}
    virtual void convertLinkedListToData() {}
    void drawPage() override;

   protected:
    int row, col;
    float *columnWidths;
    void *dataLinkedList;
    std::string **tableData, *columnTitle, title;
    Table table;
    void initComponents() override;

   public:
    template <typename T>
    TablePage(const std::string &title, int col, Node<T> *dataLinkedList)
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
    ~TablePage();
};

#endif
