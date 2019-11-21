//
//  gl.h
//  Tuzzi
//
//  Created by Lyn on 2019/11/20.
//

#ifndef _TUZZU_GL_H_
#define _TUZZU_GL_H_



#if defined(__APPLE__)

#include "TargetConditionals.h"
    
#if TARGET_OS_IPHONE
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

#elif TARGET_OS_MAC
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#   error "Unknown Apple platform"
#endif

#elif __ANDROID__

#include <GLES3/gl3.h>

#elif _WIN32

#endif

#endif /* gl_h */
