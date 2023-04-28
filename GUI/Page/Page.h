#ifndef PAGE_H
#define PAGE_H

#include "../DropDown/DropDown.h"

class Page {
   private:
    char* menuDropDownItems;
    DropDown menuDropDown;
    virtual void initComponents() {}
    virtual void drawPage() {}

   protected:
    bool stopLoop = false;

   public:
    Page();
    ~Page();
    void mainLoop();
};

#endif
