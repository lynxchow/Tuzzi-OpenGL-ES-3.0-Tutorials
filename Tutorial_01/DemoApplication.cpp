//
//  DemoApplication.cpp
//  TuzziApp
//
//  Created by Lyn on 2019/5/30.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "DemoApplication.h"
#include "Tuzzi.h"
#include "gl/gl.h"

NAMESPACE_TUZZI_ENGINE_USING

DemoApplication::DemoApplication() : tuzzi::Application()
{
    
}

DemoApplication::~DemoApplication()
{
    
}

void DemoApplication::onInit()
{
    TZ_LOGD("DemoApplication", "onInit");
}

void DemoApplication::onUpdate()
{
    TZ_LOGD("DemoApplication", "onUpdate");
    
    glClearColor(0.0, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void DemoApplication::onDestroy()
{
    TZ_LOGD("DemoApplication", "onDestroy");
}
