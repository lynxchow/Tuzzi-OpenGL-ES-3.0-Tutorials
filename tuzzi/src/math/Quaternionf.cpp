//
//  Quaternionf.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/12/22.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "math/Math.h"
#include "math/Quaternionf.h"
#include "string/String.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

Quaternionf Quaternionf::identity()
{
    return Quaternionf();
}

Quaternionf::Quaternionf(float x, float y, float z, float w):
    x(x), y(y), z(z), w(w)
{
}

Vector3f Quaternionf::toEulerAngles() const
{
    float rx = atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y));
    float ry = asin(2 * (w * y - z * x));
    float rz = atan2(2 * (w * z + x * y), 1 - 2 * (z * z + y * y));

    return Vector3f(rx, ry, rz) * Math::Rad2Deg;
}

String Quaternionf::toString() const
{
    std::stringstream ss;
    ss << '(' << x << ',' << y << ',' << z << ',' << w << ')';
    auto str = ss.str();
    return str.c_str();
}

Quaternionf Quaternionf::operator *(const Quaternionf& quat) const
{
    float _x = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
    float _y = w * quat.y + y * quat.w + z * quat.x - x * quat.z;
    float _z = w * quat.z + z * quat.w + x * quat.y - y * quat.x;
    float _w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;

    return Quaternionf(_x, _y, _z, _w);
}

Quaternionf Quaternionf::operator *(float v) const
{
    return Quaternionf(x * v, y * v, z * v, w * v);
}

Vector3f Quaternionf::operator *(const Vector3f& p) const
{
    Quaternionf p_ = *this * Quaternionf(p.x, p.y, p.z, 0) * inverse(*this);

    return Vector3f(p_.x, p_.y, p_.z);
}

bool Quaternionf::operator !=(const Quaternionf& v) const
{
    return !(*this == v);
}

bool Quaternionf::operator ==(const Quaternionf& v) const
{
    return Math::floatEqual(v.x, x) &&
        Math::floatEqual(v.y, y) &&
        Math::floatEqual(v.z, z) &&
        Math::floatEqual(v.w, w);
}

Quaternionf Quaternionf::inverse(const Quaternionf& q)
{
    return Quaternionf(-q.x, -q.y, -q.z, q.w);
}

Quaternionf Quaternionf::angleAxis(float angle, const Vector3f& axis)
{
    Vector3f v = Vector3f::normalize(axis);
    float cosv, sinv;

    cosv = cos(Math::Deg2Rad * angle * 0.5f);
    sinv = sin(Math::Deg2Rad * angle * 0.5f);

    float x = v.x * sinv;
    float y = v.y * sinv;
    float z = v.z * sinv;
    float w = cosv;

    return Quaternionf(x, y, z, w);
}

Quaternionf Quaternionf::euler(float x, float y, float z)
{
    Quaternionf around_x = angleAxis(x, Vector3f(1, 0, 0));
    Quaternionf around_y = angleAxis(y, Vector3f(0, 1, 0));
    Quaternionf around_z = angleAxis(z, Vector3f(0, 0, 1));

    return around_y * around_x * around_z;
}

Quaternionf Quaternionf::lerp(const Quaternionf& from, const Quaternionf& to, float t)
{
    Quaternionf to_;

    if (from.dot(to) < 0)
    {
        to_ = to * -1.0f;
    }
    else
    {
        to_ = to;
    }

    Quaternionf lerp = Quaternionf(
        Math::lerp(from.x, to_.x, t),
        Math::lerp(from.y, to_.y, t),
        Math::lerp(from.z, to_.z, t),
        Math::lerp(from.w, to_.w, t));
    lerp.normalize();

    return lerp;
}

Quaternionf Quaternionf::slerp(const Quaternionf& from, const Quaternionf& to, float t)
{
    Quaternionf to_;

    if (from.dot(to) < 0)
    {
        to_ = to * -1.0f;
    }
    else
    {
        to_ = to;
    }

    Quaternionf slerp;
    float t_ = 1 - t;
    float Wa, Wb;
    float theta = acos(from.x * to_.x + from.y * to_.y + from.z * to_.z + from.w * to_.w);
    float sn = sin(theta);
    if (!Math::floatEqual(sn, 0))
    {
        float inv_sin = 1 / sn;
        Wa = sin(t_ * theta);
        Wb = sin(t * theta);
        slerp.x = (Wa * from.x + Wb * to_.x) * inv_sin;
        slerp.y = (Wa * from.y + Wb * to_.y) * inv_sin;
        slerp.z = (Wa * from.z + Wb * to_.z) * inv_sin;
        slerp.w = (Wa * from.w + Wb * to_.w) * inv_sin;
    }
    else
    {
        slerp = from;
    }

    slerp.normalize();

    return slerp;
}

Quaternionf Quaternionf::fromToRotation(const Vector3f& from_direction, const Vector3f& to_direction)
{
    Vector3f origin = Vector3f::normalize(from_direction);
    Vector3f fn = Vector3f::normalize(to_direction);

    if (fn != origin)
    {
        if (!Math::floatEqual(fn.sqrMagnitude(), 0) && !Math::floatEqual(origin.sqrMagnitude(), 0))
        {
            float deg = Vector3f::angle(origin, fn);
            Vector3f axis = origin * fn;

            if (axis == Vector3f(0, 0, 0))
            {
                if (!Math::floatEqual(origin.x, 0))
                {
                    float x = -origin.y / origin.x;
                    float y = 1;
                    float z = 0;

                    axis = Vector3f(x, y, z);
                }
                else if (!Math::floatEqual(origin.y, 0))
                {
                    float y = -origin.z / origin.y;
                    float x = 0;
                    float z = 1;

                    axis = Vector3f(x, y, z);
                }
                else
                {
                    float z = -origin.x / origin.z;
                    float y = 0;
                    float x = 1;

                    axis = Vector3f(x, y, z);
                }

                return Quaternionf::angleAxis(deg, axis);
            }
            else
            {
                return Quaternionf::angleAxis(deg, axis);
            }
        }
    }

    return Quaternionf::identity();
}

Quaternionf Quaternionf::lookRotation(const Vector3f& forward, const Vector3f& up)
{
    Vector3f fn = Vector3f::normalize(forward);
    Vector3f un = Vector3f::normalize(up);
    Vector3f right = un * fn;
    Vector3f up0 = fn * right;
    
    Quaternionf rot0 = Quaternionf::fromToRotation(Vector3f(0, 0, 1), fn);
    Vector3f up1 = rot0 * Vector3f(0, 1, 0);
    Quaternionf rot1 = Quaternionf::fromToRotation(up1, up0);
    
    return rot1 * rot0;
}

void Quaternionf::normalize()
{
    float sqr_magnitude = x*x + y*y + z*z + w*w;
    if (!Math::floatEqual(sqr_magnitude, 0))
    {
        float sq = sqrt(sqr_magnitude);

        float inv = 1.0f / sq;
        x = x * inv;
        y = y * inv;
        z = z * inv;
        w = w * inv;
    }
}

float Quaternionf::dot(const Quaternionf& v) const
{
    return x * v.x + y * v.y + z * v.z + w * v.w;
}

NAMESPACE_TUZZI_ENGINE_END
