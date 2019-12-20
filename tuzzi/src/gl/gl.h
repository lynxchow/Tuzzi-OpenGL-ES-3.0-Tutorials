//
//  gl.h
//  Tuzzi
//
//  Created by Lyn on 2019/11/20.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_GL_H_
#define _TUZZI_GL_H_

#if defined(__APPLE__)

#include "TargetConditionals.h"
    
#if TARGET_OS_IPHONE
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

#ifndef GL_HEADER_VERSION
#define GL_HEADER_VERSION "#version 300 es\n"
#endif

#elif TARGET_OS_MAC
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#ifndef GL_HEADER_VERSION
#define GL_HEADER_VERSION "#version 330 core\n"
#endif

#else
#   error "Unknown Apple platform"
#endif

#elif __ANDROID__

#include <GLES3/gl3.h>

#ifndef GL_HEADER_VERSION
#define GL_HEADER_VERSION "#version 300 es\n"
#endif

#elif _WIN32

#endif

#endif /* gl_h */
