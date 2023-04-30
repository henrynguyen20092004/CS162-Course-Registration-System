#ifndef GLOBAL_STYLE_H
#define GLOBAL_STYLE_H

#include <raygui.h>
#include <raylib.h>

#include "../Struct/Semester.h"
#include "../Struct/User.h"

#define PRIMARY_COLOR \
    (Color) { 165, 215, 232, 255 }
#define NORMAL_TEXT_COLOR \
    (Color) { 11, 24, 47, 255 }
#define ERROR_TEXT_COLOR \
    (Color) { 255, 0, 0, 255 }
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define MENU_HEIGHT 150
#define DEFAULT_TITLE_SIZE 48
#define DEFAULT_TEXT_SIZE 24
#define MAX_INPUT_CHAR 256
#define DEFAULT_ITEM_HEIGHT 60.0f
#define DEFAULT_MENU_BUTTON_WIDTH 180.0f
#define DEFAULT_PADDING \
    (Vector2) { 20.0f, 20.0f }
#define DEFAULT_TEXT_MARGIN \
    (Vector2) { 6.0f, 6.0f }
#define DEFAULT_ITEM_MARGIN \
    (Vector2) { 20.0f, 20.0f }

enum Command {
    HOME,
    CHANGE_CURRENT_SEMESTER,
    CHANGE_PASSWORD,
    VIEW_STUDENT_INFO,
    VIEW_SCHOOL_YEARS,
    VIEW_SEMESTERS,
    VIEW_COURSES,
    VIEW_CLASSES,
    VIEW_STUDENTS_IN_CLASS,
    VIEW_STUDENTS_IN_COURSE,
    VIEW_SCOREBOARD_OF_COURSE,
    VIEW_SCOREBOARD_OF_CLASS,
    VIEW_SCOREBOARD_OF_STUDENT,
    VIEW_COURSES_OF_STUDENT,
    CREATE_SCHOOL_YEAR,
    CREATE_CLASS,
    CREATE_STUDENT,
    CREATE_SEMESTER,
    CREATE_COURSE,
    ADD_STUDENT_TO_COURSE,
    IMPORT_STUDENTS_IN_CLASS,
    IMPORT_STUDENTS_IN_COURSE,
    IMPORT_SCOREBOARD,
    EXPORT_STUDENTS_IN_COURSE,
    UPDATE_COURSE,
    UPDATE_STUDENT_RESULT,
    EXIT
};

extern std::string renderArgs;
extern Command commandChoice;
extern Font titleFont, textFont;
extern Texture2D defaultAvatar;
extern User currentUser;
extern Semester currentSemester;

#endif
