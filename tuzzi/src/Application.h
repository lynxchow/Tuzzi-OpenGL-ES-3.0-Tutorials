//
//  Application.h
//  Tuzzi
//
//  Created by Lyn on 2019/7/10.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_APPLICATION_H_
#define _TUZZI_APPLICATION_H_

#include "Object.h"
#include "SharedPtr.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class Tuzzi;
class ResourceManager;
class Application : public Object
{
public:
    friend class Tuzzi;
    
    Application();
    virtual ~Application();
    bool isStarted();
    unsigned int getWidth();
    unsigned int getHeight();
    Tuzzi *getTuzzi() const;
    
private:
    void init(Tuzzi *tuzzi);
    void setSize(int width, int height);
    void update();
    void lateUpdate();
    void destroy();
    virtual void onInit();
    virtual void onResize(int width, int height);
    virtual void onUpdate();
    virtual void onLateUpdate();
    virtual void onDestroy();
    
private:
    unsigned int m_width;
    unsigned int m_height;
    bool m_is_started = false;
    Tuzzi *m_tuzzi = nullptr;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Application_h */
