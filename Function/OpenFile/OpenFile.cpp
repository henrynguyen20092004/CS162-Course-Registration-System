#include "OpenFile.h"

void readFile(std::ifstream &fin, const std::string &filePath) {
    fin.open(filePath);

    if (!fin.is_open()) {
        throw std::invalid_argument("File doesn't exist or is inaccessible!");
    }
}

void writeFile(
    std::ofstream &fout, const std::string &filePath, std::ios::openmode openmode
) {
    fout.open(filePath, openmode);

    if (!fout.is_open()) {
        throw std::invalid_argument(
            "Illegal path, the parent folder doesn't exist or it's inaccessible!"
        );
    }
}
