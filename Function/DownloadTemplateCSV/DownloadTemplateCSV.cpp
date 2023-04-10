#include "DownloadTemplateCSV.h"

// #include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

void downloadTemplateCSV(const std::string &CSVName) {
    std::string savePath, templateLine;
    bool validPath = false;

    do {
        try {
            std::cout
                << "Please enter the path to the folder where you want to save the CSV: ";
            getline(std::cin, savePath);

            if (savePath == "") {
                std::cout << "Please enter a path!\n";
                continue;
            }

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

            validPath = true;
            fin.close();
            fout.close();
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validPath);

    std::cout << "Template successfully downloaded to " << savePath << '\n';
}

void downloadPrompt(const std::string &CSVName, void (*importCallBack)()) {
    int choice;
    bool validChoice = false;

    std::cout << "Do you want to\n"
              << "1. download the template CSV?\n"
              << "2. continue importing?\n";

    do {
        try {
            std::cout << "Enter your choice: ";
            // choice = intInput();

            switch (choice) {
                case 1: {
                    downloadTemplateCSV(CSVName);
                    break;
                }

                case 2: {
                    importCallBack();
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
