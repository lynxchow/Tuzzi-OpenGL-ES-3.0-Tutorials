//
//  TriangleApplication.hpp
//  Triangle
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef TriangleApplication_hpp
#define TriangleApplication_hpp

#include "GLApplication.h"

class TriangleApplication : public GLApplication
{
public:
    TriangleApplication();
    virtual bool Init();
    virtual void Render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* TriangleApplication_hpp */
