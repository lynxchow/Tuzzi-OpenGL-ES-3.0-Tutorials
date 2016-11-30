//
//  AmbientLightApplication.hpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef AmbientLightApplication_hpp
#define AmbientLightApplication_hpp

#include "GLApplication.hpp"

class AmbientLightApplication : public GLApplication
{
private:
    GLfloat orientationX;
    GLfloat orientationY;
    GLfloat orientationZ;
    
    GLint m_mvp;
    GLint ambientStrength;
    GLuint vaoId;
    GLuint vboIds[2];
    GLuint textureId;
public:
    AmbientLightApplication();
    virtual bool init();
    virtual void onValueChanged(const char *key, float value);
    virtual void render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* AmbientLightApplication_hpp */
