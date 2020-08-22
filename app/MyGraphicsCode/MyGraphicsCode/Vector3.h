#pragma once
#include <math.h>

class Vector3
{
public:
	float x, y, z;
	Vector3() {}
	Vector3(const Vector3& a) : x(a.x), y(a.y), z(a.z) {}
	Vector3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}

	Vector3& operator =(const Vector3& a)
	{
		x = a.x;
		y = a.y;
		z = a.z;
		return *this;
	}

	bool operator ==(const Vector3& a)
	{
		return x == a.x && y == a.y && z == a.z;
	}

	bool operator !=(const Vector3& a)
	{
		return x != a.x || y != a.y || z != a.z;
	}

	void zero()
	{
		x = y = z = 0.0f;
	}

	Vector3 operator -() const
	{
		return Vector3(-x, -y, -z);
	}

	Vector3 operator +(const Vector3& a) const
	{
		return Vector3(x + a.x, y + a.y, z + a.z);
	}

	Vector3 operator -(const Vector3& a) const
	{
		return Vector3(x - a.x, y - a.y, z - a.z);
	}

	Vector3 operator *(float a) const
	{
		return Vector3(x * a, y * a, z * a);
	}

	Vector3 operator /(float a) const
	{
		float OneOverA = 1.0f / a;
		return Vector3(x * OneOverA, y * OneOverA, z * OneOverA);
	}

	Vector3& operator +=(const Vector3& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}

	Vector3& operator -=(const Vector3& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}

	Vector3& operator *=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	Vector3& operator /=(float a)
	{
		float OneOverA = 1.0f / a;
		x *= OneOverA;
		y *= OneOverA;
		z *= OneOverA;
		return *this;
	}

	void normalize()
	{
		float MagSq = x * x + y * y + z * z;
		if (MagSq > 0.0f)
		{
			float OneOverMag = 1.0f / sqrt(MagSq);
			x *= OneOverMag;
			y *= OneOverMag;
			z *= OneOverMag;
		}
	}

	float operator *(const Vector3& a) const
	{
		return x * a.x + y * a.y + z * a.z;
	}
};

inline float VectorMag(const Vector3 &a)
{
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

inline Vector3 CrossProduct(const Vector3& a, const Vector3& b)
{
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.z
		);
}

inline Vector3 operator *(float k, const Vector3 &v)
{
	return Vector3(k * v.x, k * v.y, k * v.z);
}

inline float Distance(const Vector3& a, const Vector3& b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return sqrtf(dx * dx + dy * dy + dz * dz);
}

extern const Vector3 kZeroVector;
