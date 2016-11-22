#pragma once


#include <cmath>

#define PI		3.141592654f
#define PI2		(PI * 2)
#define PI8		float(PI / 8.0f)
#define PI16	float(PI / 16.f)
#define PI32	float(PI / 32.f)
#define PI64	float(PI / 64.f)
#define PI128	float (PI / 128.f)

#define ONE_RAD (PI / 180)


//실수 대소비교하기 위한 변수 (가장 작은 단위라고 보자)
#define FLOAT_EPSILON 0.001f 
#define FLOAT_TO_INT(f1)		static_cast<int>(f1 * FLOAT_EPSILON)
#define FLOAT_EQUAL(f1, f2)		(fabs(f1 - f2) <= FLOAT_EPSILON) //두 실수가 같은지 확인

namespace MY_UTIL
{
	//거리 구하는 함수
	float getDistance(float startX, float startY, float endX, float endY);

	//각도 구하는 함수
	float getAngle(float startX, float startY, float endX, float endY);
}
