/**
 * main.cpp
 * entry point for a superduper game engine
 */


#include "IApplication.h"

int APIENTRY WinMain(HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR pCmdLine,
	int nCmdShow)
{
	IApplication* pApp = new IApplication;
	if (!pApp->Create())
	{
		::MessageBox(NULL, L"APP START FAILED", L"ERROR", MB_OK);
		return 0;
	}

	pApp->Run();
	delete pApp;
	return 0;
}

