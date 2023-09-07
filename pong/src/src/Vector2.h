#pragma once
#include <cmath>

struct Vector2
{
	float x;
	float y;

    Vector2();
	Vector2(float x, float y);

	Vector2& operator *=(float s);
	Vector2& operator /=(float s);
	Vector2& operator +=(const Vector2& v);
	Vector2& operator -=(const Vector2& v);
};

inline Vector2 operator *(const Vector2& v, float s)
{
    return (Vector2(v.x * s, v.y * s));
}

inline Vector2 operator /(const Vector2& v, float s)
{
    s = 1.0f / s;
    return (Vector2(v.x * s, v.y * s));
}

inline Vector2 operator -(const Vector2& v)
{
    return (Vector2(-v.x, -v.y));
}

inline Vector2 operator +(const Vector2& a, const Vector2& b)
{
    return (Vector2(a.x + b.x, a.y + b.y));
}

inline Vector2 operator -(const Vector2& a, const Vector2& b)
{
    return (Vector2(a.x - b.x, a.y - b.y));
}

inline float Magnitude(const Vector2& v)
{
    return (sqrt(v.x * v.x + v.y * v.y));
}

inline Vector2 Normalize(const Vector2& v)
{
    return (v / Magnitude(v));
}