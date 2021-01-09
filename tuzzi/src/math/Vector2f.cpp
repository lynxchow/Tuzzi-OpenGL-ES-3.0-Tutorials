//
//  Vector2f.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "math/Math.h"
#include "math/Vector2f.h"
#include "math/Vector3f.h"
#include "string/String.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

const Vector2f& Vector2f::zero()
{
    static const Vector2f s_zero(0, 0);
    return s_zero;
}

const Vector2f& Vector2f::one()
{
    static const Vector2f s_one(1, 1);
    return s_one;
}

Vector2f Vector2f::lerp(const Vector2f& from, const Vector2f& to, float t)
{
    return Vector2f(Math::lerp(from.x, from.x, t), Math::lerp(from.y, from.y, t));
}

Vector2f::Vector2f(float x, float y) : x(x), y(y)
{
    
}

Vector2f::Vector2f(const Vector3f& v3) : x(v3.x), y(v3.y)
{
    
}

Vector2f Vector2f::operator *(float value) const
{
    return Vector2f(x * value, y * value);
}

Vector2f Vector2f::operator +(const Vector2f& value) const
{
    return Vector2f(x * value.x, y + value.y);
}

Vector2f Vector2f::operator -(const Vector2f& value) const
{
    return Vector2f(x - value.x, y - value.y);
}

Vector2f& Vector2f::operator *=(float value)
{
    x *= value;
    y *= value;
    return *this;
}

Vector2f& Vector2f::operator +=(const Vector2f& value)
{
    x += value.x;
    y += value.y;
    return *this;
}

Vector2f& Vector2f::operator -=(const Vector2f& value)
{
    x -= value.x;
    y -= value.y;
    return *this;
}

float Vector2f::magnitude() const
{
    return sqrt(sqrMagnitude());
}

float Vector2f::sqrMagnitude() const
{
    return x * x + y * y;
}

bool Vector2f::operator ==(const Vector2f& value) const
{
    return Math::floatEqual(x, value.x) && Math::floatEqual(y, value.y);
}

bool Vector2f::operator !=(const Vector2f& value) const
{
    return !(*this == value);
}

float Vector2f::operator *(const Vector2f& v) const
{
    return x * v.y - y * v.x;
}

float Vector2f::dot(const Vector2f& v) const
{
    return x * v.x + y * v.y;
}

String Vector2f::toString() const
{
    std::stringstream ss;
    ss << '(' << ',' << y << ')';
    auto str = ss.str();
    return str.c_str();
}

NAMESPACE_TUZZI_ENGINE_END
