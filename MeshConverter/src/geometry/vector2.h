#ifndef __GEOMETRY_VECTOR2_H_INCLUDED__
#define __GEOMETRY_VECTOR2_H_INCLUDED__

#include <math.h>

/**
 * Represents a 2D vector and provides common methods for vector math. 
 * <p>Referenced/based on code from:</p>
 * <ul>
 * <li>3D Math Primer for Graphics and Game Development (Dunn & Parberry, 2002)</li>
 * <li>http://www.dhpoware.com/source/mathlib.html</li>
 * </ul>
 * @author Gered
 */
class Vector2
{
public:
	Vector2()                                              {}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2(const float *v)
	{
		x = v[0];
		y = v[1];
	}

	~Vector2()                                             {}

	void Set(float x, float y);

	static float Distance(const Vector2 &a, const Vector2 &b);
	static float Dot(const Vector2 &a, const Vector2 &b);
	static float Length(const Vector2 &v);
	static float LengthSquared(const Vector2 &v);
	static Vector2 Normalize(const Vector2 &v);
	static Vector2 SetLength(const Vector2 &v, float length);

	float x;
	float y;
};

bool operator==(const Vector2 &left, const Vector2 &right);
Vector2 operator-(const Vector2 &left);
Vector2 operator+(const Vector2 &left, const Vector2 &right);
Vector2 &operator+=(Vector2 &left, const Vector2 &right);
Vector2 operator-(const Vector2 &left, const Vector2 &right);
Vector2 &operator-=(Vector2 &left, const Vector2 &right);
Vector2 operator*(const Vector2 &left, float right);
Vector2 &operator*=(Vector2 &left, float right);
Vector2 operator/(const Vector2 &left, float right);
Vector2 &operator/=(Vector2 &left, float right);
Vector2 operator*(const Vector2 &left, const Vector2 &right);
Vector2 &operator*=(Vector2 &left, const Vector2 &right);
Vector2 operator/(const Vector2 &left, const Vector2 &right);
Vector2 &operator/=(Vector2 &left, const Vector2 &right);

inline void Vector2::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}

/**
 * Calculates the distance between two points.
 * @param a the first point
 * @param b the second point
 * @return the distance between both points
 */
inline float Vector2::Distance(const Vector2 &a, const Vector2 &b)
{
	return sqrtf(
		((b.x - a.x) * (b.x - a.x)) + 
		((b.y - a.y) * (b.y - a.y))
		);
}

/**
 * Computes the dot product of 2 vectors.
 * @param a first vector
 * @param b second vector
 * @return the dot product
 */
inline float Vector2::Dot(const Vector2 &a, const Vector2 &b)
{
	return 
		(a.x * b.y) + 
		(a.y * b.y);
}

/**
 * Returns the length (magnitude) of a vector.
 * @param v vector to calculate the length of
 * @return the vector length
 */
inline float Vector2::Length(const Vector2 &v)
{
	return sqrtf(
		(v.x * v.x) + 
		(v.y * v.y)
		);
}

/**
 * Returns the squared length of a vector (the magnitude minus the sqrt 
 * call).
 * @param v vector to calculate the squared length of
 * @return squared length of the vector
 */
inline float Vector2::LengthSquared(const Vector2 &v)
{
	return 
		(v.x * v.x) + 
		(v.y * v.y);
}

/**
 * Normalizes a vector.
 * @param v vector to normalize
 * @return the normalized vector
 */
inline Vector2 Vector2::Normalize(const Vector2 &v)
{
	float inverseLength = 1.0f / Length(v);
	return Vector2(
		v.x * inverseLength,
		v.y * inverseLength
		);
}

/**
 * Adjusts a vector so that it's length is equal to the given length.
 * @param v the original vector to be adjusted
 * @param length desired vector length (magnitude)
 * @return the resulting vector after it's length has been converted to the 
 *         desired amount
 */
inline Vector2 Vector2::SetLength(const Vector2 &v, float length)
{
	return v * (length / Length(v));
}

inline bool operator==(const Vector2 &left, const Vector2 &right)
{
	return (left.x == right.x && left.y == right.y);
}

inline Vector2 operator-(const Vector2 &left)
{
	return Vector2(-left.x, -left.y);
}

inline Vector2 operator+(const Vector2 &left, const Vector2 &right)
{
	return Vector2(left.x + right.x, left.y + right.y);
}

inline Vector2 &operator+=(Vector2 &left, const Vector2 &right)
{
	left.x += right.x;
	left.y += right.y;

	return left;
}

inline Vector2 operator-(const Vector2 &left, const Vector2 &right)
{
	return Vector2(left.x - right.x, left.y - right.y);
}

inline Vector2 &operator-=(Vector2 &left, const Vector2 &right)
{
	left.x -= right.x;
	left.y -= right.y;

	return left;
}

inline Vector2 operator*(const Vector2 &left, float right)
{
	return Vector2(left.x * right, left.y * right);
}

inline Vector2 &operator*=(Vector2 &left, float right)
{
	left.x *= right;
	left.y *= right;

	return left;
}

inline Vector2 operator/(const Vector2 &left, float right)
{
	return Vector2(left.x / right, left.y / right);
}

inline Vector2 &operator/=(Vector2 &left, float right)
{
	left.x /= right;
	left.y /= right;

	return left;
}

inline Vector2 operator*(const Vector2 &left, const Vector2 &right)
{
	return Vector2(left.x * right.x, left.y * right.y);
}

inline Vector2 &operator*=(Vector2 &left, const Vector2 &right)
{
	left.x *= right.x;
	left.y *= right.y;

	return left;
}

inline Vector2 operator/(const Vector2 &left, const Vector2 &right)
{
	return Vector2(left.x / right.x, left.y / right.y);
}

inline Vector2 &operator/=(Vector2 &left, const Vector2 &right)
{
	left.x /= right.x;
	left.y /= right.y;

	return left;
}


#endif
