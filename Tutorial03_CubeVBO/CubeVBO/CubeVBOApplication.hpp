//
//  CubeVBOApplication.hpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef CubeVBOApplication_hpp
#define CubeVBOApplication_hpp

#include "GLApplication.hpp"

class CubeVBOApplication : public GLApplication
{
private:
    GLfloat orientationX;
    GLfloat orientationY;
    GLfloat orientationZ;
    
    GLint m_mvp;
    GLuint vboIds[2];
public:
    CubeVBOApplication();
    virtual bool init();
    virtual void render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* CubeVBOApplication_hpp */
