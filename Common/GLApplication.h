//
//  GLApplication.h
//  Common
//
//  Created by Pocoyo Chow on 24/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef GLAPPLICATION_H_
#define GLAPPLICATION_H_

#include <OpenGLES/ES3/gl.h>
#include "Util.h"
#include "Shader.h"

class GLApplication
{
private:
    GLuint vert_shader_;
    GLuint frag_shader_;
    bool initized_;
    bool InitShader(const char *vert_file, const char *frag_file);
    
public:
    GLApplication(const char *vert_file = NULL, const char *frag_file = NULL);
    bool IsInitized();
    virtual ~GLApplication();
    virtual bool Init() = 0;
    virtual void Render(GLuint x, GLuint y, GLuint width, GLuint height);
    virtual void OnValueChanged(const char *key, float value);
    
protected:
    Shader shader_;
};
#endif /* GLAPPLICATION_H_ */
