#include "CreateCoursePage.h"

#include "../../Function/Create/CreateCourse/CreateCourse.h"
#include "../../Struct/Data.h"
#include "../CreateSemesterPage/CreateSemesterPage.h"
#include "../FormPage/FormPage.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../GlobalStyle.h"
#include "../TextInput/TextInput.h"

class CreateCoursePage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
    using Page::mainLoop;
    Course curCourse;
};

void CreateCoursePage ::drawFormInput() {
    TextInput courseIDIput(inputs[0], inputPosY[0]);
    TextInput classNameInput(inputs[1], inputPosY[1]);
    TextInput courseNameInput(inputs[2], inputPosY[2]);
    TextInput teacherNameInput(inputs[3], inputPosY[3]);
    TextInput creditsInput(inputs[4], inputPosY[4]);
    TextInput maxStudentInput(inputs[5], inputPosY[5]);
    TextInput dayOfWeekInput(inputs[6], inputPosY[6]);
    TextInput sessionNumberInput(inputs[7], inputPosY[7]);

    if (courseIDIput.drawTextInput("Course ID", editModes[0]) ||
            classNameInput.drawTextInput("Class Name", editModes[1]) ||
            courseNameInput.drawTextInput("Course Name", editModes[2]) ||
            teacherNameInput.drawTextInput("Teacher Name", editModes[3]) ||
            creditsInput.drawTextInput("Number of credit(s)", editModes[4]) ||
            maxStudentInput.drawTextInput("Maximum number of Student", editModes[5]),
        dayOfWeekInput.drawTextInput(
            "Day of week that course will be perfomed", editModes[6]
        ),
        sessionNumberInput.drawTextInput(
            "Session number that course will be perfomed", editModes[7]
        )) {
        submitCallBack();
    }
}

void CreateCoursePage::submitCallBack() {
    Semester curSemester = ;

    try {
        curCourse = createCourse()
    }
}
Course CreateCoursePage();
