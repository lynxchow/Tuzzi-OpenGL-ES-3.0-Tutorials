//
//  Log.cpp
//  Tuzzi
//
//  Created by Lyn on 2019/11/15.
//

#include "Log.h"
#include "Common.h"
#include "string/String.cpp"
#include <stdarg.h>

#ifdef __ANDROID__
#include <android/log.h>
#elif _WIN32
#include <Windows.h>
#else
#include <stdio.h>
#endif

NAMESPACE_TUZZI_ENGINE_BEGIN

static LogLevel s_log_filter = LOG_LEVEL_INFO;

void Debug::filterLogLevel(LogLevel level)
{
    s_log_filter = level;
}

void Debug::log(LogLevel level, const char *format, ...)
{
#ifdef ENABLE_LOG
    if (level >= s_log_filter)
    {
#ifdef __ANDROID__
        va_list vs;
        va_start(vs, format);
        switch (level) {
            case LOG_LEVEL_INFO:
                __android_log_vprint(ANDROID_LOG_INFO, "Tuzzi", format, vs);
                break;
            case LOG_LEVEL_DEBUG:
                __android_log_vprint(ANDROID_LOG_DEBUG, "Tuzzi", format, vs);
                break;
            case LOG_LEVEL_WARN:
                __android_log_vprint(ANDROID_LOG_WARN, "Tuzzi", format, vs);
                break;
            case LOG_LEVEL_ERROR:
                __android_log_vprint(ANDROID_LOG_ERROR, "Tuzzi", format, vs);
                break;
                
            default:
                break;
        }
        va_end(vs);
#elif _WIN32
        va_list vs;
        va_start(vs, format);
        OutputDebugStringA(stringWithFormat(format, vs).c_str());
        va_end(vs);
#else
        va_list vs;
        va_start(vs, format);
        vprintf(format, vs);
        va_end(vs);
#endif
        
    }
#endif
}



NAMESPACE_TUZZI_ENGINE_END
