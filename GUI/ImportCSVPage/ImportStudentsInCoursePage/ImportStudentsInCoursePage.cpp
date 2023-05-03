#include "ImportStudentsInCoursePage.h"

#include "../../../API/ImportCSV/ImportStudentsInCourse/ImportStudentsInCourse.h"
#include "../ImportCSVPage.h"

class ImportStudentsInCoursePage : public ImportCSVPage {
   public:
    using ImportCSVPage::ImportCSVPage;
};

void importStudentsInCoursePage(const std::string& course) {
    ImportStudentsInCoursePage importStudentsInCoursePage(
        "Import students of " + course, "Students_in_course.csv", course,
        &importStudentsInCourse
    );
    importStudentsInCoursePage.mainLoop();
}
