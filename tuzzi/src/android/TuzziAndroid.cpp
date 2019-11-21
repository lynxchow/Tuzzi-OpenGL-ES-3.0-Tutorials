#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <android/native_window.h>
#include <EGL/egl.h>
#include <GLES/gl.h>

#include "Log.h"
#include "Tuzzi.h"
#include "android/TuzziAndroid.h"

TuzziAndroid::TuzziAndroid(ANativeWindow *window)
    : _display(nullptr), _surface(nullptr), _context(nullptr)
{
    _window = window;
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

void TuzziAndroid::resume()
{

}

void TuzziAndroid::pause()
{

}

bool TuzziAndroid::initialize()
{
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
    
    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        TZ_LOGE("TuzziAndroid", "eglGetDisplay() returned error %d", eglGetError());
        return false;
    }
    if (!eglInitialize(display, 0, 0)) {
        TZ_LOGE("TuzziAndroid", "eglInitialize() returned error %d", eglGetError());
        return false;
    }

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

    ANativeWindow_setBuffersGeometry(_window, 0, 0, format);

    if (!(surface = eglCreateWindowSurface(display, config, _window, 0))) {
        TZ_LOGE("TuzziAndroid", "eglCreateWindowSurface() returned error %d", eglGetError());
        destroy();
        return false;
    }
    
    if (!(context = eglCreateContext(display, config, 0, 0))) {
        TZ_LOGE("TuzziAndroid", "eglCreateContext() returned error %d", eglGetError());
        destroy();
        return false;
    }
    
    if (!eglMakeCurrent(display, surface, surface, context)) {
        TZ_LOGE("TuzziAndroid", "eglMakeCurrent() returned error %d", eglGetError());
        destroy();
        return false;
    }

    if (!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
        !eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
        TZ_LOGE("TuzziAndroid", "eglQuerySurface() returned error %d", eglGetError());
        destroy();
        return false;
    }

    _display = display;
    _surface = surface;
    _context = context;

    return true;
}

void TuzziAndroid::destroy() {
    tuzzi::Tuzzi::instance()->destroy();
    eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(_display, _context);
    eglDestroySurface(_display, _surface);
    eglTerminate(_display);
    
    _display = EGL_NO_DISPLAY;
    _surface = EGL_NO_SURFACE;
    _context = EGL_NO_CONTEXT;

    return;
}

void TuzziAndroid::drawFrame()
{
    tuzzi::Tuzzi::instance()->update();

    if (!eglSwapBuffers(_display, _surface)) {
        TZ_LOGE("TuzziAndroid", "eglSwapBuffers() returned error %d", eglGetError());
    }
}

