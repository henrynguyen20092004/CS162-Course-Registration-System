#include "OpenFile.h"

void readFile(std::ifstream &fin, const std::string &filePath) {
    fin.open(filePath);

    if (!fin.is_open()) {
        throw std::runtime_error("Can't read from " + filePath + ", file not found!\n");
    }
}

void writeFile(
    std::ofstream &fout, const std::string &filePath, std::ios::openmode openmode
) {
    fout.open(filePath, openmode | std::ios::out);

    if (!fout.is_open()) {
        throw std::runtime_error(
            "Can't write to " + filePath +
            ", either the parent folder doesn't exists or it is inaccessible!\n"
        );
    }
}
