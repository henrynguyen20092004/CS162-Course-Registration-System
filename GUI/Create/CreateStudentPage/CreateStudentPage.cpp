#include "CreateStudentPage.h"

#include "../../../Function/Create/CreateStudent/CreateStudent.h"
#include "../../../GlobalVar/GlobalVar.h"
#include "../../FormPage/FormPage.h"

class CreateStudentPage : public FormPage {
   private:
    void initInputs() override;
    void submitCallBack() override;

   public:
    CreateStudentPage(const std::string &className);
    std::string className;
};

CreateStudentPage::CreateStudentPage(const std::string &className)
    : FormPage(
          "Add a student to class " + className, 5, 1, 2,
          {SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.75f}
      ),
      className(className) {}

void CreateStudentPage::initInputs() {
    textInputs[0] = TextInput("Student ID", inputs[0], inputPos[0], inputWidth);
    textInputs[1] = TextInput("First Name", inputs[1], inputPos[1], inputWidth);
    textInputs[2] = TextInput("Last Name", inputs[2], inputPos[2], inputWidth);
    dropDowns[0] = DropDown("Gender", "M;F", inputPos[3], inputWidth);
    textInputs[3] =
        TextInput("Date Of birth (dd/mm/yyyy)", inputs[3], inputPos[4], inputWidth);
    textInputs[4] = TextInput("Social ID", inputs[4], inputPos[5], inputWidth);
}

void CreateStudentPage::submitCallBack() {
    createStudent(inputs, dropDownItems, className);
    successText = "Student successfully added!";
}

void createStudentPage(const std::string &className) {
    CreateStudentPage createStudentPage(className);
    createStudentPage.mainLoop();
}
