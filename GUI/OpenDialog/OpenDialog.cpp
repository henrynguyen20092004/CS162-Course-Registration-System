#include "OpenDialog.h"

#include <shobjidl.h>

#include <cstring>
#include <stdexcept>

void showFileDialogAndGetPath(HRESULT hResult, IFileOpenDialog *iFileOpen, char *path) {
    hResult = iFileOpen->Show(nullptr);

    if (FAILED(hResult)) {
        throw 0;
    }

    IShellItem *pItem;
    hResult = iFileOpen->GetResult(&pItem);

    if (FAILED(hResult)) {
        throw 0;
    }

    PWSTR FilePath;
    hResult = pItem->GetDisplayName(SIGDN_FILESYSPATH, &FilePath);

    if (FAILED(hResult)) {
        pItem->Release();
        throw 0;
    }

    int count = wcslen(FilePath);
    wcstombs(path, FilePath, count);
    path[count] = '\0';
    CoTaskMemFree(FilePath);
}

void openDialog(char *path, bool isFolderDialog) {
    IFileOpenDialog *iFileOpen;

    try {
        HRESULT hResult =
            CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

        if (FAILED(hResult)) {
            return;
        }

        hResult = CoCreateInstance(
            CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&iFileOpen)
        );

        if (FAILED(hResult)) {
            CoUninitialize();
            return;
        }

        DWORD flags;
        hResult = iFileOpen->GetOptions(&flags);

        if (FAILED(hResult)) {
            throw 0;
        }

        if (isFolderDialog) {
            hResult = iFileOpen->SetOptions(flags | FOS_PICKFOLDERS);

            if (FAILED(hResult)) {
                throw 0;
            }

            showFileDialogAndGetPath(hResult, iFileOpen, path);
        } else {
            hResult = iFileOpen->SetOptions(flags);

            if (FAILED(hResult)) {
                throw 0;
            }

            COMDLG_FILTERSPEC fileTypes{L"CSV Files (*.csv)", L"*.csv"};
            hResult = iFileOpen->SetFileTypes(1, &fileTypes);

            if (FAILED(hResult)) {
                throw 0;
            }

            showFileDialogAndGetPath(hResult, iFileOpen, path);
        }

        iFileOpen->Release();
        CoUninitialize();
    } catch (...) {
        iFileOpen->Release();
        CoUninitialize();
    }
}

void openFileDialog(char *filePathInput) { openDialog(filePathInput, false); }

void openFolderDialog(char *folderPathInput) { openDialog(folderPathInput, true); }
