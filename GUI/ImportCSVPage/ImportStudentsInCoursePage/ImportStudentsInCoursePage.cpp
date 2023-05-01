#include "ImportStudentsInCoursePage.h"

#include "../../../Function/ImportCSV/ImportStudentsInCourse/ImportStudentsInCourse.h"
#include "../ImportCSVPage.h"

class ImportStudentsInCoursePage : public ImportCSVPage {
   public:
    using ImportCSVPage::ImportCSVPage;
};

void importStudentsInCoursePage(const std::string& course) {
    ImportStudentsInCoursePage importStudentsInCoursePage(
        "Import students of " + course, "StudentsInCourse.csv", course,
        &importStudentsInCourse
    );
    importStudentsInCoursePage.mainLoop();
}
