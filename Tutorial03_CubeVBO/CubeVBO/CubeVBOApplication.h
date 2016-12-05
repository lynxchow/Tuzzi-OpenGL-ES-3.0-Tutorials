//
//  CubeVBOApplication.hpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef CubeVBOApplication_hpp
#define CubeVBOApplication_hpp

#include "GLApplication.h"

class CubeVBOApplication : public GLApplication
{
private:
    GLfloat orientation_x_;
    GLfloat orientation_y_;
    GLfloat orientation_z_;
    
    GLint mvp_;
    GLuint vbo_ids_[2];
public:
    CubeVBOApplication();
    virtual bool Init();
    virtual void Render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* CubeVBOApplication_hpp */
