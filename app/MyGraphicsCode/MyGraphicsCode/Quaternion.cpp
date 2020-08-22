
#include <assert.h>
#include <math.h>

#include "Quaternion.h"
#include "MathUtil.h"

const Quaternion kQuaternionIdentity = { 1.0f, 0.0f, 0.0f, 0.0f };

void Quaternion::setToRotateAboutX(float theta)
{
	float thetaOver2 = theta * 0.5f;

	w = cosf(thetaOver2);
	x = sinf(thetaOver2);
	y = 0.0f;
	z = 0.0f;
}

void Quaternion::setToRotateAboutY(float theta)
{
	float thetaOver2 = theta * 0.5f;

	w = cosf(thetaOver2);
	x = 0.0f;
	y = sinf(thetaOver2);
	z = 0.0f;
}

void Quaternion::setToRotateAboutZ(float theta)
{
	float thetaOver2 = theta * 0.5f;

	w = cosf(thetaOver2);
	x = 0.0f;
	y = 0.0f;
	z = sinf(thetaOver2);
}

void Quaternion::setToRotateAboutAxis(const Vector3& axis, float theta)
{
	assert(fabs(VectorMag(axis) - 1.0f) < 0.01f);

	float thetaOver2 = theta * 0.5f;
	float sinThetaOver2 = sinf(thetaOver2);

	w = cosf(thetaOver2);
	x = axis.x * sinThetaOver2;
	y = axis.y * sinThetaOver2;
	z = axis.z * sinThetaOver2;
}

void Quaternion::setToRotateObjectToInertial(const EulerAngles& orientation)
{
	float sp, sb, sh;
	float cp, cb, ch;
	sinCos(&sp, &cp, orientation.pitch * 0.5f);
	sinCos(&sb, &cb, orientation.bank * 0.5f);
	sinCos(&sh, &ch, orientation.heading * 0.5f);

	w = ch * cp * cb + sh * sp * sb;
	x = ch * sp * cb + sh * cp * sb;
	y = -ch * sp * sb + sh * cp * cp;
	z = -sh * sp * cb + ch * cp * sb;
}

void Quaternion::setToRotateInertialToObject(const EulerAngles& orientation)
{
	float sp, sb, sh;
	float cp, cb, ch;
	sinCos(&sp, &cp, orientation.pitch * 0.5f);
	sinCos(&sb, &cb, orientation.bank * 0.5f);
	sinCos(&sh, &ch, orientation.heading * 0.5f);

	w = ch * cp * cb + sh * sp * sb;
	x = -ch * sp * cb - sh * cp * sb;
	y = ch * sp * sb - sh * cp * cp;
	z = sh * sp * cb - ch * cp * sb;
}

Quaternion Quaternion::operator*(const Quaternion& a) const
{
	Quaternion result;

	result.w = w * a.w - x * a.x - y * a.y - z * a.z;
	result.x = w * a.x + x * a.w + z * a.y - y * a.z;
	result.y = w * a.y + y * a.w + x * a.z - z * a.x;
	result.z = w * a.z + z * a.w + y * a.x - x * a.y;
	
	return result;
}

Quaternion& Quaternion::operator*=(const Quaternion& a)
{
	*this = *this * a;
	return *this;
}

void Quaternion::normalize()
{
	float mag = (float)sqrtf(w * w + x * x + y * y + z * z);

	if (mag > 0.0f)
	{
		float oneOverMag = 1.0f / mag;
		w *= oneOverMag;
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
	else
	{
		assert(false);
		identity();
	}
}

float Quaternion::getRotationAngle() const
{
	float thetaOver2 = safeAcos(w);
	return thetaOver2 * 2.0f;
}

Vector3 Quaternion::getRotationAxis() const
{
	float sinThetaOver2Sq = 1.0f - w * w;

	if (sinThetaOver2Sq <= 0.0f)
	{
		return Vector3(1.0f, 0.0f, 0.0f);
	}

	float oneOverSinThetaOver2 = 1.0f / sqrtf(sinThetaOver2Sq);
	return Vector3(x * oneOverSinThetaOver2, y * oneOverSinThetaOver2, z * oneOverSinThetaOver2);
}

float dotProduct(const Quaternion& a, const Quaternion& b)
{
	return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}

Quaternion slerp(const Quaternion& p, const Quaternion& q, float t)
{

}

Quaternion conjugate(const Quaternion& q)
{

}

Quaternion pow(const Quaternion& q, float exponent)
{

}
