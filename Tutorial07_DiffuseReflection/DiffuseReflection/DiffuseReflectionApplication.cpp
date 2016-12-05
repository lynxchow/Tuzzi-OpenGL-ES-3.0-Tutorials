//
//  DiffuseReflectionApplication.cpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#include "DiffuseReflectionApplication.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtx/euler_angles.hpp"

#define VERTEX_POS_SIZE       3 // x, y and z
#define VERTEX_COLOR_SIZE     4 // r, g, b, and a

#define VERTEX_POS_INDX       0
#define VERTEX_COLOR_INDX     1
#define VERTEX_NORMAL_INDX    2

DiffuseReflectionApplication::DiffuseReflectionApplication() : GLApplication(GetAbsolutePath("shader.vsh"), GetAbsolutePath("shader.fsh"))
{
    vao_id_ = 0;
    vbo_ids_[0] = 0;
    vbo_ids_[1] = 0;
    vbo_ids_[2] = 0;
    
    orientation_x_ = 0;
    orientation_y_ = 0;
    orientation_z_ = 0;
}

GLuint CreateTexture2D(const char *fileName)
{
    // Texture object handle
    GLuint texture_id_;
    
    int width, height;
    GLubyte *pixels = LoadTGA(fileName, &width, &height);
    
    
    // Use tightly packed data
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Generate a texture object
    glGenTextures(1, &texture_id_);
    
    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    
    // Load the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    return texture_id_;
}

bool DiffuseReflectionApplication::Init()
{
    texture_id_ = CreateTexture2D(GetAbsolutePath("box.tga"));
    model_ = glGetUniformLocation(shader_.program_, "m_model");
    mvp_ = glGetUniformLocation(shader_.program_, "m_mvp");
    
    model_normal_ = glGetUniformLocation(shader_.program_, "m_modelNormal");
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    glm::vec3 pos[] =
    {
        //Front
        glm::vec3(-1.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        
        glm::vec3(-1.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        
        //back
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f),
        
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f),
        
        //left
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f),
        
        //right
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f),
        
        //up
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f),
        
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f),
        
        //down
        glm::vec3(-1.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        
        glm::vec3(-1.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
    };
    
    glm::vec2 uv[] =
    {
        //front
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(1, 1),
        
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(0, 1),
        
        //back
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(1, 1),
        
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(0, 1),
        
        //left
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(1, 1),
        
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(0, 1),
        
        //right
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(1, 1),
        
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(0, 1),
        
        //top
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(1, 1),
        
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(0, 1),
        
        //down
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(1, 1),
        
        glm::vec2(0, 0),
        glm::vec2(1, 1),
        glm::vec2(0, 1)
    };
    
    glm::vec3 normal[] =
    {
        //Front
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        
        //back
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        
        //left
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        
        //right
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        
        //up
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        
        //down
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
    };
    
    glGenVertexArrays(1, &vao_id_);
    glBindVertexArray(vao_id_);
    
    glGenBuffers(3, vbo_ids_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids_[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids_[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids_[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normal), normal, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids_[0]);
    glEnableVertexAttribArray(VERTEX_POS_INDX);
    glVertexAttribPointer(VERTEX_POS_INDX, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void *) 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids_[1]);
    glEnableVertexAttribArray(VERTEX_COLOR_INDX);
    glVertexAttribPointer(VERTEX_COLOR_INDX, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (const void *) 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ids_[2]);
    glEnableVertexAttribArray(VERTEX_NORMAL_INDX);
    glVertexAttribPointer(VERTEX_NORMAL_INDX, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, ( const void * ) 0);
    
    glBindVertexArray(0);
    
    return true;
}

void DiffuseReflectionApplication::Render(GLuint x, GLuint y, GLuint width, GLuint height)
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    glViewport(0, 0, width, height);
    orientation_x_ += 3.0f;
    orientation_y_ += 4.0f;
    orientation_z_ += 5.0f;
    
    // Model
    glm::mat4 trans = glm::translate(glm::vec3(0,0,0));
    
    glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(orientation_x_), glm::radians(orientation_y_), glm::radians(orientation_z_));
    glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));
    
    glm::mat4 model = trans*scale*rotation;
    
    // View
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 15), glm::vec3(0, 0,0), glm::vec3(0, 1, 0));
    
    // Proj
    glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)width / height, 0.3f, 1000.0f);
    
    proj = proj * view * model;
    
    shader_.Use();
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    glUniformMatrix4fv(this->model_, 1, false, &model[0][0]);
    glUniformMatrix4fv(mvp_, 1, false, &proj[0][0]);
    
    glm::mat4 modelofnormal = glm::transpose(glm::inverse(model));
    glUniformMatrix4fv(model_normal_, 1, false, &modelofnormal[0][0]);
    
    glBindVertexArray(vao_id_);
    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    
    glDrawArrays(GL_TRIANGLES, 0, 6 * 6);
    glBindVertexArray(0);
}
