#pragma once
#include "IRenderer.h"
#include "IApplication.h"
#include <gl/GL.h>

class COpenGLRenderer :
	public IRenderer
{
public:
	COpenGLRenderer();
	virtual ~COpenGLRenderer();

	virtual bool Create();
};

