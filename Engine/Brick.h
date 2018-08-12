#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"

class Brick
{
public:
	Brick() = default;
	Brick(const RectF& rect_in, Color c_in);
	void Draw(Graphics& gfx) const;
private:
	RectF rect;
	Color c;
	bool isDestroyed = false;
};