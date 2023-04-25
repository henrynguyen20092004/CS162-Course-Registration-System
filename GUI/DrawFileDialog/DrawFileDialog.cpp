#include "DrawFileDialog.h"

#include <windows.h>

#include <cstring>

void openFileDialog(char* filePathInput, const char* filter) {
    OPENFILENAME openFile;
    char filePath[256], currentDir[256];

    GetCurrentDirectory(256, currentDir);
    ZeroMemory(&openFile, sizeof(openFile));
    openFile.lStructSize = sizeof(openFile);
    openFile.hwndOwner = nullptr;
    openFile.lpstrFile = filePath;
    openFile.lpstrFile[0] = '\0';
    openFile.nMaxFile = sizeof(filePath);
    openFile.lpstrFilter = filter;
    openFile.nFilterIndex = 1;
    openFile.lpstrFileTitle = nullptr;
    openFile.nMaxFileTitle = 0;
    openFile.lpstrInitialDir = nullptr;
    openFile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&openFile)) {
        SetCurrentDirectory(currentDir);
        strcpy(filePathInput, filePath);
    }
}
