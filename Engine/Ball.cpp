#include "Ball.h"
#include "Graphics.h"

Ball::Ball(Vec2 & pos_in, Vec2 & vel_in)
	:
	pos(pos_in),
	vel(vel_in)
{
}

void Ball::Update(float speed)
{
	pos += vel * speed;

	if (pos.x < 0)
	{
		vel.x = -vel.x;
		pos.x = 0;
	}
	else if (pos.x >= Graphics::ScreenWidth - diameter)
	{
		vel.x = -vel.x;
		pos.x = float(Graphics::ScreenWidth - diameter);
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

void Ball::ReboundY()
{
	if (vel.y < 0) {
		vel.y = -vel.y;
	}
}
