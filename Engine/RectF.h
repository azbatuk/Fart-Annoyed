#pragma once

#include "Vec2.h"

class RectF
{
public:
	RectF(float left_in, float top_in, float right_in, float bottom_in);
	RectF(const Vec2& topLeft, const Vec2& bottomRight);
	RectF(const Vec2& topLeft, float width_in, float height_in);
	bool isRectOverlapping(const RectF& other) const;
public:
	float left;
	float top;
	float right;
	float bottom;
};