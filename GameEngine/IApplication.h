#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include "Timer.h"
#include "IRenderer.h"

#define SAFE_DELETE(x) if (x) { delete(x); (x) = NULL; }

class IApplication
{
public:
	IApplication();
	virtual ~IApplication();

	bool Create();
	void Run();
	
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void OnUpdate(float fFrameTime) = 0;
	virtual void OnDraw(IRenderer* pRenderer) = 0;

	inline bool IsActive() const { return m_bActive; }
	void SetActive(bool bSet);

	inline float GetFrameTime() const { return m_Timer.GetElapsedSeconds(); }
	inline IRenderer* GetRenderer() { return m_pRenderer; }
	inline HWND GetWindow() { return m_Window; }

	static IApplication* GetApp() { return m_pApp; }

protected:
	virtual bool OnEvent(UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	static HWND MakeWindow(int iWidth, int iHeight, const wchar_t* pTitle);
	static long WINAPI WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	static IApplication* m_pApp;

	HWND m_Window;
	bool m_bActive;
	Timer m_Timer;

	IRenderer* m_pRenderer;
};

