//
//  Vector2f.h
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_MATH_VECTOR2F_H_
#define _TUZZI_MATH_VECTOR2F_H_

#include "Common.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class String;
struct Vector3f;

struct Vector2f
{
public:
    static const Vector2f& one();
    static const Vector2f& zero();
    static Vector2f lerp(const Vector2f& from, const Vector2f& to, float t);
    explicit Vector2f(float x = 0, float y = 0);
    Vector2f(const Vector3f& v3);
    Vector2f operator +(const Vector2f& value) const;
    Vector2f& operator +=(const Vector2f& value);
    Vector2f operator -(const Vector2f& value) const;
    Vector2f& operator -=(const Vector2f& value);
    float operator *(const Vector2f& v) const;
    Vector2f operator *(float value) const;
    Vector2f& operator *=(float value);
    bool operator ==(const Vector2f& value) const;
    bool operator !=(const Vector2f& value) const;
    float dot(const Vector2f& v) const;
    float magnitude() const;
    float sqrMagnitude() const;
    String toString() const;

    float x;
    float y;
};

NAMESPACE_TUZZI_ENGINE_END


#endif /* Vector2f_h */
