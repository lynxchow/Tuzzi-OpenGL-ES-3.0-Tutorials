//
//  Shader.cpp
//  Tuzzi
//
//  Created by Lyn on 2019/12/17.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "Shader.h"
#include "Log.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "gl/gl.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

Shader::Shader()
{
    
}

bool Shader::initWithFile(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        TZ_LOGE("SHADER", "read file fail");
    }
    const char *vertexSource = vertexCode.c_str();
    const char *fragmentSource = fragmentCode.c_str();
    
    return initWithSource(vertexSource, fragmentSource);
}

bool Shader::initWithSource(const char *vertexSource, const char *fragmentSource)
{
    unsigned int vertex, fragment;
    bool result = true;
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, NULL);
    glCompileShader(vertex);
    result = checkCompileErrors(vertex, "VERTEX");
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, NULL);
    glCompileShader(fragment);
    result = result && checkCompileErrors(fragment, "FRAGMENT");
    
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);
    result = result && checkCompileErrors(m_id, "PROGRAM");
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    return result;
}

void Shader::use()
{
    glUseProgram(m_id);
}

bool Shader::checkCompileErrors(GLuint shader, const std::string &type)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            TZ_LOGE("SHADER", "%s compilation\n %s", type.c_str(), infoLog);
            return false;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            TZ_LOGE("SHADER", "%s compilation\n %s", type.c_str(), infoLog);
            return false;
        }
    }
    
    return true;
}

NAMESPACE_TUZZI_ENGINE_END
