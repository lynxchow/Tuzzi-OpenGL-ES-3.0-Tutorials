//
//  Math.h
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_MATH_MATH_H_
#define _TUZZI_MATH_MATH_H_

#include <math.h>
#include "Common.h"
#include "math/Vector2f.h"
#include "math/Vector3f.h"
#include "math/Vector4f.h"
#include "math/Matrix4x4f.h"
#include "math/Quaternionf.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class Math
{
public:
    static const float Epsilon;
    static const float PI;
    static const float Deg2Rad;
    static const float Rad2Deg;
    
    template <class T>
    inline static T max(T a, T b) { return a > b ? a : b; }
    template <class T>
    inline static T min(T a, T b) { return a < b ? a : b; }
    static bool floatEqual(float a, float b);
    static float lerp(float from, float to, float t);
    template <class T>
    inline static T clamp(T value, T min, T max) { return Math::min(Math::max(value, min), max); }
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Math_h */
