//
//  CubeWithTextureApplication.hpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef CubeWithTextureApplication_hpp
#define CubeWithTextureApplication_hpp

#include "GLApplication.hpp"

class CubeWithTextureApplication : public GLApplication
{
private:
    GLfloat orientationX;
    GLfloat orientationY;
    GLfloat orientationZ;
    
    GLint m_mvp;
    GLuint vaoId;
    GLuint vboIds[2];
    GLuint textureId;
public:
    CubeWithTextureApplication();
    virtual bool init();
    virtual void render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* CubeWithTextureApplication_hpp */
