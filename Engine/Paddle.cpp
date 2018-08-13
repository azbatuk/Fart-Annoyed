#include "Paddle.h"

Paddle::Paddle(Vec2& pos_in)
	:
	pos(pos_in)
{
}

void Paddle::Update(Keyboard& kbd, float dt, const RectF& gameArea)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= dt * speed;
		if (pos.x < gameArea.left)
		{ 
			pos.x = gameArea.left;
		}
	}

	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += dt * speed;
		if (pos.x + width > gameArea.right)
		{
			pos.x = gameArea.right - width;
		}
	}
}

void Paddle::Draw(Graphics & gfx)
{
	gfx.DrawRect(int(pos.x), int(pos.y), int(pos.x + width), int(pos.y + height), c);
}

bool Paddle::BallCollision(const Ball & ball)
{
	const float ballLeft = ball.GetPos().x;
	const float ballRight = ball.GetPos().x + ball.GetDiameter();
	const float ballTop = ball.GetPos().y;
	const float ballBottom = ball.GetPos().y + ball.GetDiameter();

	if (ballLeft	< pos.x + width &&
		ballRight	> pos.x &&
		ballTop		< pos.y + height &&
		ballBottom	> pos.y)
	{
		return true;
	}
	return false;
}
