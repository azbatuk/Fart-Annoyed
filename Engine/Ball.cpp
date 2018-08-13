#include "Ball.h"
#include "Graphics.h"

Ball::Ball(Vec2 & pos_in, Vec2 & vel_in)
	:
	pos(pos_in),
	vel(vel_in)
{
}

void Ball::Update(float speed, const RectF& walls)
{
	pos += vel * speed;

	if (pos.x < walls.left)
	{
		vel.x = -vel.x;
		pos.x = walls.left;
	}
	else if (pos.x >= walls.right - diameter)
	{
		vel.x = -vel.x;
		pos.x = float(walls.right - diameter);
	}
	else if (pos.y < 0)
	{
		vel.y = -vel.y;
		pos.y = 0;
	}
	else if (pos.y >= Graphics::ScreenHeight - diameter)
	{
		vel.y = -vel.y;
		pos.y = float(Graphics::ScreenHeight - diameter);
	}
}

Vec2 Ball::GetPos() const
{
	return pos;
}

Vec2 Ball::GetVel() const
{
	return vel;
}

int Ball::GetDiameter() const
{
	return diameter;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	if (vel.y < 0) {
		vel.y = -vel.y;
	}
}
