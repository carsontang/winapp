#include <windows.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    HANDLE hPipe;
    DWORD dwWritten;


    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Pipe"), 
                       GENERIC_READ | GENERIC_WRITE, 
                       0,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);
    if (hPipe != INVALID_HANDLE_VALUE)
    {
        HANDLE hImage = CreateFileW(
            L"C:\\Users\\Carson Tang\\Documents\\tab.bmp",
            GENERIC_READ | GENERIC_WRITE,
            0, // the pipe can only be opened once
            nullptr,
            OPEN_EXISTING,
            0,
            nullptr);
        
        if (hImage == INVALID_HANDLE_VALUE) {
            OutputDebugStringA("[VisorGG] Unable to create file");
            return false;
        }

        HANDLE hFilemap = CreateFileMapping(
            hImage,
            nullptr,
            PAGE_READWRITE,
            0,
            1920 * 1040 * 4,
            nullptr);
        
        if (hFilemap == INVALID_HANDLE_VALUE) {
            OutputDebugStringA("[VisorGG] Unable to create file map");
            return false;
        }

        uint8_t *image_buffer = (uint8_t*)MapViewOfFile(hFilemap, FILE_MAP_WRITE, 0, 0, 0);

        DWORD total_written = 0;

        while (WriteFile(hPipe,
                  image_buffer,
                  1920 * 1040 * 4,   // = length of string + terminating '\0' !!!
                  &dwWritten,
                  NULL) != FALSE) {
            total_written += dwWritten;
            if (total_written == (1920 * 1040 * 4)) {
                printf("Done writing buffer to server\n");
                break;
            }
        }

        CloseHandle(hPipe);
    }

    return (0);
}