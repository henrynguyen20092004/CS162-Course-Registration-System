#include "GetAllSchoolYears.h"

#include "../OpenFile/OpenFile.h"

Node<std::string> *getSchoolYear() {
    std::ifstream fin;
    readFile(fin, "Data/SchoolYear.txt");
    std::string schoolYearName;
    Node<std::string> *result = nullptr, *cur = nullptr;
    while (!fin.eof()) {
        getline(fin, schoolYearName);
        if (schoolYearName == "") {
            break;
        }
        Node<std::string> *tmp = new Node(schoolYearName);
        if (result == nullptr) {
            result = tmp;
            cur = result;
        } else {
            cur->next = tmp;
            cur = cur->next;
        }
    }
    fin.close();
    return result;
}
