//
//  Tuzzi.cpp
//  Tuzzi
//
//  Created by Lyn on 2019/5/30.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "Tuzzi.h"
#include "Application.h"
#include "ResourceManager.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

Tuzzi::Tuzzi()
{
    
}

Tuzzi::~Tuzzi()
{
    
}

bool Tuzzi::loadApplication(SharedPtr<Application> application)
{
    m_application = application;
    
    if (m_application)
    {
        m_application->setSize(m_width, m_height);
        m_application->init(this);
    }
    
    return true;
}

bool Tuzzi::unloadApplication()
{
    if (m_application)
    {
        m_application->destroy();
        m_application = nullptr;
        return true;
    }
    
    return false;
}

SharedPtr<Application> Tuzzi::currentApplication()
{
    return m_application;
}

void Tuzzi::init()
{
    m_resource_manager.init();
    m_resource_manager.setRootDir(getResourcePath());
    m_texture_manager.init();
    
    if (m_application)
    {
        m_application->setSize(m_width, m_height);
        m_application->init(this);
    }
}

ResourceManager *Tuzzi::getResourceManager()
{
    return &m_resource_manager;
}

TextureManager *Tuzzi::getTextureManager()
{
    return &m_texture_manager;
}

void Tuzzi::setSize(int width, int height)
{
    m_width = width;
    m_height = height;
    if (m_application)
    {
        m_application->setSize(width, height);
    }
}

void Tuzzi::update()
{
    if (m_application)
    {
        m_application->update();
    }
}

void Tuzzi::destroy()
{
    if (m_application)
    {
        m_application->destroy();
        m_application = nullptr;
    }
    m_texture_manager.destroy();
    m_resource_manager.destroy();
}

NAMESPACE_TUZZI_ENGINE_END
