#include "AddStudentToCoursePage.h"

#include "../../Function/AddStudentToCourse/AddStudentToCourse.h"
#include "../../Struct/Data.h"
#include "../FormPage/FormPage.h"

class AddStudentToCoursePage : public FormPage {
   private:
    void initComponents() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void AddStudentToCoursePage::initComponents() {
    FormPage::initComponents();
    dropDowns[0] = DropDown("Course name", allData.allCourses, inputPos[0], inputWidth);
    textInputs[0] = TextInput("Student ID", inputs[0], inputPos[1], inputWidth);
}

void AddStudentToCoursePage::submitCallBack() {
    addStudentToCourse(inputs, dropDownItems);
}

void addStudentToCoursePage() {
    AddStudentToCoursePage addStudentToCoursePage(
        "Add student to course", 1, 1, 1, {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 2.0f}
    );
    addStudentToCoursePage.mainLoop();
}
