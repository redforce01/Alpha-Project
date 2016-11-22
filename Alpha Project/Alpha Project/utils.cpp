#include "stdafx.h"
#include "utils.h"


namespace MY_UTIL
{
	//거리 구하는 함수
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//각도 구하는 함수
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		float distance = sqrtf( x * x + y * y );
		float angle = acosf(x / distance);

		if (y > 0) angle = PI2 - angle;

		return angle;
	}
}