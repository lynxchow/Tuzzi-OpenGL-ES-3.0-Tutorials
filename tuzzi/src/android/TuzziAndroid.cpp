#include <stdint.h>
#include <unistd.h>
#include <android/native_window.h>
#include <EGL/egl.h>

#include "Log.h"
#include "Tuzzi.h"
#include "android/TuzziAndroid.h"

TuzziAndroid::TuzziAndroid(ANativeWindow *window)
    : m_display(nullptr), m_surface(nullptr), m_context(nullptr)
{
    m_window = window;
    initialize();
    tuzzi::Tuzzi::instance()->init();
}

TuzziAndroid::~TuzziAndroid()
{

}

bool TuzziAndroid::loadApplication(SharedPtr<tuzzi::Application> application)
{
    return tuzzi::Tuzzi::instance()->loadApplication(application);
}

bool unloadApplication()
{
    return tuzzi::Tuzzi::instance()->unloadApplication();
}

tuzzi::Application *currentApplication()
{
    return tuzzi::Tuzzi::instance()->currentApplication().get();
}

void TuzziAndroid::resume()
{

}

void TuzziAndroid::pause()
{

}

bool TuzziAndroid::initialize()
{
    // 查找可用的surface配置
    const EGLint attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
    };
    EGLDisplay display;
    EGLConfig config;    
    EGLint numConfigs;
    EGLint format;
    EGLSurface surface;
    EGLContext context;
    EGLint width;
    EGLint height;

    // 创建并初始化一个与本地EGL dispaly的连接
    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        TZ_LOGE("TuzziAndroid", "eglGetDisplay() returned error %d", eglGetError());
        return false;
    }
    if (!eglInitialize(display, 0, 0)) {
        TZ_LOGE("TuzziAndroid", "eglInitialize() returned error %d", eglGetError());
        return false;
    }
    // 让EGL推荐匹配的EGLConfig
    if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs)) {
        TZ_LOGE("TuzziAndroid", "eglChooseConfig() returned error %d", eglGetError());
        destroy();
        return false;
    }

    if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format)) {
        TZ_LOGE("TuzziAndroid", "eglGetConfigAttrib() returned error %d", eglGetError());
        destroy();
        return false;
    }

    ANativeWindow_setBuffersGeometry(m_window, 0, 0, format);

    // 创建窗口
    if (!(surface = eglCreateWindowSurface(display, config, m_window, 0))) {
        TZ_LOGE("TuzziAndroid", "eglCreateWindowSurface() returned error %d", eglGetError());
        destroy();
        return false;
    }

    // 渲染上下文的属性，因为要用的是ES 3.0的版本，所以版本信息要初始化为3
    const EGLint context_attribs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 3,
            EGL_NONE
    };
    // 创建渲染上下文
    if (!(context = eglCreateContext(display, config, nullptr, context_attribs))) {
        TZ_LOGE("TuzziAndroid", "eglCreateContext() returned error %d", eglGetError());
        destroy();
        return false;
    }
    // 把 EGLContext 和 EGLSurface 关联起来
    if (!eglMakeCurrent(display, surface, surface, context)) {
        TZ_LOGE("TuzziAndroid", "eglMakeCurrent() returned error %d", eglGetError());
        destroy();
        return false;
    }
    // 获取surface宽高
    if (!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
        !eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
        TZ_LOGE("TuzziAndroid", "eglQuerySurface() returned error %d", eglGetError());
        destroy();
        return false;
    }
    tuzzi::Tuzzi::instance()->setSize(width, height);

    m_display = display;
    m_surface = surface;
    m_context = context;

    return true;
}

void TuzziAndroid::onSurfaceDestory()
{
    // 销毁Context，并释放资源
    eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(m_display, m_context);
    eglDestroySurface(m_display, m_surface);
    eglTerminate(m_display);

    m_display = EGL_NO_DISPLAY;
    m_surface = EGL_NO_SURFACE;
    m_context = EGL_NO_CONTEXT;
}

void TuzziAndroid::destroy()
{
    tuzzi::Tuzzi::instance()->destroy();
}

void TuzziAndroid::drawFrame()
{
    tuzzi::Tuzzi::instance()->update();

    if (!eglSwapBuffers(m_display, m_surface)) {
        TZ_LOGE("TuzziAndroid", "eglSwapBuffers() returned error %d", eglGetError());
    }
}

