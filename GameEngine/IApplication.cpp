#include "IApplication.h"

// include all your renderers
#include "OpenGLRenderer.h"

IApplication* IApplication::m_pApp = NULL;

IApplication::IApplication()
{
	m_pApp = this;
	m_Window = NULL;
	m_bActive = false;
	m_Timer.Create();
	m_pRenderer = NULL;
}

IApplication::~IApplication()
{
	m_pApp = NULL;
}

bool IApplication::Create()
{
	m_Window = MakeWindow(1024, 720, L"GAME-ENGINE");
	if (m_Window)
	{
		::SetWindowLong(m_Window, GWL_USERDATA, (LONG)this);

		// create the renderer
		m_pRenderer = new COpenGLRenderer;
		if (!m_pRenderer->Create())
		{
			return false;
		}

		// call pure virtual OnCreate
		if (OnCreate())
		{
			SetActive(true);
			return true;
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
}


bool IApplication::OnEvent(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_SETFOCUS:
		//SetActive(true);
		break;
	case WM_KILLFOCUS:
		//SetActive(false);
		break;
	case WM_ACTIVATEAPP:

		break;
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
		{
			SetActive(false);
		}
		else if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)
		{
			SetActive(true);
		}
		break;
	default:
		break;
	}
	return false;
}


void IApplication::Run()
{
	// run the app
	MSG msg;
	BOOL gotMsg = false;
	HWND window = NULL;

	// get the first message
	::PeekMessage(&msg, window, 0, 0, PM_NOREMOVE);

	while (msg.message != WM_QUIT)
	{
		if (IsActive())
		{
			gotMsg = ::PeekMessage(&msg, window, 0, 0, PM_REMOVE);
		}
		else
		{
			gotMsg = ::GetMessage(&msg, window, 0, 0);
		}
		if (gotMsg)
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if (msg.message != WM_QUIT)
		{
			m_Timer.Stop();
			m_Timer.Start();
			OnUpdate(m_Timer.GetElapsedSeconds());
			OnDraw(m_pRenderer);
		}
	}

	OnDestroy();
	SAFE_DELETE(m_pRenderer);
}

void IApplication::SetActive(bool bSet)
{
	m_bActive = bSet;
	m_Timer.Start();
}

HWND IApplication::MakeWindow(int iWidth, int iHeight, const wchar_t* pTitle)
{
	HINSTANCE hInst = ::GetModuleHandle(NULL);
	DWORD windowStyle = 0;

	windowStyle = WS_OVERLAPPED |
		WS_CAPTION |
		WS_SYSMENU |
		WS_THICKFRAME |
		WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX;

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

	if (!::RegisterClass(&wc))
	{
		return NULL;
	}

	// create the window
	HWND window = ::CreateWindow(
		wc.lpszClassName,
		pTitle,
		windowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		iWidth,
		iHeight,
		NULL,
		NULL,
		hInst,
		NULL);

	if (!window)
	{
		::OutputDebugString(L"Failed to create window, exiting...");
		return NULL;
	}

	::SetWindowLong(window, GWL_STYLE, windowStyle);
	RECT clientArea = { 0, 0, iWidth, iHeight };
	::AdjustWindowRectEx(&clientArea, windowStyle, FALSE, 0);
	::SetWindowPos(
		window,
		NULL,
		0,
		0,
		iWidth,
		iHeight,
		SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW);
	::UpdateWindow(window);
	::ShowWindow(window, SW_SHOWNORMAL);

	return window;
}


long WINAPI IApplication::WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
		break;

	case WM_CREATE:
		::SetForegroundWindow(hwnd);
		break;

	case WM_CLOSE:
		::DestroyWindow(hwnd);
		return 0;
		break;

	default:
		break;
	}

	bool callDefWndProc = true;
	IApplication* pApp = (IApplication*)::GetWindowLong(hwnd, GWL_USERDATA);
	if (pApp)
	{
		callDefWndProc = !pApp->OnEvent(iMessage, wParam, lParam);
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


