#ifndef PAGE_H
#define PAGE_H

class Page {
   private:
    virtual void initComponents() {}
    virtual void drawPage() {}

   protected:
    bool stopLoop = false;

   public:
    void mainLoop();
};

#endif
