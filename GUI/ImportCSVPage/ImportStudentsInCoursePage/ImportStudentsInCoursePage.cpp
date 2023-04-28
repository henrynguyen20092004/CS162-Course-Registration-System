#include "ImportStudentsInCoursePage.h"

#include "../../../Function/ImportCSV/ImportScoreboard/ImportScoreboard.h"
#include "../../../Function/ImportCSV/ImportStudentsInCourse/ImportStudentInCourse.h"
#include "../../../Struct/Data.h"
#include "../ImportCSVPage.h"

class ImportStudentsInCoursePage : public ImportCSVPage {
   private:
    void initInputs() override;

   public:
    using ImportCSVPage::ImportCSVPage;
};

void ImportStudentsInCoursePage::initInputs() {
    ImportCSVPage::initInputs();
    dropDowns[1] = DropDown("Course name", allData.allCourses, inputPos[2], inputWidth);
}

void importStudentsInCoursePage() {
    ImportStudentsInCoursePage importStudentsInCoursePage(
        "Import students in a course", "StudentsInCourse.csv", &importStudentsInCourse,
        VIEW_STUDENTS_IN_COURSE
    );

    importStudentsInCoursePage.mainLoop();
}
