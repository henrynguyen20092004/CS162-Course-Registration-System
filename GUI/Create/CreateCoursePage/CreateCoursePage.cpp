#include "CreateCoursePage.h"

#include <cstring>

#include "../../../API/Create/CreateCourse/CreateCourse.h"
#include "../../../GlobalVar/GlobalVar.h"
#include "../../FormPage/FormPage.h"

class CreateCoursePage : public FormPage {
   private:
    void initInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void CreateCoursePage::initInputs() {
    strcpy(inputs[4], "4");
    strcpy(inputs[5], "50");
    textInputs[0] = TextInput("Course ID", inputs[0], inputPos[0], inputWidth);
    textInputs[1] = TextInput("Class Name", inputs[1], inputPos[1], inputWidth);
    textInputs[2] = TextInput("Course Name", inputs[2], inputPos[2], inputWidth);
    textInputs[3] = TextInput("Teacher Name", inputs[3], inputPos[3], inputWidth);
    textInputs[4] = TextInput("Number of credits", inputs[4], inputPos[4], inputWidth);
    textInputs[5] =
        TextInput("Maximum number of students", inputs[5], inputPos[5], inputWidth);
    dropDowns[0] =
        DropDown("Day of week", "MON;TUE;WED;THU;FRI;SAT", inputPos[6], inputWidth);
    dropDowns[1] = DropDown("Session number", "1;2;3;4", inputPos[7], inputWidth);
}

void CreateCoursePage::submitCallBack() {
    createCourse(inputs, dropDownItems);
    successText = "Course successfully created!";
}

void createCoursePage() {
    CreateCoursePage createCoursePage(
        "Create a course", 6, 2, 2, {SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.35f}
    );
    createCoursePage.mainLoop();
}
