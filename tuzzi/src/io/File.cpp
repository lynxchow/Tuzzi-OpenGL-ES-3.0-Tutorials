//
//  File.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/5/6.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "io/File.h"
#include <fstream>

NAMESPACE_TUZZI_ENGINE_BEGIN

bool File::exist(const String& path)
{
    std::ifstream is(path.str(), std::ios::binary);

    bool exist = !(!is);

    if (exist)
    {
        is.close();
    }

    return exist;
}

ByteBuffer File::readAllBytes(const String& path)
{
    ByteBuffer buffer;

    std::ifstream is(path.str(), std::ios::binary);
    if (is)
    {
        is.seekg(0, std::ios::end);
        int size = (int) is.tellg();
        is.seekg(0, std::ios::beg);

        buffer = ByteBuffer(size);

        is.read((char*) buffer.bytes(), size);
        is.close();
    }

    return buffer;
}

bool File::writeAllBytes(const String& path, const ByteBuffer& buffer)
{
    std::ofstream os(path.str(), std::ios::binary);
    if (os)
    {
        os.write((const char*) buffer.bytes(), buffer.size());
        os.close();

        return true;
    }
    else
    {
        return false;
    }
}

String File::readAllText(const String& path)
{
    ByteBuffer buffer = File::readAllBytes(path);
    return String((const char *) buffer.bytes(), buffer.size());
}

bool File::writeAllText(const String& path, const String& text)
{
    ByteBuffer buffer((byte*) text.str(), text.size());
    return File::writeAllBytes(path, buffer);
}

NAMESPACE_TUZZI_ENGINE_END
