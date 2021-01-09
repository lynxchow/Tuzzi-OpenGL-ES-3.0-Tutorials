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
#include "math/Quaternionf.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

struct Matrix4x4f
{
    
    Matrix4x4f();
    Matrix4x4f(float m00, float m01, float m02, float m03,
               float m10, float m11, float m12, float m13,
               float m20, float m21, float m22, float m23,
               float m30, float m31, float m32, float m33);
    
    Matrix4x4f operator *(const Matrix4x4f& mat) const;
    Vector4f operator *(const Vector4f& v) const;
    Vector3f multiplyPoint(const Vector3f& v) const;
    Vector3f multiplyPoint3x4(const Vector3f& v) const;
    Vector3f multiplyDirection(const Vector3f& v) const;
    Matrix4x4f inverse() const;
    Matrix4x4f transpose() const;
    String toString() const;
    void setRow(int row, const Vector4f& v);
    Vector4f getRow(int row);
    void setColumn(int row, const Vector4f& v);
    Vector4f getColumn(int row);

    static Matrix4x4f identity();
    static Matrix4x4f translation(const Vector3f& t);
    static Matrix4x4f rotation(const Quaternionf& r);
    static Matrix4x4f scaling(const Vector3f& s);
    static Matrix4x4f trs(const Vector3f& t, const Quaternionf& r, const Vector3f& s);
    static Matrix4x4f lookTo(const Vector3f& eye_position, const Vector3f& to_direction, const Vector3f& up_direction);
    static Matrix4x4f perspective(float fov, float aspect, float zNear, float zFar);
    static Matrix4x4f ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    
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
