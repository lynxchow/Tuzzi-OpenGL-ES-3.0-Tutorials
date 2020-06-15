//
//  ResourceManager.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/5/15.
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
    String full_path = Tuzzi::instance()->getEnginePath() + "/" + path;
    return Image::loadFromFile(full_path);
}

SharedPtr<Shader> ResourceManager::loadShader(const String& vert_path, const String& frag_path)
{
    String full_vert_path = Tuzzi::instance()->getEnginePath() + "/" + vert_path;
    String full_frag_path = Tuzzi::instance()->getEnginePath() + "/" + frag_path;
    
    SharedPtr<Shader> shader = MakeShared<Shader>();
    shader->initWithFile(full_vert_path.str(), full_frag_path.str());
    return shader;
}

NAMESPACE_TUZZI_ENGINE_END
