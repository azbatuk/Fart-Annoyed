#pragma once

#include "Vec2.h"

class Ball
{
public:
	Ball(Vec2& pos_in, Vec2& vel_in);
	void Update(float speed);
	Vec2 GetPos() const;
	Vec2 GetVel() const;
	int GetDiameter() const;
	void ReboundY();
private:
	Vec2 pos;
	Vec2 vel;
	static constexpr int diameter = 14;
};