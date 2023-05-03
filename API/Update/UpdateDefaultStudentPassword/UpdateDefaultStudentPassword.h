#ifndef UPDATE_DEFAULT_STUDENT_PASSWORD
#define UPDATE_DEFAULT_STUDENT_PASSWORD

#include "../../../Struct/LinkedList.h"
#include "../../../Struct/Student.h"
#include "../../../Struct/User.h"

void updateDefaultStudentPassword(
    Node<Student> *curStudent, Node<User> *allUsers, const Student &student
);

#endif
