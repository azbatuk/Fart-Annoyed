#include "Brick.h"

Brick::Brick(const RectF& rect_in, Color c_in)
	:
	rect(rect_in),
	c(c_in)
{
}

void Brick::Draw(Graphics & gfx) const
{
	if (!isDestroyed)
	{
		gfx.DrawRect(rect.GetExpanded(-padding), c);
	}
}

bool Brick::BallCollision(Ball& ball)
{
	const int ballLeft = int(ball.GetPos().x);
	const int ballTop = int(ball.GetPos().y);
	const int ballRight = int(ball.GetPos().x + ball.GetDiameter());
	const int ballBottom = int(ball.GetPos().y + ball.GetDiameter());

	if (!isDestroyed && 
		ballLeft	< rect.right &&
		ballRight	> rect.left &&
		ballTop		< rect.bottom &&
		ballBottom	> rect.top)
	{
		isDestroyed = true;
		if (ball.GetVel().y < 0) {
			ball.ReboundY();
		}
		return true;
	}
	return false;
}
