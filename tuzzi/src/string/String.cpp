//
//  String.cpp
//  Tuzzi
//
//  Created by Lyn on 2019/7/18.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "string/String.h"
#include <stdarg.h>
NAMESPACE_TUZZI_ENGINE_BEGIN

String stringWithFormat(const char* format, ...)
{
    va_list vs;
    va_start(vs, format);
    String result = stringWithFormat(format, vs);
    va_end(vs);

    return result;
}

String stringWithFormat(const char* format, va_list vs)
{
    String result;

    int size = vsnprintf(nullptr, 0, format, vs);

	char *buffer = (char *)malloc(size + 1);
    buffer[size] = 0;

    size = vsnprintf(buffer, size + 1, format, vs);

    result = buffer;

    free(buffer);

    return result;
    
}

NAMESPACE_TUZZI_ENGINE_END
