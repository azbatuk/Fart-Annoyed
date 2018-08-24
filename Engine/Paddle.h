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
	bool BallCollision(Ball& ball);
	void WallCollision(const RectF& gameArea);
	Vec2 GetCenter() const;
	void ResetCooldown();
	int CooldownCounter = 0;
private:
	Vec2 pos;
	static constexpr float width = 90.0f;
	static constexpr float height = 20.0f;
	static constexpr float speed = 200.0f;

	/*
	exitXFactor: 
	Used to correct ball bounce back dir.x value to prevent 
	the ball's angle from becoming too horizontal (extreme in the x direction).
	This is when ball direction is calculated based on where it hit on 
	the paddle and dir.x is adjusted to bounce it back at different angles.
	*/
	float exitXFactor = 0.045f;

	/*
	fixedZoneHalfWidth:
	Prevent ball from bouncing straight up and down
	(or close to it) when it hits on the center (or 
	close to it) of the paddle by usding a fixed dir.x
	angle if ball hit within the fixedZoneHalfWidth value 
	distance from the paddle center.
	*/
	float fixedZoneHalfWidth = 15.0f;

	static constexpr Color c = Colors::LightGray;
	static constexpr float wingWidth = 10.0f;
	static constexpr Color wingColor = Colors::Red;
	bool isCooldown = false;
};