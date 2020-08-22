#pragma once

#include "Vector3.h"
#include "EulerAngles.h"

class Quaternion
{
public:
	float x, y, z, w;
	void identity() 
	{
		x = y = z = 0.0f;
		w = 1.0f;
	}

	void setToRotateAboutX(float theta);
	void setToRotateAboutY(float theta);
	void setToRotateAboutZ(float theta);
	void setToRotateAboutAxis(const Vector3& axis, float theta);
	void setToRotateObjectToInertial(const EulerAngles& orientation);
	void setToRotateInertialToObject(const EulerAngles& orientation);

	Quaternion operator*(const Quaternion& a) const;
	Quaternion& operator*=(const Quaternion& a);

	void normalize();
	float getRotationAngle() const;
	Vector3 getRotationAxis() const;
};

extern const Quaternion kQuaternionIdentity;

extern float dotProduct(const Quaternion& a, const Quaternion& b);
extern Quaternion slerp(const Quaternion& p, const Quaternion& q, float t);
extern Quaternion conjugate(const Quaternion& q);
extern Quaternion pow(const Quaternion& q, float exponent);
