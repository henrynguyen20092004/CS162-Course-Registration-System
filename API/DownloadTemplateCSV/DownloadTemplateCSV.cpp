#include "DownloadTemplateCSV.h"

#include "../OpenFile/OpenFile.h"

void downloadTemplateCSV(const std::string &CSVName, char *inputtedCSVPath) {
    std::string savePath = inputtedCSVPath, templateLine;

    if (savePath.back() != '\\' && savePath.back() != '/') {
        savePath += savePath.find('\\') != std::string::npos ? '\\' : '/';
    }

    savePath += CSVName;
    std::ifstream fin;
    std::ofstream fout;
    readFile(fin, "TemplateCSV/" + CSVName);
    writeFile(fout, savePath);

    while (fin.good()) {
        getline(fin, templateLine);
        fout << templateLine;
    }

    fin.close();
    fout.close();
}
