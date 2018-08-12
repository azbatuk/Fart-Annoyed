#include "Brick.h"

Brick::Brick(const RectF& rect_in, Color c_in)
	:
	rect(rect_in),
	c(c_in)
{
}

void Brick::Draw(Graphics & gfx) const
{
	gfx.DrawRect(rect, c);
}
