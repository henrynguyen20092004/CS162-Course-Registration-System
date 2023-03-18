#include "OpenFile.h"

std::string getFileName(const std::string &filePath) {
    int fileNameFinder = filePath.find_last_of('/');
    return filePath.substr(fileNameFinder + 1);
}

void readFile(std::ifstream &fin, const std::string &filePath) {
    std::string fileName = getFileName(filePath);

    fin.open(filePath);
    if (!fin.is_open()) {
        throw std::runtime_error(
            "Can't open " + fileName + ", file not found!\n"
        );
    }
}

void writeFile(
    std::ofstream &fout, const std::string &filePath,
    std::ios::openmode openmode
) {
    std::string fileName = getFileName(filePath);

    fout.open(filePath, openmode | std::ios::out);
    if (!fout.is_open()) {
        throw std::runtime_error(
            "Can't open " + fileName + ", file not found!\n"
        );
    }
}
