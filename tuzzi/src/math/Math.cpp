//
//  Math.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "math/Math.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

const float Math::Epsilon = 0.00001f;
const float Math::PI = 3.1415926f;
const float Math::Deg2Rad = 0.0174533f;
const float Math::Rad2Deg = 57.2958f;

bool Math::floatEqual(float a, float b)
{
    return fabs(a - b) < Epsilon;
}

float Math::lerp(float from, float to, float t)
{
    return from + (to - from) * t;
}

NAMESPACE_TUZZI_ENGINE_END
