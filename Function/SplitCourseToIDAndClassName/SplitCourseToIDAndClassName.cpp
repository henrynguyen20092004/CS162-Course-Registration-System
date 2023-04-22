#include "SplitCourseToIDAndClassName.h"

#include "../CheckAndConvertString/CheckAndConvertString.h"

void splitCourseToIDAndClassName(std::string* courseIDAndClassName, char* course) {
    std::string courseString = checkDropDownAndConvertToString(course, "course");
    int hyphenIndex = courseString.find('-');
    courseIDAndClassName[0] = courseString.substr(0, hyphenIndex);
    courseIDAndClassName[1] = courseString.substr(hyphenIndex + 1);
}
