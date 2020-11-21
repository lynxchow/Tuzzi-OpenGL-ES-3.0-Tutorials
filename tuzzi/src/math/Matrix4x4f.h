//
//  Matrix4x4f.h
//  Tuzzi
//
//  Created by Lyn on 2020/11/21.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_MATH_MATRIX4X4F_H_
#define _TUZZI_MATH_MATRIX4X4F_H_

#include "Common.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

struct Matrix4x4f
{
    Matrix4x4f() { }
    Matrix4x4f(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33):
        m00(m00), m01(m01), m02(m02), m03(m03),
        m10(m10), m11(m11), m12(m12), m13(m13),
        m20(m20), m21(m21), m22(m22), m23(m23),
        m30(m30), m31(m31), m32(m32), m33(m33)
    {
    }

    float m00;
    float m01;
    float m02;
    float m03;
    float m10;
    float m11;
    float m12;
    float m13;
    float m20;
    float m21;
    float m22;
    float m23;
    float m30;
    float m31;
    float m32;
    float m33;

private:
    Matrix4x4f(const float* ms);
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Matrix4x4f_h */
