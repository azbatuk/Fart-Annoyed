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
		const Vec2 ballCenter = ball.GetCenter();
		const Vec2 brickCenter = GetCenter();

		// If ball's X velocity and the value from the difference between 
		// X values of ball and brick positions are both pointing the same 
		// velocity direction (both numbers are negative or positive) 
		// then ball can only rebound on the Y axis due to the angle it is 
		// approaching - hitting the brick approacing from inside, 
		// no need to check if it is hitting the side of the brick or not.
		if ( std::signbit( ball.GetVel().x ) == std::signbit( (ballCenter - brickCenter).x ) )
		{
			ball.ReboundY();
		}
		// Otherwise - hitting the brick approacing from outside, 
		// check if ball is hitting top/bottom or sides of the brick
		// and Rebound accordingly.
		else
		{
			if (ballCenter.x >= rect.left && ballCenter.x <= rect.right)
			{
				// ball hit top or bottom of brick
				ball.ReboundY();
			}
			else
			{
				// ball hit left or right side of brick
				ball.ReboundX();
			}
		}
		return true;
	}
	return false;
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}

void Brick::SetDestroyed(const bool isDestroyed_in)
{
	isDestroyed = isDestroyed_in;
}
