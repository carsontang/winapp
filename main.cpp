// // include the basic windows header files and the Direct3D header files
// #include <stdio.h>
// #include <windows.h>
// #include <windowsx.h>
// #include <d3d11.h>
// #include <d3dcompiler.h>
// #include <DirectXColors.h>
// #include <DirectXMath.h>

// // include the Direct3D Library file
// #pragma comment (lib, "d3d11.lib")

// #define SCREEN_WIDTH 800
// #define SCREEN_HEIGHT 600

// // global declarations
// IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
// ID3D11Device *dev;                     // the pointer to our Direct3D device interface
// ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
// ID3D11RenderTargetView *backbuffer;    // the pointer to our back buffer
// ID3D11VertexShader *pVS;
// ID3D11PixelShader *pPS;

// // function prototypes
// void InitD3D(HWND hWnd);    // sets up and initializes Direct3D
// void RenderFrame(void);     // renders a single frame
// void CleanD3D(void);        // closes Direct3D and releases memory

// // the WindowProc function prototype
// LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// static pD3DCompile get_compiler(void)
// {
//     pD3DCompile compile = nullptr;
//     char d3dcompiler[40] = {};
//     int ver = 49;

//     while (ver > 30) {
//         sprintf_s(d3dcompiler, 40, "D3DCompiler_%02d.dll", ver);

//         HMODULE module = LoadLibraryA(d3dcompiler);
//         if (module) {
//             compile = (pD3DCompile) GetProcAddress(module, "D3DCompile");
//             if (compile) {
//                 break;
//             }
//         }
        
//         ver--;
//     }

//     return compile;
// }

// // the entry point for any Windows program
// int WINAPI WinMain(HINSTANCE hInstance,
//                    HINSTANCE hPrevInstance,
//                    LPSTR lpCmdLine,
//                    int nCmdShow)
// {
//     HWND hWnd;
//     WNDCLASSEX wc;

//     ZeroMemory(&wc, sizeof(WNDCLASSEX));

//     wc.cbSize = sizeof(WNDCLASSEX);
//     wc.style = CS_HREDRAW | CS_VREDRAW;
//     wc.lpfnWndProc = WindowProc;
//     wc.hInstance = hInstance;
//     wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//     // wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
//     wc.lpszClassName = "WindowClass";

//     RegisterClassEx(&wc);

//     RECT wr = {0, 0, 800, 600};
//     AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

//     hWnd = CreateWindowEx(NULL,
//                           "WindowClass",
//                           "Our First Direct3D Program",
//                           WS_OVERLAPPEDWINDOW,
//                           300,
//                           300,
//                           SCREEN_WIDTH,
//                           SCREEN_HEIGHT,
//                           NULL,
//                           NULL,
//                           hInstance,
//                           NULL);

//     ShowWindow(hWnd, nCmdShow);

//     // set up and initialize Direct3D
//     InitD3D(hWnd);

//     // enter the main loop:

//     MSG msg;

//     while(TRUE)
//     {
//         if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//         {
//             TranslateMessage(&msg);
//             DispatchMessage(&msg);

//             if(msg.message == WM_QUIT)
//                 break;
//         }

//         RenderFrame();
//     }

//     // clean up DirectX and COM
//     CleanD3D();

//     return msg.wParam;
// }


// // this is the main message handler for the program
// LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// {
//     switch(message)
//     {
//         case WM_DESTROY:
//             {
//                 PostQuitMessage(0);
//                 return 0;
//             } break;
//     }

//     return DefWindowProc (hWnd, message, wParam, lParam);
// }

// void init_pipeline()
// {
//     ID3D10Blob *VS, *PS;
//     HRESULT hr;

