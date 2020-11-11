//
//  Vector3f.h
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_MATH_VECTOR3F_H_
#define _TUZZI_MATH_VECTOR3F_H_

#include "Common.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

struct Vector3f
{
public:
    Vector3f();
    
    Vector3f(float x, float y, float z);
    
    float& operator [](int index) const;
    
    float x;
    float y;
    float z;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Vector3f_h */
