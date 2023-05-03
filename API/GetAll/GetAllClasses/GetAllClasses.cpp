#include "GetAllClasses.h"

void readClass(std::ifstream &fin, std::string &className) { getline(fin, className); }

Node<std::string> *getAllClasses() { return getAll("Data/Class.txt", &readClass); }
