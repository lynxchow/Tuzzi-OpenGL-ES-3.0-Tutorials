//
//  Vector4f.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "math/Vector4f.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

Vector4f::Vector4f() : x(0.0), y(0.0), z(0.0), w(0.0)
{
    
}

Vector4f::Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
    
}

float& Vector4f::operator [](int index) const
{
    return ((float *) this)[index];
}

NAMESPACE_TUZZI_ENGINE_END
