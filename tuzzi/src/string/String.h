//
//  String.h
//  Tuzzi
//
//  Created by Lyn on 2019/7/18.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_STRING_STRING_H_
#define _TUZZI_STRING_STRING_H_

#include "Common.h"
#include <string>

NAMESPACE_TUZZI_ENGINE_BEGIN

using String = std::string;

String stringWithFormat(const char* format, ...);
String stringWithFormat(const char* format, va_list list);

NAMESPACE_TUZZI_ENGINE_END

#endif /* String_h */
