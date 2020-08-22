#include "MathUtil.h"

float wrapPi(float theta)
{
	theta += kPi;
	theta -= floorf(theta * klOver2Pi) * k2Pi;
	theta -= kPi;
	return theta;
}

float safeAcos(float x)
{
	if (x <= -1.0f)
	{
		return kPi;
	}

	if (x >= 1.0f)
	{
		return 0.0f;
	}

	return acos(x);
}
