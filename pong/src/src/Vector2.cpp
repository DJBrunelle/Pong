#include "Vector2.h"

Vector2::Vector2()
{
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2& Vector2::operator*=(float s)
{
    x *= s;
    y *= s;
    return (*this);
}
Vector2& Vector2::operator/=(float s)
{
    s = 1.0f / s;
    x *= s;
    y *= s;
    return (*this);
}

Vector2& Vector2::operator-=(const Vector2& v)
{
    x -= v.x;
    y -= v.y;
    return (*this);
}

Vector2& Vector2::operator+=(const Vector2& v)
{
    x += v.x;
    y += v.y;
    return (*this);
}