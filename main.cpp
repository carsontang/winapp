// #include <windows.h>    // include the basic windows header file

// // the entry point for any Windows program
// int WINAPI WinMain(HINSTANCE hInstance,
//                    HINSTANCE hPrevInstance,
//                    LPSTR lpCmdLine,
//                    int nShowCmd)
// {
//     // create a "Hello World" message box using MessageBox()
//     MessageBoxW(NULL,
//                L"Hello World!",
//                L"Just another Hello World program!",
//                MB_ICONERROR | MB_OK);

//     // return 0 to Windows
//     return 0;
// }

// include the basic windows header file
#include <stdio.h>
#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")
#include <windows.h>
#include <windowsx.h>

typedef HRESULT (WINAPI *d3d10create_t)(IDXGIAdapter*, D3D10_DRIVER_TYPE,
		HMODULE, UINT, UINT, DXGI_SWAP_CHAIN_DESC*,
		IDXGISwapChain**, IUnknown**);

typedef struct dxgi_info {
    IDXGISwapChain      *swap;
    ID3D11Device        *device;
    ID3D11DeviceContext *context;
} dxgi_info;

void init_d3d(HWND hwnd, dxgi_info *info)
{
    DXGI_SWAP_CHAIN_DESC sd;

    ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));

    sd.BufferCount       = 2; // 2 backbuffers
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage       = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow      = hwnd;
    sd.SampleDesc.Count  = 1;
    sd.Windowed          = TRUE;

    D3D11CreateDeviceAndSwapChain(
        NULL,                         // default graphics adapter
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,                         // Software
        NULL,                         // Flags
        NULL,                         // Feature levels
        NULL,
        D3D11_SDK_VERSION,
        &sd,
        &(info->swap),
        &(info->device),
        NULL,
        &(info->context)
    );
}

void dxgi_free(dxgi_info *info) {
    unsigned long device_count = 0;
    unsigned long context_count = 0;
    unsigned long swap_count = 0;

    if (info->device) {
        device_count = info->device->Release();
    }

    if (info->context) {
        context_count = info->context->Release();
    }

    if (info->swap) {
        swap_count = info->swap->Release();
    }

    printf("device: %lu\n", device_count);
    printf("context: %lu\n", context_count);
    printf("swap: %lu\n", swap_count);
}

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    // the handle for the window, filled by a function
    HWND hwnd;
    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "WindowClass1";

    // register the window class
    RegisterClassEx(&wc);

    // create the window and use the result as the handle
    hwnd = CreateWindowEx(WS_EX_ACCEPTFILES,
                          "WindowClass1",    // name of the window class
                          "Our First Windowed Program",   // title of the window
                          WS_OVERLAPPEDWINDOW,    // window style
                          300,    // x-position of the window
                          300,    // y-position of the window
                          500,    // width of the window
                          400,    // height of the window
                          NULL,    // we have no parent window, NULL
                          NULL,    // we aren't using menus, NULL
                          hInstance,    // application handle
                          NULL);    // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hwnd, nCmdShow);

    dxgi_info info;
    // set up and initialize D3D
    init_d3d(hwnd, &info);

    // enter the main loop:

    // this struct holds Windows event messages
    MSG msg;

    // wait for the next message in the queue, store the result in 'msg'
    while(GetMessage(&msg, NULL, 0, 0))
    {
        // translate keystroke messages into the right format
        TranslateMessage(&msg);

        // send the message to the WindowProc function
        DispatchMessage(&msg);
    }

    // return this part of the WM_QUIT message to Windows

    dxgi_free(&info);
    return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed
        case WM_DESTROY:
            {
                // close the application entirely
                PostQuitMessage(0);
                return 0;
            } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}