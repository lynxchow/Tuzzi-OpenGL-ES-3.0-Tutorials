//
//  ColorApplication.h
//  TuzziApp
//
//  Created by Lyn on 2019/5/30.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _COLOR_APPLICATION_H_
#define _COLOR_APPLICATION_H_

#include "Application.h"
#include "Shader.h"

class ColorApplication : public tuzzi::Application
{
public:
    ColorApplication();
    virtual ~ColorApplication();
    
private:
    unsigned int VBO, VAO, EBO;
//    int shaderProgram;
    tuzzi::Shader *m_shader;
    virtual void onInit() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
};

#endif /* ColorApplication_h */
