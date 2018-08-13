#pragma once

#include "RectF.h"
#include "Keyboard.h"
#include "Colors.h"
#include "Graphics.h"

class Paddle
{
public:
	Paddle(Vec2& pos_in, float halfWidth_in, float halfHeight_in);
	void Update(Keyboard& kbd, float dt, const RectF& walls);
	void Draw(Graphics& gfx);
private:
	Vec2 pos;
	float halfWidth;
	float halfHeight;
	static constexpr Color c = Colors::LightGray;
};