//
//  TextureManager.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/11/20.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "TextureManager.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

TextureManager::TextureManager()
{
    
}

void TextureManager::init()
{
    
}

void TextureManager::destroy()
{
    
}

void TextureManager::setInputTexture(SharedPtr<Texture>& input_texture)
{
    m_input_texture = input_texture;
}

const SharedPtr<Texture>& TextureManager::getInputTexture()
{
    return m_input_texture;
}

NAMESPACE_TUZZI_ENGINE_END
