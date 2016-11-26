//
//  CubeVAOApplication.hpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef CubeVAOApplication_hpp
#define CubeVAOApplication_hpp

#include "GLApplication.hpp"

class CubeVAOApplication : public GLApplication
{
private:
    GLfloat orientationX;
    GLfloat orientationY;
    GLfloat orientationZ;
    
    GLint m_mvp;
    GLuint vaoId;
    GLuint vboIds[2];
public:
    CubeVAOApplication();
    virtual bool init();
    virtual void render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* CubeVAOApplication_hpp */
