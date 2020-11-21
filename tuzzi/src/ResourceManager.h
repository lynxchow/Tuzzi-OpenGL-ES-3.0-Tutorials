//
//  ResourceManager.h
//  Tuzzi
//
//  Created by Lyn on 2020/5/13.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_RESOURCE_MANAGGER_H_
#define _TUZZI_RESOURCE_MANAGGER_H_

#include "Common.h"
#include "image/Image.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class ResourceManager
{
    friend class Tuzzi;
    
public:
    SharedPtr<Image> loadImage(const String& path);
    
    SharedPtr<Shader> loadShader(const String& vert_path, const String& frag_path);
    
    SharedPtr<Texture> loadTexture(const String& path, FilterMode filter_mode, WrapMode wrap_mode, bool gen_mipmap);
    
private:
    ResourceManager();
    
    void init();
    
    void destroy();
    
    void setRootDir(const String& path) { m_path = path; }
    
private:
    String m_path;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* ResourceManager_h */
