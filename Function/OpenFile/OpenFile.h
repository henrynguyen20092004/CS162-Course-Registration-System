#ifndef OPEN_FILE_H
#define OPEN_FILE_H

#include <fstream>

void readFile(std::ifstream &fin, const std::string &filePath);
void writeFile(
    std::ofstream &fout, const std::string &filePath,
    std::ios::openmode openmode = std::ios::out
);

#endif
