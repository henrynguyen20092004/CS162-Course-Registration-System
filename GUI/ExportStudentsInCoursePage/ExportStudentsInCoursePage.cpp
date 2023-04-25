#include "ExportStudentsInCoursePage.h"

#include "../../Function/ExportStudentsInCourse/ExportStudentsInCourse.h"
#include "../../Struct/Data.h"
#include "../FormPage/FormPage.h"

class ExportStudentsInCoursePage : public FormPage {
   private:
    void initInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void ExportStudentsInCoursePage::initInputs() {
    textInputs[0] = TextInput("Export folder path", inputs[0], inputPos[1], inputWidth);
    dropDowns[0] = DropDown("Course name", allData.allCourses, inputPos[0], inputWidth);
}

void ExportStudentsInCoursePage::submitCallBack() {
    exportStudentsInCourse(inputs, dropDownItems);
}

void exportStudentsInCoursePage() {
    ExportStudentsInCoursePage exportStudentsInCoursePage(
        "Export students in a course", 1, 1, 1,
        {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.0f}
    );
    exportStudentsInCoursePage.mainLoop();
}
