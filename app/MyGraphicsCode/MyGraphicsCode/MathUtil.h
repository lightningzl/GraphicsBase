#pragma once

#include <math.h>
#include "Vector3.h"

const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float klOverPi = 1.0f / kPi;
const float klOver2Pi = 1.0f / k2Pi;
const Vector3 kZeroVector(0.0f, 0.0f, 0.0f);

extern float wrapPi(float theta);
extern float safeAcos(float x);

inline void sinCos(float * returnSin, float *returnCos, float theta)
{
	*returnSin = sinf(theta);
	*returnCos = cosf(theta);
}