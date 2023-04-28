#define RAYGUI_IMPLEMENTATION

#include "MainGUI.h"

#include "../Function/GetCurrentSemester/GetCurrentSemester.h"
#include "AddStudentToCoursePage/AddStudentToCoursePage.h"
#include "ChangeCurrentSemesterPage/ChangeCurrentSemesterPage.h"
#include "ChangePasswordPage/ChangePasswordPage.h"
#include "Create/CreateClassPage/CreateClassPage.h"
#include "Create/CreateCoursePage/CreateCoursePage.h"
#include "Create/CreateSchoolYearPage/CreateSchoolYearPage.h"
#include "Create/CreateSemesterPage/CreateSemesterPage.h"
#include "Create/CreateStudentPage/CreateStudentPage.h"
#include "ExportStudentsInCoursePage/ExportStudentsInCoursePage.h"
#include "FontFunction/FontFunction.h"
#include "GlobalStyle.h"
#include "ImportCSVPage/ImportScoreboardPage/ImportScoreboardPage.h"
#include "ImportCSVPage/ImportStudentsInClassPage/ImportStudentsInClassPage.h"
#include "ImportCSVPage/ImportStudentsInCoursePage/ImportStudentsInCoursePage.h"
#include "LogInPage/LogInPage.h"
#include "Page/Page.h"
#include "Update/UpdateCoursePage/UpdateCoursePage.h"
#include "Update/UpdateStudentResultPage/UpdateStudentResultPage.h"
#include "View/ViewClassesPage/ViewClassesPage.h"
#include "View/ViewCourseScoreboardPage/ViewCourseScoreboardPage.h"
#include "View/ViewCoursesOfStudentPage/ViewCoursesOfStudentPage.h"
#include "View/ViewCoursesPage/ViewCoursesPage.h"
#include "View/ViewSchoolYearsPage/ViewSchoolYearsPage.h"
#include "View/ViewScoreboardOfStudentPage/ViewScoreboardOfStudentPage.h"
#include "View/ViewSemestersPage/ViewSemestersPage.h"
#include "View/ViewStudentsInClassPage/ViewStudentsInClassPage.h"
#include "View/ViewStudentsInCoursePage/ViewStudentsInCoursePage.h"

std::string renderArgs;
Command commandChoice;
Font titleFont, textFont;
Texture2D defaultAvatar;
User currentUser;
Semester currentSemester = getCurrentSemester();

void SetDefaultStyle() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, DEFAULT_TEXT_SIZE);
    GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
    GuiSetStyle(DROPDOWNBOX, DROPDOWN_ITEMS_SPACING, 0);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x063970ff);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xffffffff);
    GuiSetStyle(LISTVIEW, SCROLLBAR_WIDTH, 18);
    GuiSetFont(textFont);
}

void selectPage() {
    Page temp;

    switch (commandChoice) {
        case HOME:
            temp.mainLoop();
            break;

        case CHANGE_CURRENT_SEMESTER:
            changeCurrentSemesterPage();
            break;

        case CHANGE_PASSWORD:
            changePasswordPage();
            break;

        case VIEW_STUDENT_INFO:
            temp.mainLoop();
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
            viewStudentsInClassPage(renderArgs);
            break;

        case VIEW_STUDENTS_IN_COURSE:
            viewStudentsInCoursePage(renderArgs);
            break;

        case VIEW_SCOREBOARD_OF_COURSE:
            viewCourseScoreboardPage(renderArgs);
            break;

        case VIEW_SCOREBOARD_OF_CLASS:
            temp.mainLoop();
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
            importStudentsInClassPage(renderArgs);
            break;

        case IMPORT_STUDENTS_IN_COURSE:
            importStudentsInCoursePage(renderArgs);
            break;

        case IMPORT_SCOREBOARD:
            importScoreboardPage(renderArgs);
            break;

        case EXPORT_STUDENTS_IN_COURSE:
            exportStudentsInCoursePage(renderArgs);
            break;

        case UPDATE_COURSE:
            updateCoursePage();
            break;

        case UPDATE_STUDENT_RESULT:
            updateStudentResultPage();
            break;

        case DELETE_COURSE:
            temp.mainLoop();
            break;
    }
}

void mainWindow() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Course Registration System");

    Image windowIcon = LoadImage("Pictures/WindowIcon.png");
    titleFont = loadDefaultTitleFont();
    textFont = loadDefaultTextFont();
    defaultAvatar = LoadTexture("Pictures/DefaultAvatar.png");

    SetWindowIcon(windowIcon);
    SetTargetFPS(60);
    SetDefaultStyle();

    do {
        if (currentUser.username == "") {
            logInPage();
        } else {
            selectPage();
        }
    } while (commandChoice != EXIT);

    UnloadImage(windowIcon);
    UnloadFont(titleFont);
    UnloadFont(textFont);
    UnloadTexture(defaultAvatar);
    CloseWindow();
}
