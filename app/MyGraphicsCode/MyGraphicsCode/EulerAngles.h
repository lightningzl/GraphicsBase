#pragma once

class Quaternion;
class Matrix4x3;
class RotationMatrix;

class EulerAngles
{
public:
	float heading = 0.0f;
	float pitch = 0.0f;
	float bank = 0.0f;

	EulerAngles() {}

	EulerAngles(float h, float p, float b) :
		heading(h), pitch(p), bank(b) {}

	void identity()
	{
		heading = pitch = bank = 0.0f;
	}

	void canonize();

	void fromObjectToInertialQuaternion(const Quaternion& q);
	void fromInertialToObjectQuaternion(const Quaternion& q);

	void fromObjectToWorldMatrix(const Matrix4x3& m);
	void fromWorldToObjectMatrix(const Matrix4x3& m);

	void fromRotationMatrix(const RotationMatrix& m);
};

extern const EulerAngles kEulerAnglesIdentity;