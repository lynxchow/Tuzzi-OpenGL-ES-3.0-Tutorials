//
//  CubeVAOApplication.hpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef CubeVAOApplication_hpp
#define CubeVAOApplication_hpp

#include "GLApplication.h"

class CubeVAOApplication : public GLApplication
{
private:
    GLfloat orientation_x_;
    GLfloat orientation_y_;
    GLfloat orientation_z_;
    
    GLint mvp_;
    GLuint vao_id_;
    GLuint vbo_ids_[2];
public:
    CubeVAOApplication();
    virtual bool Init();
    virtual void Render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* CubeVAOApplication_hpp */
