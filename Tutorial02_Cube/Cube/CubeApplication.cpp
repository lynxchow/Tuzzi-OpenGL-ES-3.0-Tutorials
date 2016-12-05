//
//  CubeApplication.cpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#include "CubeApplication.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtx/euler_angles.hpp"

CubeApplication::CubeApplication() : GLApplication(GetAbsolutePath("shader.vsh"), GetAbsolutePath("shader.fsh"))
{
    orientation_x_ = 0;
    orientation_y_ = 0;
    orientation_z_ = 0;
}

bool CubeApplication::Init()
{
    position_ = glGetAttribLocation(shader_.program_, "m_position");
    color_ = glGetAttribLocation(shader_.program_, "m_color");
    mvp_ = glGetUniformLocation(shader_.program_, "m_mvp");
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return true;
}

void CubeApplication::Render(GLuint x, GLuint y, GLuint width, GLuint height)
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width, height);
    
    orientation_x_ += 3.0f;
    orientation_y_ += 4.0f;
    orientation_z_ += 5.0f;
    
    //model;
    glm::mat4 trans = glm::translate(glm::vec3(0,0,0));
    
    glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(orientation_x_), glm::radians(orientation_y_), glm::radians(orientation_z_));
    glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));

    glm::mat4 model = trans*scale*rotation;
    
    //View
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 15), glm::vec3(0, 0,0), glm::vec3(0, 1, 0));
    
    
    glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)width / height, 0.3f, 1000.0f);
    
    proj = proj * view * model;
    
    shader_.Use();
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    glEnableVertexAttribArray(position_);
    glEnableVertexAttribArray(color_);

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
    
    glm::vec4 color[] =
    {
        //Front
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        
        //back
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        
        //left
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        
        //right
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        
        //up
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        
        //down
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
    };
    
    glUniformMatrix4fv(mvp_, 1, false, &proj[0][0]);
    
    glVertexAttribPointer(position_, 3, GL_FLOAT, false, sizeof(glm::vec3), pos);
    glVertexAttribPointer(color_, 4, GL_FLOAT, false, sizeof(glm::vec4), color);
    
    glDrawArrays(GL_TRIANGLES, 0, 6 * 6);

    glDisableVertexAttribArray(position_);
    glDisableVertexAttribArray(color_);
    glUseProgram(0);
}
