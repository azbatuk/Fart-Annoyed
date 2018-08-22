#include "Ball.h"
#include "Graphics.h"

Ball::Ball(Vec2 & pos_in, Vec2 & vel_in)
	:
	pos(pos_in),
	vel(vel_in)
{
}

void Ball::Update(float dt)
{
	pos += vel * ballSpeed * dt;
}

bool Ball::WallCollision(const RectF & gameArea)
{
	if (pos.x < gameArea.left)
	{
		ReboundX();
		pos.x = gameArea.left;
		return true;
	}
	else if (pos.x >= gameArea.right - diameter)
	{
		ReboundX();
		pos.x = float(gameArea.right - diameter);
		return true;
	}
	else if (pos.y <= gameArea.top)
	{
		ReboundY();
		pos.y = gameArea.top;
		return true;
	}
	else if (pos.y >= Graphics::ScreenHeight - diameter)
	{
		ReboundY();
		pos.y = float(Graphics::ScreenHeight - diameter);
		return true;
	}

	return false;
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

Vec2 Ball::GetCenter() const
{
	const int radius = diameter / 2;
	return Vec2(pos.x + radius, pos.y + radius);
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

void Ball::NewRound(Vec2& pos_in, Vec2& vel_in)
{
	pos = pos_in;
	vel = vel_in;
}
