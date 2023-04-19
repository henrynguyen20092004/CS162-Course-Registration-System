#include "ExportStudentsInCoursePage.h"

#include <cstring>

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
        submitCallBack();
    }

    courseDropDown.drawDropDown(
        "Course", dropDownItems[0], dropdownActiveItems[0], dropdownEditModes[0]
    );
}

void ExportStudentsInCoursePage::submitCallBack() {
    try {
        exportStudentsInCourse(inputs, dropDownItems);
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

void exportStudentsInCoursePage() {
    ExportStudentsInCoursePage exportStudentsInCoursePage(
        "Export students in a course", 1, 1, 1,
        {SCREEN_WIDTH / 2.7f, SCREEN_HEIGHT / 1.8f}
    );
    exportStudentsInCoursePage.mainLoop();
}
