#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"

class Brick
{
public:
	Brick() = default;
	//Brick() : rect(0.f, 0.f, 0.f, 0.f), c(Colors::Magenta) {}
	Brick(const RectF& rect_in, Color c_in);
	void Draw(Graphics& gfx) const;
private:
	RectF rect;
	Color c;
	bool isDestroyed = false;
};