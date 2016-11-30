//
//  GLApplication.cpp
//  Common
//
//  Created by Pocoyo Chow on 24/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#include "GLApplication.hpp"
#include <iostream>
#include <fstream>

using namespace std;

GLApplication::GLApplication(const char *vertFile, const char *fragFile)
{
    initized = initShader(vertFile, fragFile);
}

bool GLApplication::isInitized()
{
    return initized;
}

GLuint loadShader(GLenum type, const char *shaderFile)
{
    GLuint shader;
    GLint compiled;
    long length = 0;
    char *shaderSrc;
    ifstream in(fileOpen(shaderFile), ios_base::in);
    if (in.is_open())
    {
        in.seekg(0, ios::end);
        length = in.tellg();
        length += 1;
        in.seekg(0, ios::beg);
        shaderSrc = new char[length];
        memset((void *)shaderSrc, 0, sizeof(char) * length);
        in.read(shaderSrc, length);
    }
    else
    {
        utilLog("shader file cannot open.\n");
        return false;
    }
    in.close();
    
    // Create the shader object
    shader = glCreateShader(type);
    
    if (shader == 0)
    {
        return 0;
    }
    
    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);
    
    // Compile the shader
    glCompileShader(shader);
    
    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    
    if (!compiled)
    {
        GLint infoLen = 0;
        
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        
        if (infoLen > 1)
        {
            char *infoLog = (char *)malloc(sizeof(char) * infoLen);
            
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            utilLog("Error compiling shader:\n%s\n", infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}

bool GLApplication::initShader(const char *vertFile, const char *fragFile)
{
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked;
    
    if (vertFile == NULL || fragFile == NULL) {
        return false;
    }
    
    // Load the vertex/fragment shaders
    vertexShader = loadShader(GL_VERTEX_SHADER, vertFile);
    fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragFile);
    
    // Create the program object
    programObject = glCreateProgram();
    
    if (programObject == 0)
    {
        return 0;
    }
    
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    
    // Link the program
    glLinkProgram(programObject);
    
    // Check the link status
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    
    if (!linked)
    {
        GLint infoLen = 0;
        
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        
        if (infoLen > 1)
        {
            char *infoLog = (char *) malloc(sizeof(char) * infoLen);
            
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            utilLog("Error linking program:\n%s\n", infoLog);
            
            free(infoLog);
        }
        
        glDeleteProgram(programObject);
        return false;
    }
    
    return true;
    
}

void GLApplication::onValueChanged(const char *key, float value)
{
    
}

void GLApplication::render(GLuint x, GLuint y, GLuint width, GLuint height)
{

}

GLApplication::~GLApplication()
{
    glDeleteProgram(programObject);
}
