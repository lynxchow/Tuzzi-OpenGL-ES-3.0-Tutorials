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
#include "string/String.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

struct Color
{
public:
    static const Color& white();
    static const Color& black();
    static const Color& red();
    static const Color& green();
    static const Color& blue();

    static Color lerp(const Color &from, const Color &to, float t, bool clamp_01 = true);
    static Color parse(const String& str);

    Color(float r = 1, float g = 1, float b = 1, float a = 1);
    bool operator ==(const Color &c) const;
    bool operator !=(const Color &c) const;
    Color operator *(const Color &c) const;
    Color &operator *=(const Color &c);
    Color operator *(float v) const;
    Color operator /(float v) const;
    
    float r;
    float g;
    float b;
    float a;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Color_h */
