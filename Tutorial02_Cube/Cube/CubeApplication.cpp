//
//  CubeApplication.cpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#include "CubeApplication.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtx/euler_angles.hpp"

CubeApplication::CubeApplication() : GLApplication("shader.vsh", "shader.fsh")
{
    orientationX = 0;
    orientationY = 0;
    orientationZ = 0;
}

bool CubeApplication::init()
{
    m_position = glGetAttribLocation(programObject, "m_position");
    m_color = glGetAttribLocation(programObject, "m_color");
    m_mvp = glGetUniformLocation(programObject, "m_mvp");
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return true;
}

void CubeApplication::render(GLuint x, GLuint y, GLuint width, GLuint height)
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width, height);
    
    orientationX += 3.0f;
    orientationY += 4.0f;
    orientationZ += 5.0f;
    
    //model;
    glm::mat4 trans = glm::translate(glm::vec3(0,0,0));
    
    glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(orientationX), glm::radians(orientationY), glm::radians(orientationZ));
    glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));

    glm::mat4 model = trans*scale*rotation;
    
    //View
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 15), glm::vec3(0, 0,0), glm::vec3(0, 1, 0));
    
    
    glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)width / height, 0.3f, 1000.0f);
    
    proj = proj*view*model;
    
    glUseProgram(programObject);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    glEnableVertexAttribArray(m_position);
    glEnableVertexAttribArray(m_color);

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
    
    glUniformMatrix4fv(m_mvp, 1, false, &proj[0][0]);
    
    glVertexAttribPointer(m_position, 3, GL_FLOAT, false, sizeof(glm::vec3), pos);
    glVertexAttribPointer(m_color, 4, GL_FLOAT, false, sizeof(glm::vec4), color);
    
    glDrawArrays(GL_TRIANGLES, 0, 6*6);

    glDisableVertexAttribArray(m_position);
    glDisableVertexAttribArray(m_color);
    glUseProgram(0);
}
