#include "Ball.h"
#include "Graphics.h"

Ball::Ball(const Vec2 & pos_in, const Vec2 & dir_in)
	:
	pos(pos_in)
{
	SetDirection(dir_in);
}

void Ball::Update(float dt)
{
	pos += vel * dt;
}

int Ball::WallCollision(const RectF & gameArea)
{
	if (pos.x < gameArea.left)
	{
		ReboundX();
		pos.x = gameArea.left;
		return 1;
	}
	else if (pos.x >= gameArea.right - diameter)
	{
		ReboundX();
		pos.x = float(gameArea.right - diameter);
		return 1;
	}
	else if (pos.y <= gameArea.top)
	{
		ReboundY();
		pos.y = gameArea.top;
		return 1;
	}
	else if (pos.y >= Graphics::ScreenHeight - diameter)
	{
		// No rebound! Game/Round over!
		return 2;
	}

	return 0;
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

RectF Ball::GetRect() const
{
	return RectF(pos, diameter, diameter);
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

void Ball::SetDirection(const Vec2 & dir_in)
{
	vel = dir_in.GetNormalized() * ballSpeed;
}
