#include "CheckClass.h"

bool checkClassExists(Node<std::string> *allClassName, const std::string &className) {
    while (allClassName) {
        if (allClassName->data == className) {
            return true;
        }

        allClassName = allClassName->next;
    }

    return false;
}
