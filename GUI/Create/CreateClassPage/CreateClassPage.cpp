#include "CreateClassPage.h"

#include "../../../Function/Create/CreateClass/CreateClass.h"
#include "../../FormPage/FormPage.h"

class CreateClassPage : public FormPage {
   private:
    void initComponents() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void CreateClassPage::initComponents() {
    FormPage::initComponents();
    textInputs[0] = TextInput("Class name", inputs[0], inputPos[0], inputWidth);
}

void CreateClassPage::submitCallBack() { createClass(inputs[0]); }

void createClassPage() {
    CreateClassPage createClassPage(
        "Create a class", 1, 0, 1, {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 3.0f}
    );
    createClassPage.mainLoop();
}
