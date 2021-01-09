//
//  Quaternionf.hpp
//  Tuzzi
//
//  Created by Lyn on 2020/12/22.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_MATH_QUATERNIONF_H_
#define _TUZZI_MATH_QUATERNIONF_H_

#include "Common.h"
#include "math/Vector3f.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

struct Quaternionf
{
    static Quaternionf identity();
    static Quaternionf inverse(const Quaternionf& q);
    static Quaternionf angleAxis(float angle, const Vector3f& axis);
    static Quaternionf euler(float x, float y, float z);
    static Quaternionf euler(const Vector3f& e) { return euler(e.x, e.y, e.z); }
    static Quaternionf lerp(const Quaternionf& from, const Quaternionf& to, float t);
    static Quaternionf slerp(const Quaternionf& from, const Quaternionf& to, float t);
    static Quaternionf fromToRotation(const Vector3f& from_direction, const Vector3f& to_direction);
    static Quaternionf lookRotation(const Vector3f& forward, const Vector3f& up);

    explicit Quaternionf(float x = 0, float y = 0, float z = 0, float w = 1);
    Quaternionf operator *(const Quaternionf& q) const;
    Quaternionf operator *(float v) const;
    Vector3f operator *(const Vector3f& p) const;
    bool operator !=(const Quaternionf& v) const;
    bool operator ==(const Quaternionf& v) const;
    Vector3f toEulerAngles() const;
    void normalize();
    float dot(const Quaternionf& v) const;
    String toString() const;
    
    float x;
    float y;
    float z;
    float w;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Quaternionf_h */
