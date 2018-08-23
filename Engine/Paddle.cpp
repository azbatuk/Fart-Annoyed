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
			// check if ball is hitting top or sides of the paddle
			// and Rebound accordingly.
			else
			{
				if (ballCenter.x >= pos.x && ballCenter.x <= pos.x + width)
				{
					// Ball hit the top of the paddle
					ball.ReboundY();

					// This condition also means Ball hit the side of the paddle same as the side it is approaching from:

					// - First : Adjust the bounce angle based on how far from the paddle's center the ball hit
					const float ballX_to_paddleX = ballCenter.x - paddleCenter.x;
					float ballVelX_modifier = 0.0f;
					if (ballX_to_paddleX > 20 && ballX_to_paddleX < 35)
					{
						ballVelX_modifier = 0.5f;
					}
					else if (ballX_to_paddleX > 35)
					{
						ballVelX_modifier = 1.0f;
					}
					else if (ballX_to_paddleX < -20 && ballX_to_paddleX > -35)
					{
						ballVelX_modifier = -0.5f;
					}
					else if (ballX_to_paddleX < -35)
					{
						ballVelX_modifier = -1.0f;
					}

					// - Second: Ball coming from left and hitting the top-left of the paddle or coming from right and hitting top-right,
					// then bounce it back to that side.
					ball.ReboundX();

					// calculate and set new Vel.x for Ball
					float ballVelX_out = (ball.GetVel().x > 0) ? 1 : -1;
					ballVelX_out += ballVelX_modifier;
					ball.SetVel(Vec2(ballVelX_out, ball.GetVel().y));
				}
				else
				{
					// Ball hit left of right vertical side of the paddle, send it to bottom to end the game.
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
