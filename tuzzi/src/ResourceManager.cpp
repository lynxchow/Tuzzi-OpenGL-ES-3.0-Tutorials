//
//  ResourceManager.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/5/15.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "ResourceManager.h"
#include "Tuzzi.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

ResourceManager::ResourceManager()
{
    
}

void ResourceManager::init()
{
    
}

void ResourceManager::destroy()
{
    
}

SharedPtr<Image> ResourceManager::loadImage(const String& path)
{
    String full_path = m_path + "/" + path;
    return Image::loadFromFile(full_path);
}

SharedPtr<Shader> ResourceManager::loadShader(const String& vert_path, const String& frag_path)
{
    String full_vert_path = m_path + "/" + vert_path;
    String full_frag_path = m_path + "/" + frag_path;
    
    SharedPtr<Shader> shader = MakeShared<Shader>();
    shader->initWithFile(full_vert_path.str(), full_frag_path.str());
    return shader;
}

SharedPtr<Texture> ResourceManager::loadTexture(const String& path, FilterMode filter_mode, WrapMode wrap_mode, bool gen_mipmap)
{
    String full_path = m_path + "/" + path;
    return Texture::loadTexture2DFromFile(full_path, filter_mode, wrap_mode, gen_mipmap);
}

NAMESPACE_TUZZI_ENGINE_END
