#pragma once
#include "CameraObserver.h"

class CameraObserver;
class CameraSubject
{
public:
	virtual void attach(CameraObserver* observer) = 0;
	virtual void detach(CameraObserver* observer) = 0;
	virtual void useProjection() = 0;
	virtual void useView() = 0;
};

