//
//  Vector2f.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "math/Vector2f.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

Vector2f::Vector2f() : x(0.0), y(0.0)
{
    
}

Vector2f::Vector2f(float x, float y) : x(x), y(y)
{
    
}

float& Vector2f::operator [](int index) const
{
    return ((float *) this)[index];
}

NAMESPACE_TUZZI_ENGINE_END
