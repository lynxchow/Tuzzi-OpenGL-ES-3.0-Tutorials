//
//  DiffuseReflectionApplication.hpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef DiffuseReflectionApplication_hpp
#define DiffuseReflectionApplication_hpp

#include "GLApplication.h"

class DiffuseReflectionApplication : public GLApplication
{
private:
    GLfloat orientation_x_;
    GLfloat orientation_y_;
    GLfloat orientation_z_;
    
    GLint mvp_;
    GLint model_;
    GLint model_normal_;
    GLuint vao_id_;
    GLuint vbo_ids_[3];
    GLuint texture_id_;
public:
    DiffuseReflectionApplication();
    virtual bool Init();
    virtual void Render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* DiffuseReflectionApplication_hpp */
