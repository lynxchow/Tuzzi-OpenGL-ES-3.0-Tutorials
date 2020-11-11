//
//  File.h
//  Tuzzi
//
//  Created by Lyn on 2020/5/6.
//  Copyright © 2020 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_IO_FILE_H_
#define _TUZZI_IO_FILE_H_

#include "Object.h"
#include "memory/ByteBuffer.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class File
{
public:
    static bool exist(const String& path);
    static ByteBuffer readAllBytes(const String& path);
    static bool writeAllBytes(const String& path, const ByteBuffer& buffer);
    static String readAllText(const String& path);
    static bool writeAllText(const String& path, const String& text);
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* File_h */
