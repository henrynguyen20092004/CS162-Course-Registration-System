#include "DownloadTemplateCSV.h"

#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"
#include "../ValidatePath/ValidatePath.h"

void downloadTemplateCSV(const std::string &CSVName) {
    std::ifstream fin;
    std::ofstream fout;
    std::string savePath, templateLine;
    bool validPath = false;

    do {
        try {
            std::cout
                << "Please enter the path to the folder where you want to save the CSV: ";
            getline(std::cin, savePath);
            validatePath(savePath);

            if (savePath.back() != '\\' && savePath[savePath.size() - 2] != '\\' &&
                savePath.back() != '/') {
                savePath += '/';
            }

            readFile(fin, "TemplateCSV/" + CSVName);
            writeFile(fout, savePath + CSVName);

            while (fin.good()) {
                getline(fin, templateLine);
                fout << templateLine;
            }

            validPath = true;
            fin.close();
            fout.close();
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validPath);

    std::cout << "The template has been downloaded to " << savePath + CSVName << '\n';
}

void downloadPrompt(const std::string &CSVName, void (*importFunction)()) {
    int choice;
    bool validChoice = false;

    std::cout << "Do you want to\n"
              << "1. download the template CSV?\n"
              << "2. continue importing?\n";

    do {
        try {
            std::cout << "Enter your choice: ";
            choice = intInput();

            switch (choice) {
                case 1: {
                    downloadTemplateCSV(CSVName);
                    break;
                }

                case 2: {
                    importFunction();
                    break;
                }

                default: {
                    std::cout << "Invalid option, please try again!\n";
                    continue;
                }
            }

            validChoice = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validChoice);
}
