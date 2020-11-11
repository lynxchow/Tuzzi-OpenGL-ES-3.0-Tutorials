//
//  TextureApplication.h
//  TuzziApp
//
//  Created by Lyn on 2019/5/30.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TEXTURE_APPLICATION_H_
#define _TEXTURE_APPLICATION_H_

#include "Application.h"
#include "Shader.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"

class TextureApplication : public tuzzi::Application
{
public:
    TextureApplication();
    
    virtual ~TextureApplication();
    
private:
    virtual void onInit() override;
    
    virtual void onUpdate() override;
    
    virtual void onDestroy() override;
    
    SharedPtr<tuzzi::Texture> m_texture;
    SharedPtr<tuzzi::Mesh> m_mesh;
    SharedPtr<tuzzi::Shader> m_shader;
};

#endif /* TextureApplication_h */
