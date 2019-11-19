//
//  DemoApplication.cpp
//  TuzziApp
//
//  Created by Lyn on 2019/5/30.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "DemoApplication.h"
#include "Tuzzi.h"

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
}

void DemoApplication::onDestroy()
{
    TZ_LOGD("DemoApplication", "onDestroy");
}
