#ifndef FORM_H
#define FORM_H

#include <raylib.h>

#include "../Page/Page.h"

class FormPage : public Page {
   private:
    void drawPage() override;
    void drawFormBox();
    virtual void drawFormInput() {}
    void drawErrorText();

   protected:
    const char *title;
    char **inputs;
    const char *errorText;
    bool *editModes;
    int numberOfInputs;
    float childrenPosX;
    Vector2 mainBoxSize, mainBoxPosition, padding;
    virtual void submitCallBack() {}

   public:
    FormPage(
        const char *title, int numberOfInputs, Vector2 mainBoxSize,
        Vector2 padding = {20.0f, 20.0f}
    );
    ~FormPage();
};

#endif
