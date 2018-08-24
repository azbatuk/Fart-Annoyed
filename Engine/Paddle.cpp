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

			/*
			1st condition: 
			If ball's X velocity and the value from the difference between 
			X values of ball and paddle positions are both pointing the same 
			velocity direction (both numbers are negative or positive) 
			then ball can only rebound on the Y axis due to the angle it is 
			approaching - hitting the paddle approaching from inside.
			OR
			2nd condition: 
			If ball is hitting top of the paddle after approaching from outside
			*/
			if (std::signbit(ball.GetVel().x) == std::signbit((ballCenter - paddleCenter).x) ||
				(ballCenter.x >= pos.x && ballCenter.x <= pos.x + width))
			{
				Vec2 dir;
				const float xDifference = ballCenter.x - paddleCenter.x;
				const float fixedXComponent = fixedZoneHalfWidth * exitXFactor;

				/* if ball hit within fixedZoneHalfWidth distance
				of paddle center, then use a fixed angle to bounce it back
				to prevent too vertical bounce backs. */
				if (std::abs(xDifference) < fixedZoneHalfWidth)
				{
					// ball hit left of paddle center
					if (xDifference < 0.0f)
					{
						dir = Vec2(-fixedXComponent, -1.0f);
					}
					// ball hit right of paddle center
					else
					{
						dir = Vec2(fixedXComponent, -1.0f);
					}
				}
				// ball hit outside the fixed zone around paddle center
				else
				{
					dir = Vec2(xDifference * exitXFactor, -1.0f);
				}
		
				ball.SetDirection(dir);
			}
			else
			{
				// Ball hit left of right vertical side of the paddle, so send it to bottom to end the game.
				ball.ReboundX();
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
