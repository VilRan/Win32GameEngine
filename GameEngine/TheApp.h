#pragma once
#include "IApplication.h"
class CTheApp :
	public IApplication
{
public:
	CTheApp();
	virtual ~CTheApp();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void OnUpdate(float fFrameTime);
	virtual void OnDraw();
};

