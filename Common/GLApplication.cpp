//
//  GLApplication.cpp
//  Common
//
//  Created by Pocoyo Chow on 24/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#include "GLApplication.h"
#include <iostream>
#include <fstream>

using namespace std;

GLApplication::GLApplication(const char *vert_file, const char *frag_file) : shader_(vert_file, frag_file)
{
    
}

bool GLApplication::IsInitized()
{
    return initized_;
}

void GLApplication::OnValueChanged(const char *key, float value)
{
    
}

void GLApplication::Render(GLuint x, GLuint y, GLuint width, GLuint height)
{

}

GLApplication::~GLApplication()
{
//    glDeleteProgram(programObject);
}
