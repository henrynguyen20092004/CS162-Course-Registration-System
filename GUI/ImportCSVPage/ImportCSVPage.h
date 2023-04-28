#ifndef IMPORT_CSV_PAGE_H
#define IMPORT_CSV_PAGE_H

#include "../FormPage/FormPage.h"

class ImportCSVPage : public FormPage {
   private:
    const char *CSVName;
    std::string arg;
    void (*importCallBack)(char **, char **, const std::string &arg);
    void drawInputs() override;
    void checkFilledFields() override;
    void submitCallBack() override;
    Button browseFileButton, browseFolderButton;

   protected:
    void initInputs() override;

   public:
    using FormPage::FormPage;
    ImportCSVPage(
        const std::string &title, const char *CSVName, const std::string &arg,
        void (*importCallBack)(char **, char **, const std::string &arg),
        Command backButtonCommand
    );
};

#endif
