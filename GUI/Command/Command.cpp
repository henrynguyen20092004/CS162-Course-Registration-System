#include "Command.h"

#include "../../GlobalVar/GlobalVar.h"
#include "../AddStudentToCoursePage/AddStudentToCoursePage.h"
#include "../ChangeCurrentSemesterPage/ChangeCurrentSemesterPage.h"
#include "../ChangePasswordPage/ChangePasswordPage.h"
#include "../Create/CreateClassPage/CreateClassPage.h"
#include "../Create/CreateCoursePage/CreateCoursePage.h"
#include "../Create/CreateSchoolYearPage/CreateSchoolYearPage.h"
#include "../Create/CreateSemesterPage/CreateSemesterPage.h"
#include "../Create/CreateStudentPage/CreateStudentPage.h"
#include "../ExportStudentsInCoursePage/ExportStudentsInCoursePage.h"
#include "../HomePage/HomePage.h"
#include "../ImportCSVPage/ImportScoreboardPage/ImportScoreboardPage.h"
#include "../ImportCSVPage/ImportStudentsInClassPage/ImportStudentsInClassPage.h"
#include "../ImportCSVPage/ImportStudentsInCoursePage/ImportStudentsInCoursePage.h"
#include "../Update/UpdateCoursePage/UpdateCoursePage.h"
#include "../Update/UpdateStudentResultPage/UpdateStudentResultPage.h"
#include "../View/ViewClassScoreboardPage/ViewClassScoreboardPage.h"
#include "../View/ViewClassesPage/ViewClassesPage.h"
#include "../View/ViewCourseScoreboardPage/ViewCourseScoreboardPage.h"
#include "../View/ViewCoursesOfStudentPage/ViewCoursesOfStudentPage.h"
#include "../View/ViewCoursesPage/ViewCoursesPage.h"
#include "../View/ViewSchoolYearsPage/ViewSchoolYearsPage.h"
#include "../View/ViewScoreboardOfStudentPage/ViewScoreboardOfStudentPage.h"
#include "../View/ViewSemestersPage/ViewSemestersPage.h"
#include "../View/ViewStudentInfoPage/ViewStudentInfoPage.h"
#include "../View/ViewStudentsInClassPage/ViewStudentsInClassPage.h"
#include "../View/ViewStudentsInCoursePage/ViewStudentsInCoursePage.h"

void selectPage() {
    switch (GlobalVar::commandChoice) {
        case HOME:
            homePage();
            break;

        case CHANGE_CURRENT_SEMESTER:
            changeCurrentSemesterPage();
            break;

        case CHANGE_PASSWORD:
            changePasswordPage();
            break;

        case VIEW_STUDENT_INFO:
            viewStudentInfoPage();
            break;

        case VIEW_SCHOOL_YEARS:
            viewSchoolYearsPage();
            break;

        case VIEW_SEMESTERS:
            viewSemestersPage();
            break;

        case VIEW_COURSES:
            viewCoursesPage();
            break;

        case VIEW_CLASSES:
            viewClassesPage();
            break;

        case VIEW_STUDENTS_IN_CLASS:
            viewStudentsInClassPage(GlobalVar::renderArgs);
            break;

        case VIEW_STUDENTS_IN_COURSE:
            viewStudentsInCoursePage(GlobalVar::renderArgs);
            break;

        case VIEW_SCOREBOARD_OF_COURSE:
            viewCourseScoreboardPage(GlobalVar::renderArgs);
            break;

        case VIEW_SCOREBOARD_OF_CLASS:
            viewClassScoreboardPage(GlobalVar::renderArgs);
            break;

        case VIEW_SCOREBOARD_OF_STUDENT:
            viewScoreboardOfStudentPage();
            break;

        case VIEW_COURSES_OF_STUDENT:
            viewCoursesOfStudentPage();
            break;

        case CREATE_SCHOOL_YEAR:
            createSchoolYearPage();
            break;

        case CREATE_CLASS:
            createClassPage();
            break;

        case CREATE_STUDENT:
            createStudentPage();
            break;

        case CREATE_SEMESTER:
            createSemesterPage();
            break;

        case CREATE_COURSE:
            createCoursePage();
            break;

        case ADD_STUDENT_TO_COURSE:
            addStudentToCoursePage();
            break;

        case IMPORT_STUDENTS_IN_CLASS:
            importStudentsInClassPage(GlobalVar::renderArgs);
            break;

        case IMPORT_STUDENTS_IN_COURSE:
            importStudentsInCoursePage(GlobalVar::renderArgs);
            break;

        case IMPORT_SCOREBOARD:
            importScoreboardPage(GlobalVar::renderArgs);
            break;

        case EXPORT_STUDENTS_IN_COURSE:
            exportStudentsInCoursePage(GlobalVar::renderArgs);
            break;

        case UPDATE_COURSE:
            updateCoursePage();
            break;

        case UPDATE_STUDENT_RESULT:
            updateStudentResultPage();
            break;
    }
}
