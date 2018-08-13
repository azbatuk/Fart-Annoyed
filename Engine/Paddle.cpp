#include "Paddle.h"

Paddle::Paddle(Vec2& pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfHeight_in),
	halfHeight(halfHeight_in)
{
}

void Paddle::Update(Keyboard& kbd, float dt, const RectF& walls)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{

	}
}

void Paddle::Draw(Graphics & gfx)
{
}
