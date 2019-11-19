/*
* Viry3D
* Copyright 2014-2019 by Stack - stackos@qq.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <Windows.h>
#include <windowsx.h>
#include <io.h>
#include "Tuzzi.h"
#include "string/String.h"
#include "Tutorial_01/DemoApplication.h"

using namespace tuzzi;

static void SwitchFullScreen(HWND hWnd)
{
    static bool full_screen = false;
    static int old_style = 0;
    static RECT old_pos;

    if (!full_screen)
    {
        full_screen = true;

        old_style = GetWindowLong(hWnd, GWL_STYLE);
        GetWindowRect(hWnd, &old_pos);

        RECT rect;
        HWND desktop = GetDesktopWindow();
        GetWindowRect(desktop, &rect);
        SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPED);
        SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, rect.right, rect.bottom, SWP_SHOWWINDOW);
    }
    else
    {
        full_screen = false;

        SetWindowLong(hWnd, GWL_STYLE, old_style);
        SetWindowPos(hWnd, HWND_NOTOPMOST,
            old_pos.left,
            old_pos.top,
            old_pos.right - old_pos.left,
            old_pos.bottom - old_pos.top,
            SWP_SHOWWINDOW);
    }
}

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
			Tuzzi::instance()->destroy();
            DestroyWindow(hWnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    String name = "TuzziApp";
	int window_width = 1280;
	int window_height = 720;

    WNDCLASSEX win_class;
    ZeroMemory(&win_class, sizeof(win_class));

    win_class.cbSize = sizeof(WNDCLASSEX);
    win_class.style = CS_HREDRAW | CS_VREDRAW;
    win_class.lpfnWndProc = WindowProc;
    win_class.cbClsExtra = 0;
    win_class.cbWndExtra = 0;
    win_class.hInstance = hInstance;
    win_class.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    win_class.lpszMenuName = nullptr;
    win_class.lpszClassName = name.c_str();
    win_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
    win_class.hIcon = (HICON) LoadImage(nullptr, "icon.ico", IMAGE_ICON, SM_CXICON, SM_CYICON, LR_LOADFROMFILE);
    win_class.hIconSm = win_class.hIcon;

    if (!RegisterClassEx(&win_class))
    {
        return 0;
    }

    DWORD style = WS_OVERLAPPEDWINDOW;
    DWORD style_ex = 0;

    RECT wr = { 0, 0, window_width, window_height };
    AdjustWindowRect(&wr, style, FALSE);

    int x = (GetSystemMetrics(SM_CXSCREEN) - window_width) / 2 + wr.left;
    int y = (GetSystemMetrics(SM_CYSCREEN) - window_height) / 2 + wr.top;
    int w = wr.right - wr.left;
    int h = wr.bottom - wr.top;

    if (GetSystemMetrics(SM_CXSCREEN) == window_width)
    {
        x = wr.left;
        y = wr.top;
    }

    HWND hwnd = CreateWindowEx(
        style_ex,			// window ex style
        name.c_str(),		// class name
        name.c_str(),		// app name
        style,			    // window style
        x, y,				// x, y
        w, h,               // w, h
        nullptr,		    // handle to parent
        nullptr,            // handle to menu
        hInstance,			// hInstance
        nullptr);           // no extra parameters
    if (!hwnd)
    {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOW);

	Tuzzi::instance()->init();
	SharedPtr<Application> app = MakeShared<DemoApplication>();
	Tuzzi::instance()->loadApplication(app);

    bool exit = false;
    MSG msg;
	
    while (true)
    {
        while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                exit = true;
                break;
            }
            else
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }

        if (exit)
        {
            break;
        }
		
		Tuzzi::instance()->update();
    }

    return 0;
}
