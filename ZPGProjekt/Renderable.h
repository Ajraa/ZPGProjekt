#pragma once
class Renderable
{
	virtual void createVAO() = 0;
	virtual void createVBO() = 0;
	virtual void drawArrays() = 0;
};

