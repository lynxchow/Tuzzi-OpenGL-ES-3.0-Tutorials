//
//  TriangleApplication.hpp
//  Triangle
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#ifndef TriangleApplication_hpp
#define TriangleApplication_hpp

#include "GLApplication.hpp"

class TriangleApplication : public GLApplication
{
public:
    TriangleApplication();
    virtual bool init();
    virtual void render(GLuint x, GLuint y, GLuint width, GLuint height);
};

#endif /* TriangleApplication_hpp */
