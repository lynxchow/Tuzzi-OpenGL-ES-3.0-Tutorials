//
//  Shader.h
//  Common
//
//  Created by Pocoyo Chow on 01/12/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <OpenGLES/ES3/gl.h>

class Shader
{
public:
    GLuint program_;
    // Constructor generates the shader on the fly
    Shader(const GLchar *vertex_path, const GLchar *fragment_path)
    {
        // 1. Retrieve the vertex/fragment source code from filePath
        std::string vertex_code;
        std::string fragment_code;
        std::ifstream vertx_shader_file;
        std::ifstream frag_shader_file;
        // ensures ifstream objects can throw exceptions:
        vertx_shader_file.exceptions(std::ifstream::badbit);
        frag_shader_file.exceptions(std::ifstream::badbit);
        try
        {
            // Open files
            vertx_shader_file.open(vertex_path);
            frag_shader_file.open(fragment_path);
            std::stringstream vertx_shader_stream, frag_shader_stream;
            // Read file's buffer contents into streams
            vertx_shader_stream << vertx_shader_file.rdbuf();
            frag_shader_stream << frag_shader_file.rdbuf();
            // close file handlers
            vertx_shader_file.close();
            frag_shader_file.close();
            // Convert stream into string
            vertex_code = vertx_shader_stream.str();
            fragment_code = frag_shader_stream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar *vertx_shader_code = vertex_code.c_str();
        const GLchar *frag_shader_code = fragment_code.c_str();
        // 2. Compile shaders
        GLuint vertex, fragment;
        GLint success;
        GLchar info_log[512];
        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertx_shader_code, NULL);
        glCompileShader(vertex);
        // Print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, info_log);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
        }
        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &frag_shader_code, NULL);
        glCompileShader(fragment);
        // Print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, info_log);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
        }
        // Shader Program
        this->program_ = glCreateProgram();
        glAttachShader(this->program_, vertex);
        glAttachShader(this->program_, fragment);
        glLinkProgram(this->program_);
        // Print linking errors if any
        glGetProgramiv(this->program_, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->program_, 512, NULL, info_log);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
        }
        // Delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        
    }
    // Uses the current shader
    void Use()
    {
        glUseProgram(this->program_);
    }
};

#endif /* SHADER_H_ */
