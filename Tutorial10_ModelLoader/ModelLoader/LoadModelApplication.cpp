//
//  LoadModelApplication.cpp
//  ModelLoader
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#include "LoadModelApplication.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "assimp/Importer.hpp"
#include "Util.h"

#define VERTEX_POS_SIZE       3 // x, y and z
#define VERTEX_COLOR_SIZE     4 // r, g, b, and a

#define VERTEX_POS_INDX       0
#define VERTEX_COLOR_INDX     1

LoadModelApplication::LoadModelApplication() : GLApplication(GetAbsolutePath("shader.vsh"), GetAbsolutePath("shader.fsh"))
{
    vaoId = 0;
    vboIds[0] = 0;
    vboIds[1] = 0;
    
    orientationX = 0;
    orientationY = 0;
    orientationZ = 0;
}

bool LoadModelApplication::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    this->model_ = new Model(GetAbsolutePath("earth.obj"));
    this->shader_.Use();
    return true;
}

void LoadModelApplication::Render(GLuint x, GLuint y, GLuint width, GLuint height)
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    glViewport(0, 0, width, height);
    
    orientationX += 1.0f;
    orientationY = 0.0f;
    orientationZ = 0.0f;
    
    shader_.Use();
    // Transformation matrices
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float) width / height, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 1.0f, 3.0f), glm::vec3(0, 1.0, 0), glm::vec3(0, 1, 0));
    
    glUniformMatrix4fv(glGetUniformLocation(shader_.program_, "projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader_.program_, "view"), 1, GL_FALSE, &view[0][0]);
    
    // Draw the loaded model
    glm::mat4 trans = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene
    glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));	// It's a bit too big for our scene, so scale it down
    
    glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(orientationX), glm::radians(orientationY), glm::radians(orientationZ));
    
    glm::mat4 model = trans * scale * rotation;
    
    glUniformMatrix4fv(glGetUniformLocation(shader_.program_, "model"), 1, GL_FALSE, &model[0][0]);
    this->model_->Draw(this->shader_);
    
}
