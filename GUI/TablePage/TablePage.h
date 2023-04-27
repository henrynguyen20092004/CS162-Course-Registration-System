#ifndef TABLE_PAGE_H
#define TABLE_PAGE_H

#include "../Page/Page.h"
#include "../Table/Table.h"

template <typename T>
class TablePage : public Page {
   private:
    virtual void initColumns() {}
    virtual void initButtons() {}
    virtual void convertLinkedListToData() {}
    void drawPage() override;
    void clipData();
    void addColumnsForButton();
    void calculateTableAndFirstRow();
    void generateRowHeights();
    void generateButtons();

   protected:
    const char **headerButtonTitles = nullptr, **firstRowButtonTitles = nullptr;
    int row, col, buttonCol, headerButton, *rowHeights;
    float *columnWidths = nullptr, tableWidth = 0.0f, firstRowButtonsPosX = 0.0f;
    Node<T> *dataLinkedList;
    std::string **tableData, *columnTitle = nullptr, title;
    Vector2 tablePos{0.0f, 0.0f};
    Button **columnButtons = nullptr, *headerButtons = nullptr;
    Table table;
    void initComponents() override;
    void createAndSortDataArray(T *&dataArray);

   public:
    TablePage(
        const std::string &title, int col, int buttonCol, int headerButton,
        Node<T> *dataLinkedList
    );
    ~TablePage();
};

#include "TablePage.tpp"

#endif
