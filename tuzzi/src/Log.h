#ifndef _TUZZI_LOG_H_
#define _TUZZI_LOG_H_

#include "string/String.h"
#include "Common.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

enum LogLevel
{
    LOG_LEVEL_INFO = 0,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
};

class Debug
{
public:
    static void log(LogLevel level, const char *format, ...);
    static void filterLogLevel(LogLevel level);
};

#define TZ_LOGI(TAG, FMT, ...) Debug::log(LOG_LEVEL_INFO, "(%s:%d)[INFO][%s]: " FMT "\n", __FILE__, __LINE__, TAG, ##__VA_ARGS__)
#define TZ_LOGD(TAG, FMT, ...) Debug::log(LOG_LEVEL_DEBUG, "(%s:%d)[DEBUG][%s]: " FMT "\n", __FILE__, __LINE__, TAG, ##__VA_ARGS__)
#define TZ_LOGW(TAG, FMT, ...) Debug::log(LOG_LEVEL_WARN, "(%s:%d)[WARN][%s]: " FMT "\n", __FILE__, __LINE__, TAG, ##__VA_ARGS__)
#define TZ_LOGE(TAG, FMT, ...) Debug::log(LOG_LEVEL_ERROR, "(%s:%d)[ERROR][%s]: " FMT "\n", __FILE__, __LINE__, TAG, ##__VA_ARGS__)

NAMESPACE_TUZZI_ENGINE_END

#endif
