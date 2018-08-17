#include "Paddle.h"

Paddle::Paddle(Vec2& pos_in)
	:
	pos(pos_in)
{
}

void Paddle::Update(Keyboard& kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= dt * speed;
	}

	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += dt * speed;
	}
}

void Paddle::Draw(Graphics & gfx)
{
	gfx.DrawRect(int(pos.x), int(pos.y), int(pos.x + width), int(pos.y + height), wingColor);
	gfx.DrawRect(int(pos.x + wingWidth), int(pos.y), int(pos.x + width - wingWidth), int(pos.y + height), c);
}

bool Paddle::BallCollision(Ball & ball)
{
	if (!isCooldown) {
		const float ballLeft = ball.GetPos().x;
		const float ballRight = ball.GetPos().x + ball.GetDiameter();
		const float ballTop = ball.GetPos().y;
		const float ballBottom = ball.GetPos().y + ball.GetDiameter();

		if (ballLeft	< pos.x + width &&
			ballRight	> pos.x &&
			ballTop		< pos.y + height &&
			ballBottom	> pos.y)
		{

			const Vec2 ballCenter = ball.GetCenter();
			const Vec2 paddleCenter = GetCenter();

			// If ball's X velocity and the value from the difference between 
			// X values of ball and paddle positions are both pointing the same 
			// velocity direction (both numbers are negative or positive) 
			// then ball can only rebound on the Y axis due to the angle it is 
			// approaching - hitting the paddle approacing from inside, 
			// no need to check if it is hitting the side of the paddle or not.
			if (std::signbit(ball.GetVel().x) == std::signbit((ballCenter - paddleCenter).x))
			{
				ball.ReboundY();
			}
			// Otherwise - hitting the paddle approacing from outside, 
			// check if ball is hitting top/bottom or sides of the paddle
			// and Rebound accordingly.
			else
			{
				if (ballCenter.x >= pos.x && ballCenter.x <= pos.x + width)
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
			isCooldown = true;
			return true;
		}
	}
	return false;
}

void Paddle::WallCollision(const RectF & gameArea)
{
	if (pos.x < gameArea.left)
	{
		pos.x = gameArea.left;
	}
	else if (pos.x + width > gameArea.right)
	{
		pos.x = gameArea.right - width;
	}
}

Vec2 Paddle::GetCenter() const
{
	return Vec2(pos.x + width / 2, pos.y + height / 2);
}

void Paddle::ResetCooldown()
{
	isCooldown = false;
}
