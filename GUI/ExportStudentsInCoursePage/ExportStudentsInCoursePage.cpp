#include "ExportStudentsInCoursePage.h"

#include "../../Function/ExportStudentsInCourse/ExportStudentsInCourse.h"
#include "../../Struct/Data.h"
#include "../DropDown/DropDown.h"
#include "../FormPage/FormPage.h"
#include "../TextInput/TextInput.h"

class ExportStudentsInCoursePage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void ExportStudentsInCoursePage::drawFormInput() {
    TextInput exportPathInput(inputs[0], inputPos[1], inputWidth);
    DropDown courseDropDown(allData.allCourses, inputPos[0], inputWidth);

    if (exportPathInput.drawTextInput("Export path", textInputEditModes[0])) {
        submit();
    }

    courseDropDown.drawDropDown(
        "Course", dropDownItems[0], dropDownActiveItems[0], dropDownEditModes[0]
    );
}

void ExportStudentsInCoursePage::submitCallBack() {
    exportStudentsInCourse(inputs, dropDownItems);
}

void exportStudentsInCoursePage() {
    ExportStudentsInCoursePage exportStudentsInCoursePage(
        "Export students in a course", 1, 1, 1,
        {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 2.0f}
    );
    exportStudentsInCoursePage.mainLoop();
}
