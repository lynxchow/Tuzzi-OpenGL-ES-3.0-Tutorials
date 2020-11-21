//
//  Color.h
//  Tuzzi
//
//  Created by Lyn on 2020/11/21.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_MATH_COLOR_H_
#define _TUZZI_MATH_COLOR_H_

#include "Common.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

struct Color
{
public:
    Color(float r = 1, float g = 1, float b = 1, float a = 1);
    
    float r;
    float g;
    float b;
    float a;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Color_h */
