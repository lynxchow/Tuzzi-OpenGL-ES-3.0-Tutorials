//
//  TextureManager.h
//  Tuzzi
//
//  Created by Lyn on 2020/11/20.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_TEXTURE_MANAGGER_H_
#define _TUZZI_TEXTURE_MANAGGER_H_

#include "Common.h"
#include "graphics/Texture.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class TextureManager
{
    friend class Tuzzi;

private:
    TextureManager();
    void init();
    void destroy();
    
public:
    void setInputTexture(SharedPtr<Texture>& input_texture);
    const SharedPtr<Texture>& getInputTexture();
    
private:
    SharedPtr<Texture> m_input_texture;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* TextureManager_h */
