#ifndef TABLE_PAGE_H
#define TABLE_PAGE_H

#include "../Page/Page.h"
#include "../Table/Table.h"

template <typename T>
class TablePage : public Page {
   private:
    virtual void initColumns() {}
    virtual void convertLinkedListToData() {}
    void drawPage() override;
    void clipData();
    void generateRowHeights();

   protected:
    int row, col, *rowHeights;
    float *columnWidths;
    Node<T> *dataLinkedList;
    std::string **tableData, *columnTitle, title;
    Table table;
    void initComponents() override;
    void createAndSortDataArray(T *&dataArray);

   public:
    TablePage(const std::string &title, int col, Node<T> *dataLinkedList);
    ~TablePage();
};

#include "TablePage.tpp"

#endif
