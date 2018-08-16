#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
public:
	Brick() = default;
	//Brick() : rect(0.f, 0.f, 0.f, 0.f), c(Colors::Magenta) {}
	Brick(const RectF& rect_in, Color c_in);
	void Draw(Graphics& gfx) const;
	bool BallCollision(Ball& ball);
	Vec2 GetCenter() const;
	void SetDestroyed(const bool isDestroyed_in);
private:
	RectF rect;
	Color c;
	bool isDestroyed = false;
	static constexpr float padding = 1.0f;
};