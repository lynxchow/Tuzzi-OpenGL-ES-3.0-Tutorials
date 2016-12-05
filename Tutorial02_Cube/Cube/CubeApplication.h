//
//  CubeApplication.hpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef CubeApplication_hpp
#define CubeApplication_hpp

#include "GLApplication.h"

class CubeApplication : public GLApplication
{
private:
    GLfloat orientation_x_;
    GLfloat orientation_y_;
    GLfloat orientation_z_;
    GLint position_;
    GLint color_;
    GLint mvp_;
public:
    CubeApplication();
    virtual bool Init();
    virtual void Render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* CubeApplication_hpp */
