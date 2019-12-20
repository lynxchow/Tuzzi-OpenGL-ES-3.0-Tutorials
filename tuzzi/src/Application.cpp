//
//  Application.cpp
//  Tuzzi
//
//  Created by Lyn on 2019/7/10.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "Application.h"

NAMESPACE_TUZZI_ENGINE_BEGIN
    
Application::Application() : m_width(0), m_height(0)
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

void Application::setSize(int width, int height)
{
    if (m_width != width || m_height != height)
    {
        m_width = width;
        m_height = height;
        onResize(width, height);
    }
}

unsigned int Application::getWidth()
{
    return m_width;
}

unsigned int Application::getHeight()
{
    return m_height;
}

void Application::onInit()
{
    
}

void Application::onResize(int width, int height)
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
