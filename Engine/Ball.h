#pragma once

#include "Vec2.h"
#include "RectF.h"

class Ball
{
public:
	Ball() = default;
	Ball(const Vec2& pos_in, const Vec2 & dir_in);
	void Update(float speed);
	// return: 0=none 1=hit wall 2=hit bottom
	int WallCollision(const RectF& gameArea);
	int GetDiameter() const;
	Vec2 GetPos() const;
	Vec2 GetVel() const;
	Vec2 GetCenter() const;
	void ReboundX();
	void ReboundY();
	void SetDirection(const Vec2& dir);
private:
	Vec2 pos;
	Vec2 vel;
	static constexpr int diameter = 14;
	static constexpr float ballSpeed = 400.0f;
};