//
//  DiffuseReflectionApplication.hpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef DiffuseReflectionApplication_hpp
#define DiffuseReflectionApplication_hpp

#include "GLApplication.hpp"

class DiffuseReflectionApplication : public GLApplication
{
private:
    GLfloat orientationX;
    GLfloat orientationY;
    GLfloat orientationZ;
    
    GLint m_mvp;
    GLint model;
    GLint modelNormal;
    GLuint vaoId;
    GLuint vboIds[3];
    GLuint textureId;
public:
    DiffuseReflectionApplication();
    virtual bool init();
    virtual void render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* DiffuseReflectionApplication_hpp */
