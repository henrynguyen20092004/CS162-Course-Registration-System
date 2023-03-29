#include "CheckClass.h"

bool checkClassExists(Node<std::string> *allClassName, const std::string &className) {
    for (; allClassName; allClassName = allClassName->next) {
        if (allClassName->data == className) {
            return true;
        }
    }

    return false;
}
