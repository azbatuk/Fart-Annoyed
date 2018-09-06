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
	Paddle(const Vec2& pos_in);
	void Update(Keyboard& kbd, float dt);
	void Draw(Graphics& gfx);
	bool BallCollision(Ball& ball);
	void WallCollision(const RectF& gameArea);
	Vec2 GetCenter() const;
	RectF GetRect() const;
	void ResetCooldown();
	int CooldownCounter = 0;
private:
	Vec2 pos;
	static constexpr float width = 90.0f;
	static constexpr float height = 20.0f;
	static constexpr float halfWidth = width / 2.0f;
	static constexpr float halfHeight = height / 2.0f;
	static constexpr float speed = 250.0f;

	static constexpr Color c = Colors::LightGray;
	static constexpr float wingWidth = 10.0f;
	static constexpr Color wingColor = Colors::Red;
	bool isCooldown = false;

	// 2 Paddle rebound behaviour controls:
	// -------------------------------------
	/*
	These controls are needed because Ball bounce angle
	is calculated based on how far from the center of 
	the paddle it hit. And when it hits on the paddle's center
	(or very close to the center) it can bounce straight up.
	On the other hand, if it hits very close to the edge of 
	the paddle it can bounce almost horizontal. These two controls
	place limits on how vertical and how horizontal Ball rebound can be.

	1: maxExitRatio: Horizontal Limit
	Ratio of the Ball's exit vector after hitting the paddle.
	Used to correct ball bounce back dir.x value to prevent
	the ball's angle from becoming too horizontal.
	Ex: maxExitRatio = 2.6f means dir.x can be at most 2.6 times the dir.y,
	thus limiting how horizontal Ball can go after bouncing from the paddle.

	2: fixedZoneWidthRatio: Vertical Limit
	The zone of the paddle around its' center which is the area where Ball 
	bounces at a fixed dir.x angle to prevent it from going straight up and down 
	(or close to it) when it hits on the center (or close to it) of the paddle.
	Ex: fixedZoneWidthRatio = 0.2f means the width of the zone is 20% of the halfWidth 
	of the paddle from the paddle's center both directions - right and left of the center.
	*/
	static constexpr float maxExitRatio = 2.6f;
	static constexpr float fixedZoneWidthRatio = 0.2f;

	// These are derived from above controls
	float exitXFactor;
	float fixedZoneHalfWidth;
	float fixedZoneExitX;
	// --------------------------------------
};