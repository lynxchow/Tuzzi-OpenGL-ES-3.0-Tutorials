#ifndef _TUZZI_ANDROID_H_
#define _TUZZI_ANDROID_H_

#include <EGL/egl.h>
#include <GLES/gl.h>

class TuzziAndroid {

public:

    TuzziAndroid(ANativeWindow* window);

    virtual ~TuzziAndroid();

    bool loadApplication(SharedPtr<tuzzi::Application> application);

    void pause();

    void resume();

    void drawFrame();

    void destroy();

private:

    ANativeWindow* _window;

    EGLDisplay _display;
    EGLSurface _surface;
    EGLContext _context;

    bool initialize();

};

#endif
