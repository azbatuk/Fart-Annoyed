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
}

bool Ball::WallCollision(const RectF & gameArea)
{
	if (pos.x < gameArea.left)
	{
		vel.x = -vel.x;
		pos.x = gameArea.left;
		return true;
	}
	else if (pos.x >= gameArea.right - diameter)
	{
		vel.x = -vel.x;
		pos.x = float(gameArea.right - diameter);
		return true;
	}
	else if (pos.y < 0)
	{
		vel.y = -vel.y;
		pos.y = 0;
		return true;
	}
	else if (pos.y >= Graphics::ScreenHeight - diameter)
	{
		vel.y = -vel.y;
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

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}
