#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class IApplication
{
public:
	IApplication();
	virtual ~IApplication();

	bool Create();
	void Run();

protected:
	virtual bool OnEvent(UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	static HWND MakeWindow(int iWidth, int iHeight, const wchar_t* pTitle);
	static long WINAPI WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	HWND m_Window;
};

