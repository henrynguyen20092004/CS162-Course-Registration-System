#include "SplitCourseToIDAndClassName.h"

void splitCourseToIDAndClassName(std::string* courseIDAndClassName, char* course) {
    int i = 0;

    for (; course[i] != '-'; ++i) {
        courseIDAndClassName[0] += course[i];
    }

    for (++i; i < course[i] != '\0'; ++i) {
        courseIDAndClassName[1] += course[i];
    }
}
