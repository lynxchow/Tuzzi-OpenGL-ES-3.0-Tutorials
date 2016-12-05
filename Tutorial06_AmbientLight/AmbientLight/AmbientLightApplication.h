//
//  AmbientLightApplication.hpp
//  Cube
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef AmbientLightApplication_hpp
#define AmbientLightApplication_hpp

#include "GLApplication.h"

class AmbientLightApplication : public GLApplication
{
private:
    GLfloat orientation_x_;
    GLfloat orientation_y_;
    GLfloat orientation_z_;
    
    GLint mvp_;
    GLint ambient_strength_;
    GLuint vao_id_;
    GLuint vbo_ids_[2];
    GLuint texture_id_;
public:
    AmbientLightApplication();
    virtual bool Init();
    virtual void OnValueChanged(const char *key, float value);
    virtual void Render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* AmbientLightApplication_hpp */
