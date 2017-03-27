#pragma once
class IRenderer
{
public:
	IRenderer();
	virtual ~IRenderer();

	virtual bool Create() = 0;

protected:
	HDC m_Context;
	HGLRC m_hRC;
};

