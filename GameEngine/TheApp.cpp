#include "TheApp.h"

CTheApp::CTheApp()
{
}

CTheApp::~CTheApp()
{
}

bool CTheApp::OnCreate()
{
	return true;
}

void CTheApp::OnDestroy()
{

}

void CTheApp::OnUpdate(float fFrameTime)
{
	char buffer[256];
	sprintf(buffer, "FPS: %.4f\r\n", 1.0f / fFrameTime);
	::OutputDebugStringA(buffer);

	::Sleep(100);
}

void CTheApp::OnDraw()
{

}
