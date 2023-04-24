#include "CreateStudentPage.h"

#include "../../../Function/Create/CreateStudent/CreateStudent.h"
#include "../../../Struct/Data.h"
#include "../../FormPage/FormPage.h"

class CreateStudentPage : public FormPage {
   private:
    void initComponents() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void CreateStudentPage::initComponents() {
    FormPage::initComponents();

    textInputs[0] = TextInput("Student ID", inputs[0], inputPos[0], inputWidth);
    textInputs[1] = TextInput("First Name", inputs[1], inputPos[1], inputWidth);
    textInputs[2] = TextInput("Last Name", inputs[2], inputPos[2], inputWidth);
    dropDowns[0] = DropDown("Gender", "M;F", inputPos[3], inputWidth);
    textInputs[3] =
        TextInput("Date Of birth (dd/mm/yyyy)", inputs[3], inputPos[4], inputWidth);
    textInputs[4] = TextInput("Social ID", inputs[4], inputPos[5], inputWidth);
    dropDowns[1] = DropDown("Class name", allData.allClasses, inputPos[6], inputWidth);
}

void CreateStudentPage::submitCallBack() { createStudent(inputs, dropDownItems); }

void createStudentPage() {
    CreateStudentPage createStudentPage(
        "Add student to class", 5, 2, 2, {SCREEN_WIDTH / 1.6f, SCREEN_HEIGHT / 1.35f}
    );
    createStudentPage.mainLoop();
}
