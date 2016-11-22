#include "stdafx.h"
#include "utils.h"


namespace MY_UTIL
{
	//�Ÿ� ���ϴ� �Լ�
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//���� ���ϴ� �Լ�
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