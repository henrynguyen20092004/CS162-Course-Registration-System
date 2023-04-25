#include "ImportStudentsInCoursePage.h"

#include "../../../Function/DownloadTemplateCSV/DownloadTemplateCSV.h"
#include "../../../Function/ImportCSV/ImportStudentsInCourse/ImportStudentInCourse.h"
#include "../../../Struct/Data.h"
#include "../../FormPage/FormPage.h"

class ImportStudentsInCoursePage : public FormPage {
   private:
    void initComponents() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void ImportStudentsInCoursePage::initComponents() {
    FormPage::initComponents();
    dropDowns[0] = DropDown(
        "What do you want to do?",
        "Download template CSV;Import CSV of students in course", inputPos[0], inputWidth
    );
    dropDowns[1] = DropDown("Course name", allData.allCourses, inputPos[1], inputWidth);
    dropDowns[1].addOption("No option");
    textInputs[0] = TextInput("Export path", inputs[0], inputPos[2], inputWidth);
}

void ImportStudentsInCoursePage::submitCallBack() {
    downloadPrompt(
        "StudentsInCourse.csv", importStudentsInCourse, dropDowns[0].activeItemIndex,
        inputs, dropDownItems
    );
}

void importStudentsInCoursePage() {
    ImportStudentsInCoursePage importStudentsInCoursePage(
        "Import students in a course", 1, 2, 1,
        {SCREEN_WIDTH / 2.5f, SCREEN_HEIGHT / 1.5f}
    );

    importStudentsInCoursePage.mainLoop();
}
