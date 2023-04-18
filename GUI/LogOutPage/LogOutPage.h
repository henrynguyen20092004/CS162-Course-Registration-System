#ifndef LOG_OUT_PAGE_H
#define LOG_OUT_PAGE_H

#include "../Page/Page.h"

class LogOutPage : public Page {
    void drawPage() override;

   public:
    using Page::stopLoop;
};

#endif