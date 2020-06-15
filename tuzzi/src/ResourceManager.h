//
//  ResourceManager.h
//  Tuzzi
//
//  Created by Lyn on 2020/5/13.
//

#ifndef _TUZZI_RESOURCE_MANAGGER_H_
#define _TUZZI_RESOURCE_MANAGGER_H_

#include "Common.h"
#include "Shader.h"
#include "image/Image.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class ResourceManager
{
    friend class TuzziImpl;
public:
    SharedPtr<Image> loadImage(const String& path);
    SharedPtr<Shader> loadShader(const String& vert_path, const String& frag_path);
    
private:
    ResourceManager();
    void init();
    void destroy();
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* ResourceManager_h */
