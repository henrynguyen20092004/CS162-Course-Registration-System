#include "SplitCourseToIDAndClassName.h"

void splitCourseToIDAndClassName(
    std::string* courseIDAndClassName, const std::string& course
) {
    int hyphenIndex = course.find('-');
    courseIDAndClassName[0] = course.substr(0, hyphenIndex);
    courseIDAndClassName[1] = course.substr(hyphenIndex + 1);
}
