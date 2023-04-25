#ifndef IMPORT_CSV_PAGE_H
#define IMPORT_CSV_PAGE_H

#include "../FormPage/FormPage.h"

class ImportCSVPage : public FormPage {
   private:
    const char *CSVName;
    void (*importCallBack)(char **, char **);
    void drawInputs() override;
    void checkFilledFields() override;
    void submitCallBack() override;
    Button openFileButton;

   protected:
    void initInputs() override;

   public:
    using FormPage::FormPage;
    ImportCSVPage(
        const char *title, const char *CSVName, Vector2 mainBoxSize,
        void (*importCallBack)(char **, char **)
    );
};

#endif
