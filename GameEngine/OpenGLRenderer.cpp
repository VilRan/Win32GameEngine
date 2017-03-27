#include "OpenGLRenderer.h"



COpenGLRenderer::COpenGLRenderer()
{
	m_Context = NULL;
	m_hRC = NULL;
}


COpenGLRenderer::~COpenGLRenderer()
{
}

bool COpenGLRenderer::Create()
{
	int flags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DEPTH_DONTCARE;

	PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR), 
		1, 
		(DWORD)flags, 
		PFD_TYPE_RGBA, 
		32, 
		0, 0, 0, 0, 0, 0,
		0, 
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		PFD_MAIN_PLANE,
		0, 0, 0, 0
	};

	m_Context = ::GetDC(IApplication::GetApp()->GetWindow());

	int pixelFormat = ::ChoosePixelFormat(m_Context, &pfd);
	if (pixelFormat == 0)
	{

		return false;
	}

	if (!::SetPixelFormat(m_Context, pixelFormat, &pfd))
	{
		return false;
	}

	return true;
}
