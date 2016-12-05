//
//  LoadModelApplication.h
//  ModelLoader
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef LOADMODELAPPLICATION_H_
#define LOADMODELAPPLICATION_H_

#include "GLApplication.h"
#include "Model.h"

class LoadModelApplication : public GLApplication
{
private:
    GLfloat orientationX;
    GLfloat orientationY;
    GLfloat orientationZ;
    
    GLint m_mvp;
    GLuint vaoId;
    GLuint vboIds[2];
    Model *model_;
    
    GLuint color_render_buffer_;
    GLuint frame_buffer_;
public:
    LoadModelApplication();
    virtual bool Init();
    virtual void Render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* LOADMODELAPPLICATION_H_ */
