
#include <math.h>
#include "EulerAngles.h"
#include "MathUtil.h"

const EulerAngles kEulerAnglesIdentity(0.0f, 0.0f, 0.0f);

void EulerAngles::canonize()
{
	pitch = wrapPi(pitch);

	if (pitch < -kPiOver2)
	{
		pitch = -kPi - pitch;
		heading += kPi;
		bank += kPi;
	}
	else if (pitch > kPiOver2)
	{
		pitch = kPi - pitch;
		heading += kPi;
		bank += kPi;
	}

	if (fabs(pitch) > kPiOver2 - 1e-4)
	{
		heading += bank;
		bank = 0.0f;
	}
	else
	{
		bank = wrapPi(bank);
	}

	heading = wrapPi(heading);
}

void EulerAngles::fromObjectToInertialQuaternion(const Quaternion& q)
{

}

void EulerAngles::fromInertialToObjectQuaternion(const Quaternion& q)
{

}

void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3& m)
{

}

void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3& m)
{

}

void EulerAngles::fromRotationMatrix(const RotationMatrix& m)
{

}
