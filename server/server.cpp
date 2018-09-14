#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE 1920

bool persist_buffer(void *buffer, int filecount)
{
    HANDLE hFile = CreateFile(TEXT("C:\\Users\\Carson Tang\\Documents\\buffer.bmp"),
        GENERIC_WRITE,
        0, // the pipe can only be opened once
        nullptr,
        CREATE_ALWAYS,
        0,
        nullptr);
    
    DWORD dwWritten;
    DWORD total_bytes = 0;
    while (WriteFile(hFile, buffer, 1920*1040*4, &dwWritten, NULL) != FALSE) {
        total_bytes += dwWritten;
    }

    CloseHandle(hFile);
    if (total_bytes == (1920 * 1040 * 4)) {
        printf("Successfully persisted a bitmap!\n");
        return true;
    }
    return false;
}

int main(void)
{
    HANDLE hPipe;
    uint8_t buffer[BUFFER_SIZE];
    DWORD dwRead;

    OutputDebugString(TEXT("[VisorGG] Before pipe creation"));

    hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Pipe"),
                            PIPE_ACCESS_DUPLEX,
                            PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
                            1,
                            BUFFER_SIZE,
                            BUFFER_SIZE,
                            NMPWAIT_USE_DEFAULT_WAIT,
                            NULL);
    int filecount = 0;
    OutputDebugString(TEXT("[VisorGG] Before loop"));
    while (hPipe != INVALID_HANDLE_VALUE)
    {
        OutputDebugString(TEXT("[VisorGG] Inside loop"));
        if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // wait for someone to connect to the pipe
        {
            DWORD num_read_bytes = 0;
            HANDLE hFile = CreateFile(TEXT("C:\\Users\\Carson Tang\\Documents\\buffer.bmp"),
                    GENERIC_WRITE,
                    0, // the pipe can only be opened once
                    nullptr,
                    CREATE_ALWAYS,
                    0,
                    nullptr);
            
            DWORD dwPos;
            DWORD dwWritten;

            while (ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL) && dwRead > 0)
            {
                dwPos = SetFilePointer(hFile, 0, NULL, FILE_END);
                LockFile(hFile, dwPos, 0, dwRead, 0);
                WriteFile(hFile, buffer, dwRead, &dwWritten, NULL);
                UnlockFile(hFile, dwPos, 0, dwRead, 0);
                // num_read_bytes += dwRead;
                // if (num_read_bytes == (1920 * 1040 * 4)) {
                //     bool persisted = persist_buffer(buffer, filecount);
                //     if (!persisted) {
                //         printf("Unable to persist buffer\n");
                //     } else {
                //         filecount++;
                //     }
                // }
            }
            CloseHandle(hFile);
        }

        DisconnectNamedPipe(hPipe);
    }

    return 0;
}