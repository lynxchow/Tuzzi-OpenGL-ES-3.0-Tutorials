//
//  Vector3f.h
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_MATH_VECTOR3F_H_
#define _TUZZI_MATH_VECTOR3F_H_

#include "Common.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class String;
struct Vector2f;
struct Vector4f;

struct Vector3f
{
    static const Vector3f& zero();
    static const Vector3f& one();
    static Vector3f normalize(Vector3f value);
    static float magnitude(const Vector3f& v);
    static float sqrMagnitude(const Vector3f& v);
    static float distance(const Vector3f& a, const Vector3f& b);
    static Vector3f max(const Vector3f& a, const Vector3f& b);
    static Vector3f min(const Vector3f& a, const Vector3f& b);
    static Vector3f lerp(const Vector3f& from, const Vector3f& to, float t);
    static float angle(const Vector3f& from, const Vector3f& to);
    static float dot(const Vector3f& a, const Vector3f& b);

    explicit Vector3f(float x = 0, float y = 0, float z = 0);
    Vector3f(const Vector4f& v4);
    Vector3f(const Vector2f& v2);
    Vector3f operator -() const;
    Vector3f operator +(const Vector3f& v) const;
    Vector3f& operator +=(const Vector3f& v);
    Vector3f operator -(const Vector3f& v) const;
    Vector3f operator *(const Vector3f& v) const;
    Vector3f operator *(float v) const;
    Vector3f operator *=(float v);
    Vector3f operator /(float v) const;
    Vector3f operator /=(float v);
    bool operator !=(const Vector3f& v) const;
    bool operator ==(const Vector3f& v) const;
    float dot(const Vector3f& v) const;
    void normalize();
    float magnitude() const;
    float sqrMagnitude() const;
    String toString() const;

    float x;
    float y;
    float z;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Vector3f_h */
