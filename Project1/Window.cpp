#include "Window.h"
#include "resource.h"

// Global variables
HINSTANCE m_hInstance;						// Current instane

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int width = 640;
	int height = 480;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		HMENU hMenubar = CreateMenu();		// hMenu Paramter
		HMENU hFile = CreateMenu();			// Menu Items
		HMENU hEdit = CreateMenu();			// -
		HMENU hHelp = CreateMenu();			// -

		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile, L"File");
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hEdit, L"Edit");
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hHelp, L"Help");

		// File items
		AppendMenu(hFile, MF_STRING, ID_FILE_SAVE, L"Save");
		AppendMenu(hFile, MF_STRING, ID_FILE_LOAD, L"Load");
		AppendMenu(hFile, MF_STRING, ID_FILE_EXIT, L"Exit");

		// Edit items
		AppendMenu(hEdit, MF_STRING, ID_EDIT_UNDO, L"Undo");
		AppendMenu(hEdit, MF_STRING, ID_EDIT_REDO, L"Redo");

		// Help items
		AppendMenu(hHelp, MF_STRING, ID_HELP_ABOUT, L"About");

		SetMenu(hWnd, hMenubar);
		break;
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId);
		
	}

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return(0);

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


Window::Window()
	: m_hInstance(GetModuleHandle(nullptr))
{
	const wchar_t* CLASS_NAME = L"A Window Class";

	WNDCLASS wndClass = {};

	// Properties of Window Class
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_OVERLAPPEDWINDOW;

	int width = 640;
	int height = 480;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, false);

	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Title",
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,					// Menu
		m_hInstance,			// Handler
		NULL
	);

	ShowWindow(m_hWnd, SW_SHOW);
}


Window::~Window()
{
	const wchar_t* CLASS_NAME = L"A Window Class";

	UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

