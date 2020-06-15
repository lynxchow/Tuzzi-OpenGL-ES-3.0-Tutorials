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

class TextureApplication : public tuzzi::Application
{
public:
    TextureApplication();
    virtual ~TextureApplication();
    
private:
    unsigned int VBO, VAO, EBO;
    unsigned int m_texture;
    
    SharedPtr<tuzzi::Shader> m_shader;
    virtual void onInit() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
};

#endif /* TextureApplication_h */