//     static const char *vertex_shader =
//     "struct VOut\
//     { \
//         float4 position : SV_POSITION;\
//         float4 color : COLOR;\
//     };\
//     \
//     VOut VShader(float4 position : POSITION, float4 color : COLOR) \
//     {\
//     VOut output; \
//     output.position = position; \
//     output.color = color; \
//     return output;\
//     }\
//     float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET\
//     {\
//     return color;\
//     }";
    // pD3DCompile compile = get_compiler();
    // hr = compile(
    //     vertex_shader, // pointer to uncompiled ASCII HLSL code
    //     strlen(vertex_shader), // length of HLSL code
    //     "vertex_shader", // source name
    //     nullptr, // macro definitions
    //     nullptr, // include files
    //     "VShader", // name of shader entry point function
    //     "vs_4_0", // shader target
    //     D3DCOMPILE_OPTIMIZATION_LEVEL1,
    //     0,
    //     &VS,
    //     nullptr);
    
    // if (FAILED(hr)) {
    //     printf("Failed to compile vertex shader.\n");
    // }

    // hr = compile(
    //     vertex_shader, // pointer to uncompiled ASCII HLSL code
    //     strlen(vertex_shader), // length of HLSL code
    //     "pixel_shader", // source name
    //     nullptr, // macro definitions
    //     nullptr, // include files
    //     "PShader", // name of shader entry point function
    //     "ps_4_0", // shader target
    //     D3DCOMPILE_OPTIMIZATION_LEVEL1,
    //     0,
    //     &PS,
    //     nullptr);
    
    // if (FAILED(hr)) {
    //     printf("Failed to compile pixel shader.\n");
    // }

//     dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), nullptr, &pVS);
//     dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), nullptr, &pPS);

//     devcon->VSSetShader(pVS, 0, 0);
//     devcon->PSSetShader(pPS, 0, 0);
// }
// // this function initializes and prepares Direct3D for use
// void InitD3D(HWND hWnd)
// {
//     // create a struct to hold information about the swap chain
//     DXGI_SWAP_CHAIN_DESC scd;

//     // clear out the struct for use
//     ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

//     // fill the swap chain description struct
//     scd.BufferCount = 1;                                    // one back buffer
//     scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
//     scd.BufferDesc.Width = SCREEN_WIDTH;
//     scd.BufferDesc.Height = SCREEN_HEIGHT;
//     scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
//     scd.OutputWindow = hWnd;                                // the window to be used
//     scd.SampleDesc.Count = 1;                               // how many multisamples
//     scd.SampleDesc.Quality = 0;                             // multisample quality level
//     scd.Windowed = TRUE;                                    // windowed/full-screen mode
//     scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

//     // create a device, device context and swap chain using the information in the scd struct
//     D3D11CreateDeviceAndSwapChain(NULL,
//                                   D3D_DRIVER_TYPE_HARDWARE,
//                                   NULL,
//                                   NULL,
//                                   NULL,
//                                   NULL,
//                                   D3D11_SDK_VERSION,
//                                   &scd,
//                                   &swapchain,
//                                   &dev,
//                                   NULL,
//                                   &devcon);


//     // get the address of the back buffer
//     ID3D11Texture2D *pBackBuffer;
//     swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

//     // use the back buffer address to create the render target
//     dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
//     pBackBuffer->Release();

//     // set the render target as the back buffer
//     devcon->OMSetRenderTargets(1, &backbuffer, NULL);


//     // Set the viewport
//     D3D11_VIEWPORT viewport;
//     ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

//     viewport.TopLeftX = 0;
//     viewport.TopLeftY = 0;
//     viewport.Width = SCREEN_WIDTH;
//     viewport.Height = SCREEN_HEIGHT;

//     devcon->RSSetViewports(1, &viewport);

//     init_pipeline();
// }


// // this is the function used to render a single frame
// void RenderFrame(void)
// {
//     // clear the back buffer to a deep blue
//     FLOAT rgba[4] = {0.0f, 0.2f, 0.4f, 1.0f};
//     devcon->ClearRenderTargetView(backbuffer, rgba);

//     // do 3D rendering on the back buffer here

//     // switch the back buffer and the front buffer
//     swapchain->Present(0, 0);
// }


// // this is the function that cleans up Direct3D and COM
// void CleanD3D(void)
// {
//     swapchain->SetFullscreenState(FALSE, NULL); // Switch to WINDOWED (FALSE) mode
//     // close and release all existing COM objects
//     pVS->Release();
//     pPS->Release();
//     swapchain->Release();
//     backbuffer->Release();
//     dev->Release();
//     devcon->Release();
// }

// include the basic windows header files and the Direct3D header files
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <stdio.h>

#include "WICTextureLoader.h"

// #include <d3dx11.h>
// #include <d3dx10.h>

