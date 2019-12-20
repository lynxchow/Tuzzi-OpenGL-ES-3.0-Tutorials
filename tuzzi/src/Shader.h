//
//  Shader.hpp
//  Tuzzi
//
//  Created by Lyn on 2019/12/17.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_SHADER_H_
#define _TUZZI_SHADER_H_

#include <string>
#include "Common.h"
#include "gl/gl.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class Shader
{
public:
    Shader();
    bool initWithFile(const char *vertexPath, const char *fragmentPath);
    bool initWithSource(const char *vertexSource, const char *fragmentSource);
    void use();
    
private:
    GLuint m_id;
    
    bool checkCompileErrors(GLuint shader, const std::string &type);
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Shader_h */
