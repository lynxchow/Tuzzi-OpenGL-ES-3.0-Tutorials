//
//  Application.h
//  Tuzzi
//
//  Created by Lyn on 2019/7/10.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_SYSTEM_H_
#define _TUZZI_SYSTEM_H_

#include "Object.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class Application : public Object
{
public:
    friend class TuzziImpl;
    
    Application();
    virtual ~Application();
    bool isStarted();
    
private:
    void init();
    void update();
    void lateUpdate();
    void destroy();
    virtual void onInit();
    virtual void onUpdate();
    virtual void onLateUpdate();
    virtual void onDestroy();
    
    bool m_is_started = false;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Application_h */