// include the Direct3D Library file
// #pragma comment (lib, "d3d11.lib")
// #pragma comment (lib, "d3dx11.lib")
// #pragma comment (lib, "d3dx10.lib")

// define the screen resolution
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

// global declarations
IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
ID3D11Device *dev;                     // the pointer to our Direct3D device interface
ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
ID3D11RenderTargetView *backbuffer;    // the pointer to our back buffer
ID3D11InputLayout *pLayout;            // the pointer to the input layout
ID3D11VertexShader *pVS;               // the pointer to the vertex shader
ID3D11PixelShader *pPS;                // the pointer to the pixel shader
ID3D11Buffer *pVBuffer;                // the pointer to the vertex buffer

// a struct to define a single vertex
typedef struct D3DXCOLOR {
  FLOAT r;
  FLOAT g;
  FLOAT b;
  FLOAT a;
} D3DXCOLOR;

struct VERTEX {
    FLOAT X;
    FLOAT Y;
    FLOAT Z;
    FLOAT R;
    FLOAT G;
    FLOAT B;
    FLOAT A;
    // FLOAT X, Y, Z, R, G, B, A;
    // D3DXCOLOR Color;
};

// function prototypes
void InitD3D(HWND hWnd);    // sets up and initializes Direct3D
void RenderFrame(void);     // renders a single frame
void CleanD3D(void);        // closes Direct3D and releases memory
void InitGraphics(void);    // creates the shape to render
void InitPipeline(void);    // loads and prepares the shaders

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

static pD3DCompile get_compiler(void)
{
    pD3DCompile compile = nullptr;
    char d3dcompiler[40] = {};
    int ver = 49;

    while (ver > 30) {
        sprintf_s(d3dcompiler, 40, "D3DCompiler_%02d.dll", ver);

        HMODULE module = LoadLibraryA(d3dcompiler);
        if (module) {
            compile = (pD3DCompile) GetProcAddress(module, "D3DCompile");
            if (compile) {
                break;
            }
        }
        
        ver--;
    }

    return compile;
}

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "WindowClass";

    RegisterClassEx(&wc);

    RECT wr = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    hWnd = CreateWindowEx(NULL,
                          "WindowClass",
                          "Our First Direct3D Program",
                          WS_OVERLAPPEDWINDOW,
                          300,
                          300,
                          wr.right - wr.left,
                          wr.bottom - wr.top,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hWnd, nCmdShow);

    // set up and initialize Direct3D
    InitD3D(hWnd);

    // enter the main loop:

    MSG msg;

    while(TRUE)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if(msg.message == WM_QUIT)
                break;
        }

        RenderFrame();
    }

    // clean up DirectX and COM
    CleanD3D();

    return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
void InitD3D(HWND hWnd)
{
    // create a struct to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC scd;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                   // one back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
    scd.BufferDesc.Width = SCREEN_WIDTH;                   // set the back buffer width
    scd.BufferDesc.Height = SCREEN_HEIGHT;                 // set the back buffer height
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
    scd.OutputWindow = hWnd;                               // the window to be used
    scd.SampleDesc.Count = 4;                              // how many multisamples
    scd.Windowed = TRUE;                                   // windowed/full-screen mode
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow full-screen switching

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL,
                                  D3D_DRIVER_TYPE_HARDWARE,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  D3D11_SDK_VERSION,
                                  &scd,
                                  &swapchain,
                                  &dev,
                                  NULL,
                                  &devcon);


    // get the address of the back buffer
    ID3D11Texture2D *pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use the back buffer address to create the render target
    dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    pBackBuffer->Release();

    // set the render target as the back buffer
    devcon->OMSetRenderTargets(1, &backbuffer, NULL);


    // Set the viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = SCREEN_WIDTH;
    viewport.Height = SCREEN_HEIGHT;

    devcon->RSSetViewports(1, &viewport);

    InitPipeline();
    InitGraphics();
}


// this is the function used to render a single frame
void RenderFrame(void)
{
    // clear the back buffer to a deep blue
    const FLOAT color_rgba[4] = {0.0f, 0.2f, 0.4f, 1.0f};
    devcon->ClearRenderTargetView(backbuffer, color_rgba);

    // select which vertex buffer to display
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;
    devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

    // select which primtive type we are using
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // draw the vertex buffer to the back buffer
    devcon->Draw(4, 0);

    // switch the back buffer and the front buffer
    swapchain->Present(0, 0);
}


