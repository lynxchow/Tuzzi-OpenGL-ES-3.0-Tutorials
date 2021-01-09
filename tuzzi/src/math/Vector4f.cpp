//
//  Vector4f.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "math/Vector4f.h"
#include "math/Math.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

Vector4f::Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
    
}

Vector4f::Vector4f(const Vector3f& v, float w):
    x(v.x), y(v.y), z(v.z), w(w)
{
}

bool Vector4f::operator ==(const Vector4f& v) const
{
    return
        Math::floatEqual(x, v.x) &&
        Math::floatEqual(y, v.y) &&
        Math::floatEqual(z, v.z) &&
        Math::floatEqual(w, v.w);
}

bool Vector4f::operator !=(const Vector4f& v) const
{
    return !(*this == v);
}

Vector4f& Vector4f::operator *=(float v)
{
    x *= v;
    y *= v;
    z *= v;
    w *= v;
    return *this;
}

Vector4f Vector4f::operator *(float v) const
{
    return Vector4f(x * v, y * v, z * v, w * v);
}

float& Vector4f::operator [](int index) const
{
    return ((float *) this)[index];
}

float Vector4f::dot(const Vector4f& v1, const Vector4f& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

Vector4f Vector4f::operator +(const Vector4f& v) const
{
    return Vector4f(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4f Vector4f::operator -(const Vector4f& v) const
{
    return Vector4f(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4f Vector4f::operator /(float v) const
{
    return Vector4f(x / v, y / v, z / v, w / v);
}

Vector4f& Vector4f::operator +=(const Vector4f& v)
{
    *this = *this + v;
    return *this;
}

Vector4f& Vector4f::operator -=(const Vector4f& v)
{
    *this = *this - v;
    return *this;
}

Vector4f& Vector4f::operator /=(float v)
{
    *this = *this / v;
    return *this;
}

NAMESPACE_TUZZI_ENGINE_END
