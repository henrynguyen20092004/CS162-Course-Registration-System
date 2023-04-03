#ifndef CREATE_STUDENT_ACCOUNT_H
#define CREATE_STUDENT_ACCOUNT_H

#include "../../Struct/Student.h"
#include "../../Struct/User.h"

std::string getPasswordFromDateOfBirth(const std::string &dateOfBirth);
User createAccount(const Student &student);
void createStudentAccount(const Student &student);

#endif