// this is the function that cleans up Direct3D and COM
void CleanD3D(void)
{
    swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

    // close and release all existing COM objects
    pLayout->Release();
    pVS->Release();
    pPS->Release();
    pVBuffer->Release();
    swapchain->Release();
    backbuffer->Release();
    dev->Release();
    devcon->Release();
}

// this is the function that creates the shape to render
void InitGraphics()
{
    // create a triangle using the VERTEX struct
    float rgba0[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    float rgba1[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

//    VERTEX OurVertices[] = {
//     {0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
//     {0.45f, -0.5, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
//     {-0.45f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}
//     };
   VERTEX OurVertices[] = {
    {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
    {-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
    {0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
    {0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}
    // {0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
    // {0.5f, -0.5, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
    // {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}
    };

    // create the vertex buffer
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
    bd.ByteWidth = sizeof(VERTEX) * 4;             // size is the VERTEX struct * 3
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

    dev->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer


    // copy the vertices into the buffer
    D3D11_MAPPED_SUBRESOURCE ms;
    devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
    memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // copy the data
    devcon->Unmap(pVBuffer, NULL);                                      // unmap the buffer
}


// this function loads and prepares the shaders
void InitPipeline()
{
    // HRESULT CreateWICTextureFromFile( _In_ ID3D11Device* d3dDevice,
    //                               _In_opt_ ID3D11DeviceContext* d3dContext,
    //                               _In_z_ const wchar_t* szFileName,
    //                               _Out_opt_ ID3D11Resource** texture,
    //                               _Out_opt_ ID3D11ShaderResourceView** textureView,
    //                               _In_ size_t maxsize = 0
    //                             );
    HRESULT hr;
    ID3D11Resource *pTexture;
    ID3D11ShaderResourceView *pTextureView;

    hr = CreateWICTextureFromFile(
        dev,
        devcon,
        L"C:\\Users\\Carson Tang\\source\\repos\\carson-winapp\\tab.png",
        &pTexture,
        &pTextureView);
    if (FAILED(hr)) {
        OutputDebugStringA("[VisorGG] failed to load tab.png");
        return;
    }

    // load and compile the two shaders
    ID3D10Blob *VS, *PS;
    // D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
    // D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

    static const char *vertex_shader_string =
    "struct VOut \
    { \
    float4 position : SV_POSITION; \
    float4 color : COLOR; \
    }; \
    \
    VOut VShader(float4 position : POSITION, float4 color : COLOR) \
    { \
    VOut output; \
    output.position = position; \
    output.color = color; \
    return output; \
    }";

    static const char *pixel_shader_string = 
    "float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET \
    { \
    return color; \
    }";

    pD3DCompile compile = get_compiler();
    hr = compile(
        vertex_shader_string, // pointer to uncompiled ASCII HLSL code
        strlen(vertex_shader_string), // length of HLSL code
        "vertex_shader", // source name
        nullptr, // macro definitions
        nullptr, // include files
        "VShader", // name of shader entry point function
        "vs_4_0", // shader target
        D3DCOMPILE_OPTIMIZATION_LEVEL1,
        0,
        &VS,
        nullptr);
    
    if (FAILED(hr)) {
        printf("Failed to compile vertex shader.\n");
    }

    hr = compile(
        pixel_shader_string, // pointer to uncompiled ASCII HLSL code
        strlen(pixel_shader_string), // length of HLSL code
        "pixel_shader", // source name
        nullptr, // macro definitions
        nullptr, // include files
        "PShader", // name of shader entry point function
        "ps_4_0", // shader target
        D3DCOMPILE_OPTIMIZATION_LEVEL1,
        0,
        &PS,
        nullptr);
    
    if (FAILED(hr)) {
        printf("Failed to compile pixel shader.\n");
    }

    // encapsulate both shaders into shader objects
    dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
    dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

    // set the shader objects
    devcon->VSSetShader(pVS, 0, 0);
    devcon->PSSetShader(pPS, 0, 0);

    // create the input layout object
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
    devcon->IASetInputLayout(pLayout);
}
