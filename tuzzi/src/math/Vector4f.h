//
//  Vector4f.h
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_MATH_VECTOR4F_H_
#define _TUZZI_MATH_VECTOR4F_H_

#include "Common.h"
#include "math/Vector3f.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

struct Vector4f
{
    explicit Vector4f(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
    Vector4f(const Vector3f& v, float w = 0);
    bool operator ==(const Vector4f& v) const;
    bool operator !=(const Vector4f& v) const;
    Vector4f& operator *=(float v);
    Vector4f operator *(float v) const;
    float& operator [](int index) const;
    static float dot(const Vector4f& v1, const Vector4f& v2);
    Vector4f operator +(const Vector4f& v) const;
    Vector4f operator -(const Vector4f& v) const;
    Vector4f operator /(float v) const;
    Vector4f& operator +=(const Vector4f& v);
    Vector4f& operator -=(const Vector4f& v);
    Vector4f& operator /=(float v);
    
    float x;
    float y;
    float z;
    float w;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Vector4f_h */
