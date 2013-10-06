#pragma once
class Drawable
{
public:
	virtual void draw3d() = 0;
	virtual void draw2d() = 0;
	virtual ~Drawable(void)
	{
	}
};

