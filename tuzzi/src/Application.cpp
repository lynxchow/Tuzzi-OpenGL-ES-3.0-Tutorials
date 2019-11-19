//
//  Application.cpp
//  Tuzzi
//
//  Created by Lyn on 2019/7/10.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "Application.h"

NAMESPACE_TUZZI_ENGINE_BEGIN
    
Application::Application()
{
    
}

Application::~Application()
{
    
}

void Application::init()
{
    m_is_started = true;
    this->onInit();
}

void Application::onInit()
{
    
}

void Application::onUpdate()
{
    
}

void Application::onLateUpdate()
{
    
}

void Application::onDestroy()
{
    
}

void Application::update()
{
    this->onUpdate();
}

void Application::lateUpdate()
{
    this->onLateUpdate();
}

void Application::destroy()
{
    m_is_started = false;
    this->onDestroy();
}

bool Application::isStarted()
{
    return m_is_started;
}
    
NAMESPACE_TUZZI_ENGINE_END
