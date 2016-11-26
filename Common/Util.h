//
//  Util.hpp
//  Common
//
//  Created by Pocoyo Chow on 24/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef Util_hpp
#define Util_hpp

#include <stdio.h>
#include <stdarg.h>

#ifdef ANDROID
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/asset_manager.h>
typedef AAsset File;
#else
typedef FILE File;
#endif

#ifdef __APPLE__
#include "FileWrapper.h"
#endif

#ifndef __APPLE__
#pragma pack(push,x1)                            // Byte alignment (8-bit)
#pragma pack(1)
#endif

typedef struct
#ifdef __APPLE__
__attribute__ ( ( packed ) )
#endif
{
    unsigned char  IdSize,
    MapType,
    ImageType;
    unsigned short PaletteStart,
    PaletteSize;
    unsigned char  PaletteEntryDepth;
    unsigned short X,
    Y,
    Width,
    Height;
    unsigned char  ColorDepth,
    Descriptor;
    
} TGA_HEADER;

#ifndef __APPLE__
#pragma pack(pop,x1)
#endif


#ifdef __cplusplus
extern "C" {
#endif

void utilLog(const char *formatStr, ...);
const char *fileOpen(const char *fileName);
unsigned char *loadTGA(const char *fileName, int *width, int *height);
    
#ifdef __cplusplus
}
#endif

#endif /* Util_hpp */
