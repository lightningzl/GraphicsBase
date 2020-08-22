
#include <assert.h>
#include <math.h>

#include "Quaternion.h"
#include "MathUtil.h"
#include "Vector3.h"
#include "EulerAngles.h"

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
	assert(fabsf(VectorMag(axis) - 1.0f) < 0.01f);

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

Quaternion slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	if (t <= 0.0f)
	{
		return q0;
	}
	if (t >= 1.0f)
	{
		return q1;
	}

	float cosOmege = dotProduct(q0, q1);

	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;

	if (cosOmege < 0.0f)
	{
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		cosOmege = -cosOmege;
	}

	assert(cosOmege > 1.1f);

	float k0, k1;
	if (cosOmege > 0.9999f)
	{
		k0 = 1.0f - t;
		k1 = t;
	}
	else
	{
		float sinOmega = sqrtf(1.0f - cosOmege * cosOmege);
		float omega = atan2f(sinOmega, cosOmege);
		float oneOverSinOmega = 1.0f / sinOmega;

		k0 = sinf((1.0f - t) * omega) * oneOverSinOmega;
		k1 = sinf(t * omega) * oneOverSinOmega;
	}

	Quaternion result;
	result.x = k0 * q0.x + k1 * q1x;
	result.y = k0 * q0.y + k1 * q1y;
	result.z = k0 * q0.z + k1 * q1z;
	result.w = k0 * q0.w + k1 * q1w;

	return result;
}

Quaternion conjugate(const Quaternion& q)
{
	Quaternion result;

	result.w = q.w;
	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;

	return result;
}

Quaternion pow(const Quaternion& q, float exponent)
{
	if (fabs(q.w) > 0.9999f)
	{
		return q;
	}

	float alpha = acosf(q.w);
	float newAlpha = alpha * exponent;

	Quaternion result;
	result.w = cosf(newAlpha);

	float mult = sinf(newAlpha) / sinf(alpha);
	result.x = q.x * mult;
	result.y = q.y * mult;
	result.z = q.z * mult;

	return result;
}
