#include "AddStudentToCoursePage.h"

#include "../../API/AddStudentToCourse/AddStudentToCourse.h"
#include "../../GlobalVar/GlobalVar.h"
#include "../FormPage/FormPage.h"

class AddStudentToCoursePage : public FormPage {
   private:
    void initInputs() override;
    void submitCallBack() override;

   public:
    AddStudentToCoursePage(const std::string &course);
    std::string course;
};

AddStudentToCoursePage::AddStudentToCoursePage(const std::string &course)
    : FormPage(
          "Add student to " + course, 1, 0, 1,
          {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.25f}
      ),
      course(course) {}

void AddStudentToCoursePage::initInputs() {
    textInputs[0] = TextInput("Student ID", inputs[0], inputPos[0], inputWidth);
}

void AddStudentToCoursePage::submitCallBack() {
    addStudentToCourse(inputs, course);
    successText = "Student successfully added!";
}

void addStudentToCoursePage(const std::string &course) {
    AddStudentToCoursePage addStudentToCoursePage(course);
    addStudentToCoursePage.mainLoop();
}
