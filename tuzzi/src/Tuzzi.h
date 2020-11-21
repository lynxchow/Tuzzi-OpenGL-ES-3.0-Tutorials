//
//  Tuzzi.h
//  Tuzzi
//
//  Created by Lyn on 2019/5/30.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_TUZZI_H_
#define _TUZZI_TUZZI_H_

#include <stdio.h>
#include "Common.h"
#include "Log.h"
#include "SharedPtr.h"
#include "ResourceManager.h"
#include "TextureManager.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class Application;
class TuzziImpl;
class ResourceManager;

class Tuzzi
{
public:
    Tuzzi();
    virtual ~Tuzzi();
    bool loadApplication(SharedPtr<Application> app);
    bool unloadApplication();
    SharedPtr<Application> currentApplication();
    ResourceManager *getResourceManager();
    TextureManager *getTextureManager();
    const String& getResourcePath();
    void setSize(int width, int height);
    void init();
    void destroy();
    void update();
    
private:
    SharedPtr<Application> m_application;
    ResourceManager m_resource_manager;
    TextureManager m_texture_manager;
    unsigned int m_width;
    unsigned int m_height;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Tuzzi_h */
