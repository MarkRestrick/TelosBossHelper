/*

#include <Windows.h>
#include <iostream>

using namespace std;

HWND windowHandle;



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{

	
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIconSm = 0;

	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = "Mark's Class";
	wc.lpszMenuName = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	//WS_OVERLAPPEDWINDOW | WS_VISIBLE
	RegisterClassEx(&wc);

	windowHandle = CreateWindowEx(WS_EX_ACCEPTFILES, "Mark's Class", "WindowTest", WS_EX_COMPOSITED | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST, 100, 100, 800, 600, 0, 0, hInstance, 0);

	// Set WS_EX_LAYERED on this window 
	SetWindowLong(windowHandle, GWL_EXSTYLE, GetWindowLong(windowHandle, GWL_EXSTYLE) | WS_EX_LAYERED);

	if (windowHandle == 0)
		MessageBoxA(0, "Create Window Failed", "Error Message", 0);

	ShowWindow(windowHandle, showCmd);

	SetLayeredWindowAttributes(windowHandle, 0, (255 * 70) / 100, LWA_ALPHA);

	UpdateWindow(windowHandle);

	MSG msg;

	SecureZeroMemory(&msg, sizeof(MSG));

	int returnValue = 0;

	while ((returnValue = GetMessage(&msg, 0, 0, 0)) != 0)
	{

		
		if (returnValue == -1)
		{
			MessageBoxA(windowHandle, "GetMessage Failed!", "Error MEssage", 0);
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);

		
	}

	return (int)msg.wParam;
}

*/