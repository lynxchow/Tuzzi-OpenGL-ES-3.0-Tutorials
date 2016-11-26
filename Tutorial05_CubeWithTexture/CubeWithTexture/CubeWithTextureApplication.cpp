//
//  CubeWithTextureApplication.cpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#include "CubeWithTextureApplication.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtx/euler_angles.hpp"

#define VERTEX_POS_SIZE       3 // x, y and z
#define VERTEX_COLOR_SIZE     4 // r, g, b, and a

#define VERTEX_POS_INDX       0
#define VERTEX_COLOR_INDX     1

CubeWithTextureApplication::CubeWithTextureApplication() : GLApplication("shader.vsh", "shader.fsh")
{
    vaoId = 0;
    vboIds[0] = 0;
    vboIds[1] = 0;
    
    orientationX = 0;
    orientationY = 0;
    orientationZ = 0;
}

GLuint createTexture2D(const char *fileName)
{
    // Texture object handle
    GLuint textureId;
    
    int width, height;
    GLubyte *pixels = loadTGA(fileName, &width, &height);
    
    
    // Use tightly packed data
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Generate a texture object
    glGenTextures(1, &textureId);
    
    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    // Load the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    return textureId;
}

bool CubeWithTextureApplication::init()
{
    textureId = createTexture2D(fileOpen("box.tga"));
    m_mvp = glGetUniformLocation(programObject, "m_mvp");
    
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
    
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
    
    glGenBuffers(2, vboIds);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glEnableVertexAttribArray(VERTEX_POS_INDX);
    glVertexAttribPointer(VERTEX_POS_INDX, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void *) 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
    glEnableVertexAttribArray(VERTEX_COLOR_INDX);
    glVertexAttribPointer(VERTEX_COLOR_INDX, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (const void *) 0);
    
    glBindVertexArray(0);
    
    return true;
}

void CubeWithTextureApplication::render(GLuint x, GLuint y, GLuint width, GLuint height)
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    glViewport(0, 0, width, height);
    orientationX += 3.0f;
    orientationY += 4.0f;
    orientationZ += 5.0f;
    
    // Model
    glm::mat4 trans = glm::translate(glm::vec3(0,0,0));
    
    glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(orientationX), glm::radians(orientationY), glm::radians(orientationZ));
    glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));
    
    glm::mat4 model = trans*scale*rotation;
    
    // View
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 15), glm::vec3(0, 0,0), glm::vec3(0, 1, 0));
    
    // Proj
    glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)width / height, 0.3f, 1000.0f);
    
    proj = proj * view * model;
    
    glUseProgram(programObject);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    glUniformMatrix4fv(m_mvp, 1, false, &proj[0][0]);
    
    glBindVertexArray(vaoId);
    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glDrawArrays(GL_TRIANGLES, 0, 6 * 6);
    glBindVertexArray(0);
}
