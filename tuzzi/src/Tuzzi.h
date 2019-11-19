//
//  Tuzzi.h
//  Tuzzi
//
//  Created by Lyn on 2019/5/30.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_REATRIX_H_
#define _TUZZI_REATRIX_H_

#include <stdio.h>
#include "Common.h"
#include "Log.h"
#include "SharedPtr.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class Application;
class TuzziImpl;

class Tuzzi
{
private:
    Tuzzi();
    
public:
    static Tuzzi *instance();
    virtual ~Tuzzi();
    bool loadApplication(SharedPtr<Application> app);
    bool unloadApplication();
    SharedPtr<Application> currentApplication();
    void init();
    void destroy();
    void update();
    
private:
    TuzziImpl *m_impl;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Tuzzi_h */
