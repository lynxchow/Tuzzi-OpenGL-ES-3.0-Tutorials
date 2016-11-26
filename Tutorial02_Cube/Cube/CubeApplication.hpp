//
//  CubeApplication.hpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef CubeApplication_hpp
#define CubeApplication_hpp

#include "GLApplication.hpp"

class CubeApplication : public GLApplication
{
private:
    GLfloat orientationX;
    GLfloat orientationY;
    GLfloat orientationZ;
    GLint m_position;
    GLint m_color;
    GLint m_mvp;
public:
    CubeApplication();
    virtual bool init();
    virtual void render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* CubeApplication_hpp */
