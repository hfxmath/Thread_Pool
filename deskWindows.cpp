// 桌面窗口.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <string>
#include "桌面窗口.h"
#include <d3d9.h>
#include <GdiPlus.h>
#include <iostream>
#include <thread>
#include <dwmapi.h>
#pragma  comment(lib, "dwmapi.lib")

using namespace std;
using namespace Gdiplus;
#define MAX_LOADSTRING 100

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"d3d9.lib")

/*d3d_begin---global_var*/
const int screen_w = 500, screen_h = 500;
const int pixel_w = 320, pixel_h = 180;
const int bpp = 12;
FILE *fp = NULL;
IDirect3D9            *g_pD3DScreenCapture = NULL;
IDirect3DDevice9    *g_pd3dDevice = NULL;
IDirect3DSurface9    *g_pSurface = NULL;
LPVOID    screenCaptureData = NULL;
unsigned char buffer[pixel_w * pixel_h * bpp / 8];
RECT m_rtViewport;
/*d3d_end-----global_var*/


void Cleanup()
{
	if (g_pSurface)
		g_pSurface->Release();
	if (g_pd3dDevice)
		g_pd3dDevice->Release();
	if (g_pD3DScreenCapture)
		g_pD3DScreenCapture->Release();
}

HRESULT    InitD3D(HWND hWnd)
{
	Cleanup();


	g_pD3DScreenCapture = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;


	GetClientRect(hWnd, &m_rtViewport);

	g_pD3DScreenCapture->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice);

	/*//RGB
	g_pd3dDevice->CreateOffscreenPlainSurface(
		pixel_w, pixel_h,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&g_pSurface,
		NULL);*/

	//YUV
	g_pd3dDevice->CreateOffscreenPlainSurface(
		pixel_w, pixel_h,
		(D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'),
		D3DPOOL_DEFAULT,
		&g_pSurface,
		NULL);


	return S_OK;
}
//direct实现的截图
void directScreenCapture()
{
	HRESULT lRet;
	if (fread(buffer, 1, pixel_w * pixel_h * bpp / 8, fp) != pixel_w * pixel_h * bpp / 8)
	{
		// Loop
		fseek(fp, 0, SEEK_SET);
		fread(buffer, 1, pixel_w * pixel_h * bpp / 8, fp);
	}

	D3DLOCKED_RECT d3d_rect;
	if (FAILED(g_pSurface->LockRect(&d3d_rect, NULL, D3DLOCK_DONOTWAIT)))
	{
		return;
	}

	byte *pSrc = buffer;
	byte *pDest = (BYTE *)d3d_rect.pBits;
	int stride = d3d_rect.Pitch;
	auto i = 0;

	//Copy Data
	for (i = 0; i < pixel_h; i++)
	{
		memcpy(pDest + i * stride, pSrc + i * pixel_w, pixel_w);
	}
	for (i = 0; i < pixel_h / 2; i++)
	{
		memcpy(pDest + stride * pixel_h + i * stride / 2, pSrc + pixel_w * pixel_h + pixel_w * pixel_h / 4 + i * pixel_w / 2, pixel_w / 2);
	}
	for (i = 0; i < pixel_h / 2; i++)
	{
		memcpy(pDest + stride * pixel_h + stride * pixel_h / 4 + i * stride / 2, pSrc + pixel_w * pixel_h + i * pixel_w / 2, pixel_w / 2);
	}

	lRet = g_pSurface->UnlockRect();

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	g_pd3dDevice->BeginScene();
	IDirect3DSurface9 *pBackBuffer = NULL;

	g_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	g_pd3dDevice->StretchRect(g_pSurface, NULL, pBackBuffer, &m_rtViewport, D3DTEXF_LINEAR);
	g_pd3dDevice->EndScene();
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	pBackBuffer->Release();

}

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID    CALLBACK	Capture(HWND);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

	MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
typedef struct SParam
{
	HWND hWnd;
}uParam, *sParam;


static HANDLE thread_cap;
DWORD WINAPI ThreadFun(PVOID pParam)
{
	sParam sparam;
	sparam = (sParam)pParam;

	if (thread_cap)
	{
		Capture(sparam->hWnd);
	}
	return TRUE;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }

   if (FAILED(InitD3D(hWnd)))
   {
	   return -1;
   }

   SParam sparam;
   SParam *p;

   sparam.hWnd = hWnd;
   p = &sparam;

   thread_cap = CreateThread(NULL, 0, ThreadFun, p, 0, NULL);
  
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case IDM_CAPTURE:
				Capture(hWnd);
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


BOOL MyBringWindowToTop(HWND hWnd)
{
	HWND hFrgWnd = ::GetForegroundWindow();
	AttachThreadInput(GetWindowThreadProcessId(hFrgWnd, NULL), GetCurrentThreadId(), TRUE);
	::SetForegroundWindow(hWnd);
	::BringWindowToTop(hWnd);

	if (!::BringWindowToTop(hWnd))
	{
		printf("BringWindowToTop Error %d/n", GetLastError());
	}
	else
	{
		printf("BringWindowToTop OK/n");
	}
	if (!::SetForegroundWindow(hWnd))
	{
		printf("SetForegroundWindow Error %d/n", GetLastError());
	}
	else
	{
		printf("SetForegroundWindow OK/n");
	}

	SwitchToThisWindow(hWnd, TRUE);

	AttachThreadInput(GetWindowThreadProcessId(hFrgWnd, NULL),
		GetCurrentThreadId(), FALSE);

	return TRUE;
}

VOID CALLBACK Capture(HWND hWnd)
{
	int ret = WaitForSingleObject(thread_cap, 100);

	/*
	HWND hq = FindWindow(NULL, "QQ");
	RECT rect;
	GetWindowRect(hq, &rect);
	int w = rect.right - rect.left, h = rect.bottom - rect.top;
	MoveWindow(hq, 100, 100, w, h, false);	//移动QQ窗口位置  
	HWND hd = GetDesktopWindow();//得到桌面窗口  
	GetWindowRect(hd, &rect);
	fp = fopen("./test_yuv420p_320x180.yuv", "rb+");
	assert(fp != NULL);
	*/

	HWND hq = FindWindow(NULL, "QQ");
	RECT rect;
	GetWindowRect(hq, &rect);

	directScreenCapture();
	//while (1)
	{
		//directScreenCapture();
	}
}
