//
//  Color.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/11/21.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "graphics/Color.h"
#include "math/Math.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

const Color& Color::white()
{
    static const Color s_color(1, 1, 1, 1);
    return s_color;
}

const Color& Color::black()
{
    static const Color s_color(0, 0, 0, 1);
    return s_color;
}

const Color& Color::red()
{
    static const Color s_color(1, 0, 0, 1);
    return s_color;
}

const Color& Color::green()
{
    static const Color s_color(0, 1, 0, 1);
    return s_color;
}

const Color& Color::blue()
{
    static const Color s_color(0, 0, 1, 1);
    return s_color;
}

Color::Color(float r, float g, float b, float a):
    r(r), g(g), b(b), a(a)
{
}

bool Color::operator ==(const Color& c) const
{
    return
        Math::floatEqual(r, c.r) &&
        Math::floatEqual(g, c.g) &&
        Math::floatEqual(b, c.b) &&
        Math::floatEqual(a, c.a);
}

bool Color::operator !=(const Color& c) const
{
    return !(*this == c);
}

Color Color::lerp(const Color& from, const Color& to, float t, bool clamp_01)
{
    if (clamp_01)
    {
        t = Math::clamp(t, 0.0f, 1.0f);
    }

    return Color(
        Math::lerp(from.r, to.r, t),
        Math::lerp(from.g, to.g, t),
        Math::lerp(from.b, to.b, t),
        Math::lerp(from.a, to.a, t));
}

Color Color::parse(const String& str)
{
    auto str_lower = str.toLower();
    std::stringstream ss;
    ss << std::hex << str_lower.str();
    unsigned int color_i = 0;
    ss >> color_i;

    int r = (color_i & 0xff000000) >> 24;
    int g = (color_i & 0xff0000) >> 16;
    int b = (color_i & 0xff00) >> 8;
    int a = (color_i & 0xff);

    float div = 1 / 255.f;
    return Color((float) r, (float) g, (float) b, (float) a) * div;
}

Color Color::operator *(const Color& c) const
{
    return Color(r * c.r, g * c.g, b * c.b, a * c.a);
}

Color& Color::operator *=(const Color& c)
{
    r *= c.r;
    g *= c.g;
    b *= c.b;
    a *= c.a;
    return *this;
}

Color Color::operator *(float v) const
{
    return Color(r * v, g * v, b * v, a * v);
}

Color Color::operator /(float v) const
{
    return *this * (1 / v);
}

NAMESPACE_TUZZI_ENGINE_END
