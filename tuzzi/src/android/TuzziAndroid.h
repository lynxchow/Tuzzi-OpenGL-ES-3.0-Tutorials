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

    void onSurfaceDestory();

private:

    ANativeWindow *m_window;

    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;

    bool initialize();

};

#endif
