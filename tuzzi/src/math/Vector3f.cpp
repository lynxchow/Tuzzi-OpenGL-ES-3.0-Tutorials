//
//  Vector3f.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "math/Vector3f.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z)
{
    
}

float& Vector3f::operator [](int index) const
{
    return ((float *) this)[index];
}

NAMESPACE_TUZZI_ENGINE_END
