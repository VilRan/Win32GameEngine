#include "IApplication.h"

IApplication::IApplication()
{
}

IApplication::~IApplication()
{
}

bool IApplication::Create()
{
	m_Window = MakeWindow(1024, 768, L"GAME-ENGINE");
	if (m_Window)
	{
		::SetWindowLongPtr(m_Window, 0, (LONG)this);
		return true;
	}
	else
	{
		return false;
	}
}

void IApplication::Run()
{
	// run the app
	MSG msg;
	BOOL gotMsg = false;
	HWND window = m_Window;

	// get the first message
	::PeekMessage(&msg, window, 0, 0, PM_NOREMOVE);

	while (msg.message != WM_QUIT)
	{
		gotMsg = ::GetMessage(&msg, window, 0, 0);
		if (gotMsg)
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
}

bool IApplication::OnEvent(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return true;
}

HWND IApplication::MakeWindow(int iWidth, int iHeight, const wchar_t* pTitle)
{
	HINSTANCE hInst = ::GetModuleHandle(NULL);
	DWORD windowStyle = 0;
	windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInst;
	wc.hIcon = ::LoadIcon(hInst, 0);
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) ::GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = L"GAMEENGINE_WNDCLASS";
	wc.cbClsExtra = sizeof(void*);

	if (! ::RegisterClass(&wc))
	{
		return NULL;
	}

	// create the window
	HWND window = ::CreateWindow(wc.lpszClassName, pTitle, windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, iWidth, iHeight, NULL, NULL, hInst, NULL);
	if (!window)
	{
		::OutputDebugString(L"Failed to create window, exiting...");
		return NULL;
	}
	
	::SetWindowLong(window, GWL_STYLE, windowStyle);
	RECT clientArea = { 0, 0, iWidth, iHeight };
	::AdjustWindowRectEx(&clientArea, windowStyle, FALSE, 0);
	::SetWindowPos(window, NULL, 0, 0, iWidth, iHeight, SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW);
	::UpdateWindow(window);
	::ShowWindow(window, SW_SHOWNORMAL);

	return window;
}

long WINAPI IApplication::WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	bool callDefWndProc = false;
	IApplication* pApp = (IApplication*) ::GetWindowLong(hwnd, 0);
	if (pApp)
	{
		callDefWndProc = pApp->OnEvent(iMessage, wParam, lParam);
	}
	else
	{
		switch (iMessage)
		{
		case WM_DESTROY:
			::PostQuitMessage(0);
			break;

		case WM_CREATE:
			::SetForegroundWindow(hwnd);
			break;

		default:
			break;
		}
	}

	if (callDefWndProc)
	{
		return (long)::DefWindowProc(hwnd, iMessage, wParam, lParam);
	}
	else
	{
		return 0;
	}
}
