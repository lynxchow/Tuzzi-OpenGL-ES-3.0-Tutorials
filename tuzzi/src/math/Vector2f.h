//
//  Vector2f.h
//  Tuzzi
//
//  Created by Lyn on 2020/9/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_MATH_VECTOR2F_H_
#define _TUZZI_MATH_VECTOR2F_H_

#include "Common.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

struct Vector2f
{
public:
    Vector2f();
    
    Vector2f(float x, float y);
    
    float& operator [](int index) const;
    
    float x;
    float y;
};

NAMESPACE_TUZZI_ENGINE_END


#endif /* Vector2f_h */
