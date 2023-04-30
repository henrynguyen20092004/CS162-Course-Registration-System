#ifndef PAGE_H
#define PAGE_H

#include "../GlobalStyle.h"

class Page {
   private:
    char* menuDropDownItems;
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
