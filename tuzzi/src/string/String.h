//
//  String.h
//  Tuzzi
//
//  Created by Lyn on 2019/7/18.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_STRING_STRING_H_
#define _TUZZI_STRING_STRING_H_

#include "memory/ByteBuffer.h"
#include "Common.h"
#include <string>
#include <sstream>

NAMESPACE_TUZZI_ENGINE_BEGIN

class String
{
public:
    static String Format(const char* format, ...);

    String();
    String(const char* str);
    String(const char* str, int size);
    String(const ByteBuffer& buffer);

    int size() const;
    bool empty() const;

    int indexOf(const String& str, int start = 0) const;
    int lastIndexOf(const String& str, int start = -1) const;
    String replace(const String& old, const String& to) const;
    bool startsWith(const String& str) const;
    bool endsWith(const String& str) const;
    String substring(int start, int count = -1) const;
    bool contains(const String& str) const;

    bool operator ==(const String& right) const;
    bool operator !=(const String& right) const;
    String operator +(const String& right) const;
    String& operator +=(const String& right);
    bool operator <(const String& right) const;
    char& operator[](int index);
    const char& operator[](int index) const;

    const char* str() const;

    template<class V>
    V to() const;

    template<class V>
    static String toString(const V& v);

private:
    std::string m_string;
};

bool operator ==(const char* left, const String& right);
bool operator !=(const char* left, const String& right);
String operator +(const char* left, const String& right);

template<class V>
V String::to() const
{
    std::stringstream ss(m_string);
    V v;
    ss >> v;
    return v;
}

template<class V>
String String::toString(const V& v)
{
    std::stringstream ss;
    ss << v;
    String str;
    str.m_string = ss.str();
    return str;
}

NAMESPACE_TUZZI_ENGINE_END

#endif /* String_h */
