/**
 * main.cpp
 * entry point for a superduper game engine
 */


#include "TheApp.h"

int APIENTRY WinMain(HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR pCmdLine,
	int nCmdShow)
{
	CTheApp* pApp = new CTheApp;
	if (!pApp->Create())
	{
		::MessageBox(NULL, L"APP START FAILED", L"ERROR", MB_OK);
		return 0;
	}

	pApp->Run();
	delete pApp;
	return 0;
}

