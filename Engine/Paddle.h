#pragma once

#include "RectF.h"
#include "Keyboard.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"
#include "Vec2.h"

class Paddle
{
public:
	Paddle(Vec2& pos_in);
	void Update(Keyboard& kbd, float dt);
	void Draw(Graphics& gfx);
	bool BallCollision(Ball& ball) const;
	void WallCollision(const RectF& gameArea);
private:
	Vec2 pos;
	static constexpr float width = 90.0f;
	static constexpr float height = 20.0f;
	static constexpr float speed = 200.0f;
	static constexpr Color c = Colors::LightGray;
	static constexpr float wingWidth = 10.0f;
	static constexpr Color wingColor = Colors::Red;
};