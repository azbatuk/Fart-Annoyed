#pragma once

#include "Vec2.h"
#include "RectF.h"

class Ball
{
public:
	Ball(Vec2& pos_in, Vec2& vel_in);
	void Update(float speed);
	// return: 0=none 1=hit wall 2=hit bottom
	int WallCollision(const RectF& gameArea);
	Vec2 GetPos() const;
	Vec2 GetVel() const;
	int GetDiameter() const;
	Vec2 GetCenter() const;
	void ReboundX();
	void ReboundY();
	void NewRound(Vec2& pos_in, Vec2& vel_in);
	void SetVel(Vec2& vel_in);
private:
	const float posX = 300.0f;
	const float posY = 300.0f;
	const float velX = -1.0f;
	const float velY = -1.0f;
	Vec2 pos;
	Vec2 vel;
	static constexpr int diameter = 14;
	static constexpr float ballSpeed = 250.0f;
};