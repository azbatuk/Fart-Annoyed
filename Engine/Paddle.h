#pragma once

#include "RectF.h"
#include "Keyboard.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Paddle
{
public:
	Paddle(Vec2& pos_in);
	void Update(Keyboard& kbd, float dt, const RectF& walls);
	void Draw(Graphics& gfx);
	bool BallCollision(const Ball& ball);
private:
	Vec2 pos;
	static constexpr float width = 90.0f;
	static constexpr float height = 20.0f;
	static constexpr float speed = 200.0f;
	static constexpr Color c = Colors::LightGray;
};