#pragma once
class Renderable
{
public:
	virtual void createVAO() = 0;
	virtual void createVBO() = 0;
	virtual void drawArrays() = 0;
	virtual int getTextureId() = 0;
};

