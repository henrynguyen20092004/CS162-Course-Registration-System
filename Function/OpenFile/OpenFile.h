#ifndef OPEN_FILE_H
#define OPEN_FILE_H

#include <fstream>

void readFile(std::ifstream &fin, std::string filePath);
void writeFile(std::ofstream &fout, std::string filePath);

#endif
