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
	virtual void update() = 0;
	virtual void useProjection(GLuint shaderProgram) = 0;
	virtual void useView(GLuint shaderProgram) = 0;
	virtual void update(GLuint shaderProgram) = 0;
};

