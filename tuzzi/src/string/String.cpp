//
//  String.cpp
//  Tuzzi
//
//  Created by Lyn on 2019/7/18.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "string/String.h"
#include "container/Vector.h"
#include <stdarg.h>

NAMESPACE_TUZZI_ENGINE_BEGIN

String::String()
{
}

String::String(const char *str):
    m_string(str)
{
}

String::String(const char* str, int size) :
    m_string(str, size)
{
}

String::String(const ByteBuffer& buffer) :
    m_string((const char*) buffer.bytes(), buffer.size())
{
}

int String::size() const
{
    return (int) m_string.size();
}

bool String::empty() const
{
    return m_string.empty();
}

bool String::operator ==(const String& right) const
{
    if (this->size() == right.size())
    {
        return memcmp(this->m_string.data(), right.m_string.data(), (int) m_string.size()) == 0;
    }

    return false;
}

bool String::operator !=(const String& right) const
{
    return !(*this == right);
}

bool operator ==(const char* left, const String& right)
{
    return right == left;
}

bool operator !=(const char* left, const String& right)
{
    return right != left;
}

String String::operator +(const String& right) const
{
    String result;
    result.m_string = m_string + right.m_string;
    return result;
}

String& String::operator +=(const String& right)
{
    *this = *this + right;
    return *this;
}

String operator +(const char* left, const String& right)
{
    return String(left) + right;
}

bool String::operator <(const String& right) const
{
    return m_string < right.m_string;
}

char& String::operator[](int index)
{
    return m_string[index];
}

const char& String::operator[](int index) const
{
    return m_string[index];
}

const char* String::str() const
{
    return m_string.c_str();
}

int String::indexOf(const String& str, int start) const
{
    size_t pos = m_string.find(str.m_string, start);
    if (pos != std::string::npos)
    {
        return (int) pos;
    }
    else
    {
        return -1;
    }
}

bool String::contains(const String& str) const
{
    return this->indexOf(str) >= 0;
}

int String::lastIndexOf(const String& str, int start) const
{
    size_t pos = m_string.rfind(str.m_string, start);
    if (pos != std::string::npos)
    {
        return (int) pos;
    }
    else
    {
        return -1;
    }
}

String String::replace(const String& old, const String& to) const
{
    String result(*this);

    int start = 0;
    while (true)
    {
        int index = result.indexOf(old, start);
        if (index >= 0)
        {
            result.m_string.replace(index, old.m_string.size(), to.m_string);
            start = index + (int) to.m_string.size();
        }
        else
        {
            break;
        }
    }

    return result;
}

bool String::startsWith(const String& str) const
{
    if (str.size() == 0)
    {
        return true;
    }
    else if (this->size() < str.size())
    {
        return false;
    }
    else
    {
        return memcmp(&(*this)[0], &str[0], str.size()) == 0;
    }
}

bool String::endsWith(const String& str) const
{
    if (str.size() == 0)
    {
        return true;
    }
    else if (this->size() < str.size())
    {
        return false;
    }
    else
    {
        return memcmp(&(*this)[this->size() - str.size()], &str[0], str.size()) == 0;
    }
}

String String::substring(int start, int count) const
{
    String result;
    result.m_string = m_string.substr(start, count);
    return result;
}

String String::toLower() const
{
    Vector<char> str;

    for (auto c : m_string)
    {
        if (c >= 'A' && c <= 'Z')
        {
            c -= 'A' - 'a';
        }
        str.push_back(c);
    }
    str.push_back(0);

    return String(&str[0]);
}

String String::toUpper() const
{
    Vector<char> str;

    for (auto c : m_string)
    {
        if (c >= 'a' && c <= 'z')
        {
            c += 'A' - 'a';
        }
        str.push_back(c);
    }
    str.push_back(0);

    return String(&str[0]);
}

NAMESPACE_TUZZI_ENGINE_END
