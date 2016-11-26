//
//  GLApplication.hpp
//  Common
//
//  Created by Pocoyo Chow on 24/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef GLApplication_hpp
#define GLApplication_hpp

#include <OpenGLES/ES3/gl.h>
#include "Util.h"

class GLApplication
{
private:
    GLuint vertShader;
    GLuint fragShader;
    bool initized;
    bool initShader(const char *vertFile, const char *fragFile);
    
public:
    GLApplication(const char *vertFile = NULL, const char *fragFile = NULL);
    bool isInitized();
    virtual ~GLApplication();
    virtual bool init() = 0;
    virtual void render(GLuint x, GLuint y, GLuint width, GLuint height);
    
protected:
    GLuint programObject;
};
#endif /* GLApplication_hpp */
