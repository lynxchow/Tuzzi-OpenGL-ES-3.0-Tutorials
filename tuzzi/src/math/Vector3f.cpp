//
//  Vector3f.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "math/Math.h"
#include "math/Vector2f.h"
#include "math/Vector3f.h"
#include "math/Vector4f.h"
#include "string/String.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

const Vector3f& Vector3f::zero()
{
    static const Vector3f s_zero(0, 0, 0);
    return s_zero;
}

const Vector3f& Vector3f::one()
{
    static const Vector3f s_one(1, 1, 1);
    return s_one;
}

Vector3f::Vector3f(float x, float y, float z):
    x(x), y(y), z(z)
{
    
}

Vector3f::Vector3f(const Vector4f& v4):
    x(v4.x),
    y(v4.y),
    z(v4.z)
{
    
}

Vector3f::Vector3f(const Vector2f& v2):
    x(v2.x),
    y(v2.y),
    z(0)
{
    
}

void Vector3f::normalize()
{
    float sqr_magnitude = sqrMagnitude();
    if (!Math::floatEqual(sqr_magnitude, 0))
    {
        float sq = sqrt(sqr_magnitude);
        
        float inv = 1.0f / sq;
        x *= inv;
        y *= inv;
        z *= inv;
    }
}

Vector3f Vector3f::normalize(Vector3f value)
{
    Vector3f v = value;
    v.normalize();
    return v;
}

Vector3f Vector3f::max(const Vector3f& a, const Vector3f& b)
{
    return Vector3f(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

Vector3f Vector3f::min(const Vector3f& a, const Vector3f& b)
{
    return Vector3f(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Vector3f Vector3f::lerp(const Vector3f& from, const Vector3f& to, float t)
{
    return Vector3f(Math::lerp(from.x, to.x, t), Math::lerp(from.y, to.y, t), Math::lerp(from.z, to.z, t));
}

float Vector3f::angle(const Vector3f& from, const Vector3f& to)
{
    float mod = from.sqrMagnitude() * to.sqrMagnitude();
    float dot = from.dot(to) / sqrt(mod);
    dot = Math::clamp(dot, -1.0f, 1.0f);

    float deg = acos(dot) * Math::Rad2Deg;

    return deg;
}

Vector3f Vector3f::operator -() const
{
    return Vector3f(-x, -y, -z);
}

Vector3f Vector3f::operator +(const Vector3f& v) const
{
    return Vector3f(x + v.x, y + v.y, z + v.z);
}

Vector3f& Vector3f::operator +=(const Vector3f& v)
{
    *this = *this + v;
    return *this;
}

Vector3f Vector3f::operator -(const Vector3f& v) const
{
    return Vector3f(x - v.x, y - v.y, z - v.z);
}

Vector3f Vector3f::operator *(const Vector3f& v) const
{
    float _x = y*v.z - z*v.y;
    float _y = z*v.x - x*v.z;
    float _z = x*v.y - y*v.x;

    return Vector3f(_x, _y, _z);
}

Vector3f Vector3f::operator *(float v) const
{
    return Vector3f(x * v, y * v, z * v);
}

Vector3f Vector3f::operator *=(float v)
{
    *this = *this * v;
    return *this;
}

Vector3f Vector3f::operator /(float v) const
{
    return Vector3f(x / v, y / v, z / v);
}

Vector3f Vector3f::operator /=(float v)
{
    *this = *this / v;
    return *this;
}

bool Vector3f::operator !=(const Vector3f& v) const
{
    return !(*this == v);
}

bool Vector3f::operator ==(const Vector3f& v) const
{
    return Math::floatEqual(v.x, x) &&
        Math::floatEqual(v.y, y) &&
        Math::floatEqual(v.z, z);
}

float Vector3f::dot(const Vector3f& a, const Vector3f& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Vector3f::dot(const Vector3f& v) const
{
    return Vector3f::dot(*this, v);
}

String Vector3f::toString() const
{
    std::stringstream ss;
    ss << '(' << x << ',' << y << ',' << z << ')';
    auto str = ss.str();
    return str.c_str();
}

float Vector3f::magnitude() const
{
    return sqrt(sqrMagnitude());
}

float Vector3f::sqrMagnitude() const
{
    return x * x + y * y + z * z;
}

float Vector3f::magnitude(const Vector3f& v)
{
    return v.magnitude();
}

float Vector3f::sqrMagnitude(const Vector3f& v)
{
    return v.sqrMagnitude();
}

float Vector3f::distance(const Vector3f& a, const Vector3f& b)
{
    return (a - b).sqrMagnitude();
}

NAMESPACE_TUZZI_ENGINE_END
