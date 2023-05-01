#ifndef SHOW_CSV_ERROR_LINES_H
#define SHOW_CSV_ERROR_LINES_H

#include <string>

#include "../../Struct/LinkedList.h"

void showCSVErrorLines(
    Node<int> *duplicateErrors, Node<int> *invalidErrors, int numberOfLines
);

#endif
